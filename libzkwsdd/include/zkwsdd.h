/** zonekey onvif

		zkwsdd_Target: ����ʵ�� onvif target

		class MyService : public wsdd_Target
		{
		public:
			MyService(id, "ptz", "http://xxxx");
		};


		MyService *ptz_service = new MyService("xxxx");
		...
 */

#pragma once

#ifdef WIN32
#	ifdef LIBZKWSDD_EXPORTS
#		define ZKWSDD_API __declspec(dllexport)
#	else
#		define ZKWSDD_API __declspec(dllimport)
#	endif
#else
#	define ZKWSDD_API
#endif 

/** Target ���࣬����ʱ���� Hello������ʱ���� Bye
 */
class ZKWSDD_API zkwsdd_Target
{
public:
	zkwsdd_Target(const char *id,	// ��Ӧ EndpointReference.Address��һ���ʽΪ urn:xxxx-xxxx....
		const char *type = "eval",	// ��Ӧ Type��Ŀǰ����֧�� eval �� ptz ����
		const char *url = 0);		// ��Ӧ XAddrs

	virtual ~zkwsdd_Target();

private:
	void *internal_impl;	// �ڲ�ʵ�֣����Բ�Ҫ�� :)
};
