/** �����߳�
 */

#pragma once

#include <deque>
#include <vector>
#include <string>
#include <cc++/thread.h>
#include "Target_Client.h"

// ���� soap ������������
class ThreadOpaque
{
	std::string name_;
	ost::Thread *th_;

public:
	ThreadOpaque(const char *name, ost::Thread *th) : name_(name), th_(th)
	{
	}

	const char *name() const
	{
		return name_.c_str();
	}

	ost::Thread *th() const
	{
		return th_;
	}
};

/** Target �����̣߳��յ� probe/resolve �󣬻����β�ѯ Target
 */
class TargetThread : ost::Thread
{
	bool quit_;

	typedef std::deque<Target*> FIFO;
	FIFO fifo_;
	ost::Mutex cs_fifo_;

public:
	TargetThread();
	~TargetThread();

	int bind(Target *target);
	int unbind(Target *target);

	// ���� probe ƥ����б�
	std::vector<Target*> probe_matched(const char *type, const char *scope);

private:
	void run();
};
