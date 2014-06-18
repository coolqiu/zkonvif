#pragma once

#include <cc++/thread.h>
#include "../soap/soapwsddService.h"
#include "MyDevice.h"
/** �豸����, ���� MyDevice �ӿ�
 */
class MyDeviceDiscovery : wsddService
	, ost::Thread
{
	const MyDevice *device_;

public:
	MyDeviceDiscovery(const MyDevice *device) : wsddService(SOAP_IO_UDP)	// ���� udp ģʽ
	{
		device_ = device;

		start();	// ���������߳� .
	}

private:
	void run();

private:
	static const char *my_messageid()
	{
		static int _i = 0;
		static char buf[64];

		snprintf(buf, sizeof(buf), "id:%u", _i++);

		return buf;
	}

	virtual int Probe(struct wsdd__ProbeType *probe);

	static int debug_before_send(struct soap *soap, const char *data, size_t len);

	/** ������δ���� soapwsddProxy.cpp �и��Ƶ�, �Լ��޸� :)
	  * ����Ϊ static ��Ŀ���Ƿ�ֹʹ�� members
	 */
	static int __send_ProbeMatches(struct soap *soap, const char *soap_endpoint, const char *soap_action, struct wsdd__ProbeMatchesType *wsdd__ProbeMatches);

};