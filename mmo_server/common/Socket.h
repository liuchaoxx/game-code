#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "SocketAPI.h"
#include "iobuffer.h"
#include "server_adapter.h"
#include "session.h"

class Socket : public ISession
{
public:
	Socket ();
	Socket ( const CHAR* host, UINT port );
	virtual ~Socket ();
public:
	UINT GetPort ()const;
	IP_t GetHost ()const;
	BOOL IsValid ()const;
	SOCKET GetSocket ()const;
	BOOL IsError ()const;
public:
	VOID Close ();
	BOOL Create ();
	VOID Initialize ( UINT32_T sendbufsize, UINT32_T recvbufsize );
	BOOL connect ( const CHAR* host, UINT port );
public:
	virtual UINT32_T GetSessionID ( ) const;
	virtual void Write ( CHAR* buf, UINT32_T len );
	virtual void Read ( CHAR* buf, UINT32_T len );
	virtual void MessageSent ( );
	virtual void MessageReveive ( );
public:
	SOCKET m_SocketID;
	SOCKADDR_IN m_SockAddr;
	CHAR m_Host[IP_SIZE];
	UINT m_Port;
	CIOBuffer* sendbuf_;
	CIOBuffer* recvbuf_;
};

class ServerSocket: public ISession
{
public:
	ServerSocket ( UINT port, UINT backlog = 5 );
	~ServerSocket ();
public:
	BOOL accept ( Socket* socket );
	SOCKET accept ( struct sockaddr* addr, UINT* addrlen );
	BOOL connect ( const CHAR* host, UINT port );
	BOOL bind ( UINT port );
	BOOL listen ( INT backlog );
	SOCKET GetSocketID ();
public:
	virtual UINT32_T GetSessionID ( ) const;
	virtual void Write ( CHAR* buf, UINT32_T len );
	virtual void Read ( CHAR* buf, UINT32_T len );
	virtual void MessageSent ( );
	virtual void MessageReveive ( );
private:
	Socket* m_Socket;

};



#endif
