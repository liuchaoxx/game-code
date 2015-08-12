#ifndef __THREAD_H__
#define __THREAD_H__

#include "commondef.h"
#if defined(__WINDOWS__)
#include <windows.h>
#endif

class Thread
{

public:
	enum ThreadStatus
	{
		READY,		// ��ǰ�̴߳���׼��״̬
		RUNNING,	// ��������״̬
		EXITING,	// �߳������˳�
		EXIT		// �Ѿ��˳� 
	};

public:
	Thread ();
	virtual ~Thread ();
public:
	void start ();
	virtual void stop ();
	void exit ( void * retval = NULL );
	virtual void run ();
public:
	UINT32_T getTID ()
	{
		return m_TID;
	}
	ThreadStatus getStatus ()
	{
		return m_Status;
	}
	void setStatus ( ThreadStatus status )
	{
		m_Status = status;
	}
private:
	UINT32_T m_TID;
	ThreadStatus m_Status;
#if defined(__WINDOWS__)
	HANDLE m_hThread;
#endif
};

extern UINT32_T g_QuitThreadCount;

#if defined(__LINUX__)
VOID * MyThreadProcess ( VOID * derivedThread ) ;
#elif defined(__WINDOWS__)
DWORD WINAPI MyThreadProcess ( VOID* derivedThread );
#endif

#endif
