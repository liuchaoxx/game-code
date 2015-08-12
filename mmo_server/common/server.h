#ifndef _SERVER_H
#define _SERVER_H

#include "ServerSocket.h"
#include <map>
#include "commondef.h"
#include "session.h"
#include "server_adapter.h"
#include "message.h"

class Server: IServer
{
public:
	Server ( );
	~Server ( );
public:
	virtual ISession* SessionCreate ( Socket *sock );
	virtual ISession* GetSession ( UINT32_T sessionID ) const;
	virtual void SessionClose ( ISession* session );
	virtual void doCommand ( ISession& session );
	virtual void MessageReceived ( ISession& session );
	virtual void MessageSent ( ISession& session );
public:
	void SelectEvent ();
	BOOL HandleEvent ( );
	BOOL ReadEvent ( ISession& session );
	BOOL WriteEvent ( ISession& session );
	BOOL ExceptEvent ( ISession& session );
	BOOL ConnEvent ( );
public:
	void SetPort ( INT port ) { port_ = port; }
	void Start ();
	ServerSocket* GetServerSocket () const { return serversock_; }
private:
	ServerSocket *serversock_;
	std::map<UINT32_T, ISession*> clientsession_;
	fd_event event_;
	INT port_;
};

#endif	