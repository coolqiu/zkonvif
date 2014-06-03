/** zonekey onvif

	֧�����ֽ�ɫ��
		client ���� Hello, Bye
		target ���� Probe, Resolve
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

class ZKWSDD_API zkwsdd_Client
{
public:
	zkwsdd_Client();
	virtual ~zkwsdd_Client();

	int probe();	// �������� probe
	int resolve();	// �������� resolve

protected:
	virtual void updated();	// target �б��Ѿ�����

private:
	void *internal_impl;	// �ڲ�ʵ�֣����Բ�Ҫ�� :)
};
