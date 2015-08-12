#ifndef _SOCKET_API_H
#define _SOCKET_API_H

#include "commondef.h"
#include <assert.h>
#include "stdio.h"

#if defined(__LINUX__)

typedef		INT		SOCKET;
#define     INVALID_SOCKET   -1
#define		SOCKET_ERROR	 -1

#endif

#if defined(__WINDOWS__)
#include <WinSock2.h>
#endif

static const INT SOCKET_ERROR_WOULDBLOCK = -100;

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
static const UINT szSOCKADDR_IN = sizeof( SOCKADDR_IN );

#if defined(__WINDOWS__)
//网络数据
enum
{
	SELECT_BAK = 0,	//当前系统中拥有的完整句柄数据
	SELECT_USE = 1,	//用于select调用的句柄数据
	SELECT_MAX = 2, //结构使用数量
};

typedef struct fd_event
{
	SOCKET		max_fd_;
	SOCKET		min_fd_;
	fd_set		fd_array;
	fd_set		fd_read;
	fd_set		fd_write;
	fd_set		fd_except;
	timeval		timeout_[SELECT_MAX];

	void fd_init ()
	{
		FD_ZERO ( &fd_array );
		FD_ZERO ( &fd_read );
		FD_ZERO ( &fd_write );
		FD_ZERO ( &fd_except );
	}

	void fd_reset () 
	{
		fd_read = fd_array;
		fd_write = fd_array;
		fd_except = fd_array;
		timeout_[SELECT_USE].tv_sec = timeout_[SELECT_BAK].tv_sec;
		timeout_[SELECT_USE].tv_usec = timeout_[SELECT_BAK].tv_usec;
	}

	void fd_add ( SOCKET fd )
	{
		assert ( fd != INVALID_SOCKET );
		if ( FD_ISSET ( fd, &fd_array ) )
			return ;

		min_fd_ = ( ( min_fd_ == INVALID_SOCKET ) ? fd : min ( fd, min_fd_ ) );
		max_fd_ = ( ( max_fd_ == INVALID_SOCKET ) ? fd : max ( fd, max_fd_ ) );

		FD_SET ( fd, &fd_array );
	}

	void fd_remove(SOCKET fd)
	{
		FD_CLR ( fd, &fd_read );
		FD_CLR ( fd, &fd_write );
		FD_CLR ( fd, &fd_except );
		if ( fd == min_fd_ )
		{
			SOCKET tmp_minfd = INVALID_SOCKET;

			INT fd_count = fd_array.fd_count;
			for ( int i = 0; i < fd_count; i++ )
			{
				if ( tmp_minfd == INVALID_SOCKET )
				{
					tmp_minfd = fd_array.fd_array[i];
					continue;
				}

				if ( fd_array.fd_array[i] < tmp_minfd )
				{
					tmp_minfd = fd_array.fd_array[i];
				}
			}
			min_fd_ = tmp_minfd;
		}

		if ( fd == max_fd_ )
		{
			SOCKET tmp_maxfd = INVALID_SOCKET;

			INT fd_count = fd_array.fd_count;
			for ( int i = 0; i < fd_count; i++ )
			{
				if ( tmp_maxfd == INVALID_SOCKET )
				{
					tmp_maxfd = fd_array.fd_array[i];
					continue;
				}

				if ( fd_array.fd_array[i] > tmp_maxfd )
				{
					tmp_maxfd = fd_array.fd_array[i];
				}
			}
			max_fd_ = tmp_maxfd;
		}
	}
};
#else

enum {
	MAX_EPOLL_SIZE = 9999,
}
typedef struct fd_event
{
	struct epoll_event events[MAX_EPOLL_SIZE];
};

#endif // __WINDOWS__



namespace SocketAPI
{

	SOCKET ox_socket ( INT domain, INT type, INT protocol );

	BOOL ox_bind ( SOCKET s, const struct sockaddr* name, UINT namelen );

	BOOL ox_connect ( SOCKET s, const struct sockaddr* name, UINT namelen );

	BOOL ox_listen ( SOCKET s, UINT backlog );

	SOCKET ox_accept ( SOCKET s, struct sockaddr* addr, UINT* addrlen );

	BOOL ox_getsockopt ( SOCKET s, INT level, INT optname, VOID* optval, UINT* optlen );

	BOOL ox_setsockopt ( SOCKET s, INT level, INT optname, const VOID* optval, UINT optlen );

	UINT ox_send ( SOCKET s, const CHAR * buf, UINT len, UINT flags );

	UINT ox_recv ( SOCKET s, CHAR * buf, UINT len, UINT flags );

	BOOL ox_closesocket ( SOCKET s );

	BOOL ox_ioctlsocket ( SOCKET s, LONG cmd, ULONG* argp );

	BOOL ox_getsocketnonblocking ( SOCKET s );

	BOOL ox_setsocketnonblocking ( SOCKET s, BOOL on );

	BOOL ox_shutdown ( SOCKET s, UINT how );

	INT ox_select ( fd_event* event_ );

	void print_error_code ( char* reason, INT error_code );
}
#endif