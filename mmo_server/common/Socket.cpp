
#include "Socket.h"


//////////////////////////////////////////////////////////////////////////
//socket¶¨Òå
//////////////////////////////////////////////////////////////////////////
Socket::Socket ()
{
	m_SocketID = INVALID_SOCKET;
	memset ( &m_SockAddr, 0, sizeof( SOCKADDR_IN ) );
	memset ( m_Host, 0, IP_SIZE );
	m_Port = 0;
	sendbuf_ = NULL;
	recvbuf_ = NULL;
}

Socket::Socket ( const CHAR* host, UINT port )
{
	strncpy ( m_Host, host, IP_SIZE - 1 );
	m_Port = port;
	sendbuf_ = NULL;
	recvbuf_ = NULL;
}

Socket::~Socket ()
{
	this->Close ();
}

UINT Socket::GetPort () const
{
	return m_Port;
}

IP_t Socket::GetHost ( ) const
{
	return ( IP_t )( m_SockAddr.sin_addr.s_addr );;
}

BOOL Socket::IsValid () const
{
	return m_SocketID != INVALID_SOCKET;
}

SOCKET Socket::GetSocket () const
{
	return m_SocketID;
}

BOOL Socket::IsError ( )const
{
	INT error;
	UINT len = sizeof( error );
	return SocketAPI::ox_getsockopt ( m_SocketID, SOL_SOCKET, SO_ERROR, &error, &len );
}

VOID Socket::Close ( )
{
	if ( IsValid () && !IsError () )
	{
		SocketAPI::ox_closesocket ( m_SocketID );
	}

	m_SocketID = INVALID_SOCKET;
	memset ( &m_SockAddr, 0, sizeof( SOCKADDR_IN ) );
	memset ( m_Host, 0, IP_SIZE );
	m_Port = 0;
}

BOOL Socket::Create ()
{
	m_SocketID = SocketAPI::ox_socket ( AF_INET, SOCK_STREAM, 0 );
	memset ( &m_SockAddr, 0, sizeof( m_SockAddr ) );
	m_SockAddr.sin_family = AF_INET;
	return IsValid ();
}

// UINT Socket::GetLinger ()const
// {
// 	struct linger ling;
// 	UINT len = sizeof( ling );
// 
// 	SocketAPI::ox_getsockopt ( m_SocketID, SOL_SOCKET, SO_LINGER, &ling, &len );
// 
// 	return ling.l_linger;
// }
// 
// BOOL Socket::SetLinger ( UINT lingertime )
// {
// 	struct linger ling;
// 
// 	ling.l_onoff = lingertime > 0 ? 1 : 0;
// 	ling.l_linger = lingertime;
// 
// 	return SocketAPI::ox_setsockopt ( m_SocketID, SOL_SOCKET, SO_LINGER, &ling, sizeof( ling ) );
// }
// 
// BOOL Socket::IsNonBlocking ( )const
// {
// 	return SocketAPI::ox_getsocketnonblocking ( m_SocketID );
// }
// 
// BOOL Socket::SetNonBlocking ( BOOL on )
// {
// 	return SocketAPI::ox_setsocketnonblocking ( m_SocketID, on );
// }
// 
// UINT Socket::GetReceiveBufferSize ( )const
// {
// 
// 	UINT ReceiveBufferSize;
// 	UINT size = sizeof( ReceiveBufferSize );
// 
// 	SocketAPI::ox_getsockopt ( m_SocketID, SOL_SOCKET, SO_RCVBUF, &ReceiveBufferSize, &size );
// 
// 	return ReceiveBufferSize;
// }
// 
// BOOL Socket::SetReceiveBufferSize ( UINT size )
// {
// 	return ( BOOL )( SocketAPI::ox_setsockopt ( m_SocketID, SOL_SOCKET, SO_RCVBUF, &size, sizeof( UINT ) ) );
// }
// 
// {
// 
// 	UINT SendBufferSize;
// 	UINT size = sizeof( SendBufferSize );
// 
// 	SocketAPI::ox_getsockopt ( m_SocketID, SOL_SOCKET, SO_SNDBUF, &SendBufferSize, &size );
// 
// 	return SendBufferSize;
// }
// 
// BOOL Socket::SetSendBufferSize ( UINT size )
// {
// 	return ( BOOL )( SocketAPI::ox_setsockopt ( m_SocketID, SOL_SOCKET, SO_SNDBUF, &size, sizeof( UINT ) ) );
// }
// 
// BOOL Socket::SetReuseAddr ( BOOL on )
// {
// 	UINT32_T opt = on == TRUE ? 1 : 0;
// 	return SocketAPI::ox_setsockopt ( m_SocketID, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( opt ) );
// }

VOID Socket::Initialize ( UINT32_T sendbufsize, UINT32_T recvbufsize )
{
	sendbuf_ = new CIOBuffer ( sendbufsize );
	recvbuf_ = new CIOBuffer ( recvbufsize );
}

UINT32_T Socket::GetSessionID ( ) const
{
	return this->GetSocket ();
}

void Socket::Write ( CHAR* param, UINT32_T len )
{
	sendbuf_->Write ( param, len );
}

void Socket::Read ( CHAR* param, UINT32_T len )
{
	recvbuf_->Read ( param, len );
}

void Socket::MessageSent ( )
{
	CHAR *buf = NULL; UINT32_T len = 0;
	sendbuf_->PopRef ( &buf, &len, true );
	if ( len > 0 )
	{
#if defined(__WINDOWS__)
		UINT flag = MSG_DONTROUTE;
#elif defined(__LINUX__)
		UINT flag = MSG_NOSIGNAL;
#endif
		UINT32_T sendlen = SocketAPI::ox_send ( m_SocketID, buf, len, flag );
		if ( sendlen > 0 )
		{
			sendbuf_->flush ( sendlen, true );
		}
	}
}

void Socket::MessageReveive ( )
{
	CHAR *buf = NULL; UINT32_T len = 0;
	recvbuf_->PopRef ( &buf, &len, false );
	if ( len > 0 )
	{
		UINT32_T recvlen = SocketAPI::ox_recv ( m_SocketID, buf, len, 0 );
		if ( recvlen > 0 )
		{
			recvbuf_->flush ( recvlen, false );
		}
	}
}

BOOL Socket::connect ( const CHAR* host, UINT port )
{
	strncpy ( m_Host, host, IP_SIZE - 1 );
	m_Port = port;

	m_SockAddr.sin_addr.s_addr = inet_addr ( m_Host );
	m_SockAddr.sin_port = htons ( m_Port );
	return SocketAPI::ox_connect ( m_SocketID, ( const struct sockaddr * )&m_SockAddr, sizeof( m_SockAddr ) );
}



ServerSocket::ServerSocket ( UINT port, UINT backlog )
{
	BOOL ret = FALSE;
	m_Socket = new Socket;
	if ( m_Socket == NULL )
		throw 1;

	ret = m_Socket->Create ();
	if ( ret == FALSE )
		throw 1;

	UINT32_T opt = 1;
	ret = SocketAPI::ox_setsockopt ( m_Socket->m_SocketID, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof( UINT32_T ) );
	if ( ret == FALSE )
		throw 1;

	ret = this->bind ( port );
	if ( ret == FALSE )
		throw 1;

	//	m_Impl->setSendBufferSize( 9000 );
	//	m_Impl->setReceiveBufferSize( 9000 );

	// set listening queue size
	ret = this->listen ( backlog );
	if ( ret == FALSE )
		throw 1;
}

ServerSocket::~ServerSocket ()
{
	m_Socket->Close ();
}

BOOL ServerSocket::accept ( Socket* socket )
{
	UINT addrlen = sizeof( SOCKADDR_IN );
	socket->Close ();

	socket->m_SocketID = this->accept ( ( struct sockaddr * )( &( m_Socket->m_SockAddr ) ), &addrlen );
	if ( socket->m_SocketID == INVALID_SOCKET )
		return FALSE;

	socket->m_Port = ntohs ( socket->m_SockAddr.sin_port );
	strncpy ( socket->m_Host, inet_ntoa ( socket->m_SockAddr.sin_addr ), IP_SIZE - 1 );

	return TRUE;
}

BOOL ServerSocket::connect ( const CHAR* host, UINT port )
{
	return m_Socket->connect ( host, port );
}

SOCKET ServerSocket::accept ( struct sockaddr* addr, UINT* addrlen )
{
	return SocketAPI::ox_accept ( m_Socket->GetSocket (), addr, addrlen );
}

BOOL ServerSocket::bind ( UINT port )
{
	m_Socket->m_Port = port;
	m_Socket->m_SockAddr.sin_addr.s_addr = htonl ( INADDR_ANY );
	m_Socket->m_SockAddr.sin_port = htons ( m_Socket->m_Port );

	return SocketAPI::ox_bind ( m_Socket->m_SocketID, ( const struct sockaddr * )&m_Socket->m_SockAddr, sizeof( m_Socket->m_SockAddr ) );
}

BOOL ServerSocket::listen ( INT backlog )
{
	return SocketAPI::ox_listen ( m_Socket->m_SocketID, backlog );
}

SOCKET ServerSocket::GetSocketID ()
{
	return m_Socket->GetSocket ();
}

UINT32_T ServerSocket::GetSessionID ( ) const
{
	return m_Socket->GetSessionID ();
}

void ServerSocket::Write ( CHAR* param, UINT32_T len )
{
	m_Socket->Write ( param, len );
}

void ServerSocket::Read ( CHAR* param, UINT32_T len )
{
	m_Socket->Read( param, len );
}

void ServerSocket::MessageSent ( )
{
	m_Socket->MessageSent ( );
}

void ServerSocket::MessageReveive ( )
{
	m_Socket->MessageReveive ( );
}