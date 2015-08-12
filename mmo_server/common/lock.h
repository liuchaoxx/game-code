
#ifndef _MY_LOCK_H
#define _MY_LOCK_H

#include "commondef.h"

//共享锁
#if defined(__WINDOWS__)
#include <WinSock2.h>
class MyLock
{
	CRITICAL_SECTION m_Lock;
public:
	MyLock ()
	{
		InitializeCriticalSection ( &m_Lock );
	};
	~MyLock ()
	{
		DeleteCriticalSection ( &m_Lock );
	};
	VOID	Lock ()
	{
		EnterCriticalSection ( &m_Lock );
	};
	VOID	Unlock ()
	{
		LeaveCriticalSection ( &m_Lock );
	};
};
#elif defined(__LINUX__)
class MyLock
{
	pthread_mutex_t 	m_Mutex;
public:
	MyLock ()
	{
		pthread_mutex_init ( &m_Mutex, NULL );
	};
	~MyLock ()
	{
		pthread_mutex_destroy ( &m_Mutex );
	};
	VOID	Lock ()
	{
		pthread_mutex_lock ( &m_Mutex );
	};
	VOID	Unlock ()
	{
		pthread_mutex_unlock ( &m_Mutex );
	};
};
#endif
//自动加锁解锁器
class AutoLock_T
{
public:
	AutoLock_T ( MyLock& rLock )
	{
		m_pLock = &rLock;
		m_pLock->Lock ();
	}
	~AutoLock_T ()
	{
		m_pLock->Unlock ();
	}
protected:
private:
	AutoLock_T ();
	MyLock* m_pLock;
};

#endif
