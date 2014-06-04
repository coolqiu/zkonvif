#pragma once

#include "../include/zkwsdd.h"
#include "Target_Client.h"
#include <string>

/** ������ Target ʵ�֣�
		����ʱ�����빤���߳��б�����ʱ���ӹ����߳��б���ɾ�� ....

 */
class zkwsdd_TargetImpl : public Target
{
	std::string id_, type_, url_;

public:
	zkwsdd_TargetImpl(const char *id, const char *type, const char *url);
	~zkwsdd_TargetImpl();

private:
	virtual const char *id() const 
	{
		return id_.c_str();
	}

	virtual const char *type() const
	{
		return type_.c_str();
	}

	virtual const char *url() const
	{
		return url_.c_str();
	}
};

class zkwsdd_ClientImpl : public Client
{
public:

};
