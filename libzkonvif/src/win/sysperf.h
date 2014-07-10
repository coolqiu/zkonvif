#ifdef WIN32

/** ͨ�� WMI �ӿڷ������ܼ�����������֧�� vista ���� windows �汾 */
#pragma once

#include <cc++/thread.h>
#define _WIN32_DCOM
#include <wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")

/** ����һ�������̣߳�ÿ��1���ռ�ͳ����Ϣ�����棬����ѯ */
class SysPerf : ost::Thread
{
	double cpurate_, mem_tot_, mem_used_;
	double disk_tot_, disk_used_;
	double net_sr_, net_rr_;

	bool quit_;

public:
	SysPerf();
	~SysPerf();

	double cpu() const 
	{
		return cpurate_;
	}
	void memory(double &total, double &used) const
	{
		total = mem_tot_, used = mem_used_;
	}
	void disk(double &total, double &used) const
	{
		total = disk_tot_, used = disk_used_;
	}
	void netinfo(double &sentrate, double &recvrate) const
	{
		sentrate = net_sr_, recvrate = net_rr_;
	}

private:
	void run();
	void once(IWbemServices *s);
	void update_cpu(IWbemServices *s);
	void update_mem(IWbemServices *s);
	void update_disk(IWbemServices *s);
	void update_net(IWbemServices *s);
};

#endif // 
