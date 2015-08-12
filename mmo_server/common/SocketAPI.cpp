#include "SocketAPI.h"


BOOL SocketAPI::ox_bind ( SOCKET s, const struct sockaddr * addr, UINT addrlen )
{
	if ( bind ( s, addr, addrlen ) == SOCKET_ERROR )
	{
		return FALSE;
	}

	return TRUE;
}

BOOL SocketAPI::ox_connect ( SOCKET s, const struct sockaddr* addr, UINT addrlen )
{
	if ( connect ( s, addr, addrlen ) == SOCKET_ERROR )
	{
		INT iErr = WSAGetLastError ();
		print_error_code ( "ox_connect", iErr );
		return FALSE;
	}

	return TRUE;
}

BOOL SocketAPI::ox_listen ( SOCKET s, UINT backlog )
{
	if ( listen ( s, backlog ) == SOCKET_ERROR )
	{
		return FALSE;
	}

	return TRUE;
}


SOCKET SocketAPI::ox_accept ( SOCKET s, struct sockaddr * addr, UINT * addrlen )
{
#if defined(__WINDOWS__)
		SOCKET client = accept ( s, addr, ( int* )addrlen );
		if ( client ==  SOCKET_ERROR )
		{
			INT iErr = WSAGetLastError ();
			print_error_code ( "ox_accept", iErr );
		}
#else 
		SOCKET client = accept ( s, addr, addrlen );
#endif
	return client;
}

BOOL SocketAPI::ox_getsockopt( SOCKET s, INT level, INT optname, VOID * optval, UINT * optlen )
{
#if defined(__WINDOWS__)
	if ( getsockopt ( s, level, optname, ( CHAR* )optval, ( int* )optlen ) == SOCKET_ERROR )
	{
		return FALSE;
	}
#else 
	if ( getsockopt ( s, level, optname, optval, optlen ) == SOCKET_ERROR )
	{
		return FALSE;
	}
#endif
	return TRUE;
}



BOOL SocketAPI::ox_setsockopt( SOCKET s, INT level, INT optname, const VOID * optval, UINT optlen )
{
#if defined(__WINDOWS__)
	if ( setsockopt ( s, level, optname, ( CHAR* )optval, optlen ) == SOCKET_ERROR )
	{
		return FALSE;
	}
#else
	if ( setsockopt ( s, level, optname, optval, optlen ) == SOCKET_ERROR )
	{
		switch ( errno )
		{
			case EBADF:
			case ENOTSOCK:
			case ENOPROTOOPT:
			case EFAULT:
			default:
			{
					   break;
			}
		}//end of switch

		return FALSE;
	}
#endif

	return TRUE;
}


UINT SocketAPI::ox_send ( SOCKET s, const CHAR * buf, UINT len, UINT flags )
{
	INT nSent;
#if defined(__WINDOWS__)
	nSent = send ( s, ( const CHAR * )buf, len, flags );
#else
	nSent = send ( s, buf, len, flags );
#endif
	return nSent;
}

UINT SocketAPI::ox_recv ( SOCKET s, CHAR * buf, UINT len, UINT flags )
{

#if defined(__WINDOWS__)
	INT nrecv = recv ( s, ( CHAR* )buf, len, flags );
#else 
	INT nrecv = recv ( s, buf, len, flags );
#endif
	return nrecv;
}


BOOL SocketAPI::ox_closesocket( SOCKET s )
{
#if defined(__WINDOWS__)
	if ( closesocket ( s ) == SOCKET_ERROR )
	{
		INT iErr = WSAGetLastError ();
		print_error_code ( "ox_closesocket", iErr );
		return FALSE;
	}
#else
	close ( s );
#endif
	return TRUE;
}

BOOL SocketAPI::ox_ioctlsocket ( SOCKET s, LONG cmd, ULONG * argp )
{

#if defined(__WINDOWS__)
	if ( ioctlsocket ( s, cmd, argp ) == SOCKET_ERROR )
	{
		return FALSE;
	}
#endif
	return TRUE;
}

BOOL SocketAPI::ox_getsocketnonblocking ( SOCKET s )
{
#if defined(__WINDOWS__)
		return FALSE;
#else
	INT flags = FileAPI::fcntl_ex ( s, F_GETFL, 0 );
	return flags | O_NONBLOCK;
#endif
}

BOOL SocketAPI::ox_setsocketnonblocking ( SOCKET s, BOOL on )
{

#if defined(__WINDOWS__)
	ULONG argp = ( on == TRUE ) ? 1 : 0;
	return ox_ioctlsocket( s, FIONBIO, &argp );
	
#else
	INT flags = FileAPI::fcntl_ex ( s, F_GETFL, 0 );

	if ( on )
		// make nonblocking fd
		flags |= O_NONBLOCK;
	else
		// make blocking fd
		flags &= ~O_NONBLOCK;

	FileAPI::fcntl_ex ( s, F_SETFL, flags );

	return TRUE;

#endif
}

SOCKET SocketAPI::ox_socket ( INT domain, INT type, INT protocol )
{
	SOCKET s = ::socket ( domain, type, protocol ); 
	if ( s == INVALID_SOCKET )
	{
		INT iErr = WSAGetLastError ();
		print_error_code ( "ox_socket", iErr );
	}
	return s;
}


INT SocketAPI::ox_select ( fd_event* event_)
{
	INT result;
#if defined(__WINDOWS__)
	result = select ( event_->max_fd_ + 1, &event_->fd_read, &event_->fd_write, &event_->fd_except, &event_->timeout_[SELECT_USE] );
#elif

#endif
	return result;
}

void SocketAPI::print_error_code( char* reason, INT error_code )
{
	printf ( "socket %s error, error code == %d \n", reason, error_code );
}
