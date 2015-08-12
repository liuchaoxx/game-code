#ifndef _SERVER_ADAPTER_H
#define _SERVER_ADAPTER_H

#include "commondef.h"
#include "session.h"

class Message;
class Socket;
class IServer
{
public:
	~IServer () {}
	virtual ISession* SessionCreate ( Socket *sock ) = 0;
	virtual void SessionClose ( ISession* session ) = 0;
	virtual ISession* GetSession ( UINT32_T sessionID ) const = 0;
	virtual void doCommand ( ISession& session ) = 0;
	virtual void MessageReceived ( ISession& session ) = 0;
	virtual void MessageSent ( ISession& session ) = 0;
};

class ICodeAdapter
{
public:
	~ICodeAdapter () {}
	virtual bool Encode ( ISession* session, Message *msg ) = 0;
	virtual bool Decode ( ISession* session, Message *msg ) = 0;
};


class IThreadRannable
{
public:
	virtual bool Run ( ISession* session, Message *msg ) = 0;
};

#endif