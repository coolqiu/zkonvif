#pragma once

/** ������ڷ��� MyDevice ֧�ָ���ķ��� ...
ע�⣺ ����Ľӿڣ���Ҫ���� MyDevice �� GetServices ʵ����Ҫ������չ .....
*/
class ServiceInf
{
public:
	virtual const char *url() const = 0;	// ���еķ��񣬶������и� url .
	virtual const char *desc() const { return ""; }	// ��ѡ�и�������Ϣ ..
};
