#include "server.h"

Server::Server ( )
{
#if defined(__WINDOWS__)
	WORD wVersionRequested;
	WSADATA wsaData;
	INT err;
	wVersionRequested = MAKEWORD ( 2, 2 );
	err = WSAStartup ( wVersionRequested, &wsaData );
#endif
	event_.fd_init ();
}
Server::~Server ( )
{
#if defined(__WINDOWS__)
	WSACleanup ();
#endif
}

ISession* Server::SessionCreate ( Socket *sock )
{
	event_.fd_add ( sock->m_SocketID );
	clientsession_.insert ( std::pair<INT, ISession*> ( sock->GetSessionID(), sock ) );
	return sock;
}

ISession* Server::GetSession ( UINT32_T sessionID ) const
{
	std::map<UINT32_T, ISession*>::const_iterator iter = clientsession_.find ( sessionID );
	if ( iter == clientsession_.end () )
	{
		return NULL;
	}
	return iter->second;
}

void Server::SessionClose ( ISession* session )
{
	std::map<UINT32_T, ISession*>::iterator iter = clientsession_.find ( session->GetSessionID ( ) );
	if ( iter != clientsession_.end () )
	{
		clientsession_.erase ( iter );
		event_.fd_remove ( session->GetSessionID () );
	}
	SAFE_DELETE ( session );
}

void Server::doCommand ( ISession& session )
{
}

void Server::MessageSent ( ISession& session )
{
	session.MessageSent ();
}

void Server::MessageReceived ( ISession& session )
{
	session.MessageReveive ();
}

void Server::Start ( )
{
	serversock_ = new ServerSocket ( port_ );
	SocketAPI::ox_setsocketnonblocking ( this->serversock_->GetSocketID(), true);
	event_.fd_add ( serversock_->GetSocketID());
}

void Server::SelectEvent ( )
{
	event_.fd_reset ();
	SocketAPI::ox_select ( &event_ );
}

BOOL Server::ReadEvent ( ISession& session )
{
	session.MessageReveive ();
	ReqLoginMessage msg;
	msg.Read ( session );
	printf ( "msg id== %d name== %s\n", msg.id, msg.name.c_str() );
	return TRUE;
}

BOOL Server::WriteEvent ( ISession& session )
{
	session.MessageSent ( );
	return TRUE;
}

BOOL Server::ExceptEvent ( ISession& session )
{
	SessionClose ( &session );
	return TRUE;
}

BOOL Server::ConnEvent ( )
{
	Socket *sock = new Socket ();
	if ( !serversock_->accept ( sock ))
	{
		SAFE_DELETE ( sock );
		return FALSE;
	}
	SessionCreate ( sock );
	return TRUE;
}

BOOL Server::HandleEvent ( )
{
#if defined(__WINDOWS__)

	//新连接接入：
	if ( FD_ISSET ( serversock_->GetSocketID(), &event_.fd_read ) )
	{
		for ( int i = 0; i < ACCEPT_ONESTEP; i++ )
		{
			if ( !ConnEvent () ) 
			{
				break;
			}
		}
		FD_CLR ( serversock_->GetSocketID(), &event_.fd_read );
	}

	UINT32_T fd_count = event_.fd_array.fd_count;
	for ( INT i = 0; i < fd_count; i++ )
	{
		if ( FD_ISSET ( event_.fd_array.fd_array[i], &event_.fd_read ) )
		{
			ISession* session = GetSession ( event_.fd_read.fd_array[i] );
			if ( session != NULL )
			{
				ReadEvent ( *session );
			}
		}
		if ( FD_ISSET ( event_.fd_array.fd_array[i], &event_.fd_write ) )
		{
			ISession* session = GetSession ( event_.fd_write.fd_array[i] );
			if ( session != NULL )
			{
				WriteEvent ( *session );
			}
		}
		if ( FD_ISSET ( event_.fd_array.fd_array[i], &event_.fd_except ) )
		{
			ISession* session = GetSession ( event_.fd_except.fd_array[i] );
			if ( session != NULL )
			{
				ExceptEvent ( *session );
			}
		}
	}
#endif
	return TRUE;
}