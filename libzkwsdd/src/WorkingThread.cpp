#include "utils.h"
#include "WorkingThread.h"
#include "../soap/soapH.h"
#include <algorithm>
#include "log.h"

TargetThread::TargetThread()
{
	quit_ = false;
	start();
}

TargetThread::~TargetThread()
{
	quit_ = true;
	join();
}

int TargetThread::bind(Target *target)
{
	ost::MutexLock al(cs_fifo_);
	fifo_.push_back(target);

	return (int)fifo_.size();
}

int TargetThread::unbind(Target *target)
{
	ost::MutexLock al(cs_fifo_);
	FIFO::iterator itend = std::remove(fifo_.begin(), fifo_.end(), target);
	fifo_.erase(itend, fifo_.end());

	return (int)fifo_.size();
}

#define MULTI_ADDR "239.255.255.250"
#define PORT 3702

void TargetThread::run()
{
	log(LOG_INFO, "%s: Target thread started!\n", __func__);

	/** Target 工作线程加入组播地址，开始接受数据 ....
	 */
	soap soap;
	soap_init1(&soap, SOAP_IO_UDP);
	
	soap.user = new ThreadOpaque("target", this);
	soap.bind_flags = SO_REUSEADDR;		// 可能多个 ...

	if (!soap_valid_socket(soap_bind(&soap, 0, PORT, 100))) {
		log(LOG_FAULT, "%s: soap_bind %d failure!!\n", __func__, PORT);
		::exit(-1);
	}

	ip_mreq mcast;
	mcast.imr_multiaddr.s_addr = inet_addr(MULTI_ADDR);
	mcast.imr_interface.s_addr = inet_addr(util_get_myip());
	if (setsockopt(soap.master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0) {
		log(LOG_FAULT, "%s: ohhh, can't join multiaddr of %s!!!!\n", __func__, MULTI_ADDR);
		::exit(-1);
	}

	while (!quit_) {
		soap_serve(&soap);	// udp 接收阻塞在此. 
		soap_destroy(&soap);
		soap_end(&soap);
	}

	soap_done(&soap);

	log(LOG_INFO, "%s: thread terminated!\n", __func__);
}

std::vector<Target*> TargetThread::probe_matched(const char *types, const char *scopes)
{
	std::vector<Target *> targets;
	ost::MutexLock al(cs_fifo_);

	FIFO::const_iterator it;
	for (it = fifo_.begin(); it != fifo_.end(); ++it) {
		// TODO: 这里进行 types, scopes 的匹配 ...

		targets.push_back(*it);
	}

	return targets;
}

std::vector<Target*> TargetThread::resolve_matched(const char *address)
{
	std::vector<Target *> targets;
	ost::MutexLock al(cs_fifo_);

	FIFO::const_iterator it;
	for (it = fifo_.begin(); it != fifo_.end(); ++it) {
		//这里进行 address 的匹配 ...
		Target *t = *it;
		if (t->id()==address)
		{
			targets.push_back(*it);
		}

	}

	return targets;
}
