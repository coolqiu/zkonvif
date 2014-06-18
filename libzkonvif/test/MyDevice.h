#pragma once

#include "../soap/soapDeviceBindingService.h"
#include <cc++/thread.h>
#include "../../common/utils.h"
#include "myservice.inf.h"
#include "../../common/log.h"

/** ʵ��һ���ӿ�,���ʾ������� gsoap ���ɵ� xxxService��, Ȼ�����ʵ������"���麯��"
 */
class MyDevice : DeviceBindingService
				, ost::Thread
{
	int listen_port_;
	std::string url_;
	std::string id_;
	std::vector<ServiceInf *> services_; // ����豸��, �ۺϵ����з�����б� ...

public:
	MyDevice(int listen_port, const std::vector<ServiceInf *> &services)
	{
		services_ = services;

		listen_port_ = listen_port;
		char buf[128];

		snprintf(buf, sizeof(buf), "http://%s:%d", util_get_myip(), listen_port_);
		url_ = buf;

		log(LOG_INFO, "%s: device mgrt using url='%s'\n", __func__, url_.c_str());

		/** ʹ�� mac ��ַ��Ϊ id */
		snprintf(buf, sizeof(buf), "urn:uuid:%s", util_get_mymac());
		id_ = buf;

		start();	// ���������߳�
	}

	const char *id() const { return id_.c_str(); }
	const char *url() const { return url_.c_str(); }

private:
	void run()
	{
		DeviceBindingService::run(listen_port_);
	}
private:
	/// ����ʵ�� device mgrt �ӿ�...
	virtual int GetServices(_tds__GetServices *tds__GetServices, _tds__GetServicesResponse *tds__GetServicesResponse);

	// ���Թ��߻��������,�����Ϣ ...
	virtual int GetDeviceInformation(_tds__GetDeviceInformation *tds__GetDeviceInformation, _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse);
};
