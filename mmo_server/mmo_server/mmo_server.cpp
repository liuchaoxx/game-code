// mmo_server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
// #include "commondef.h"
// #include "Thread.h"
// #include <iostream>
// #include "session.h"
// #include "message.h"
#include "server.h"

// ISession *session = NULL;
// 
// class TestMessage: public Message
// {
// public:
// 	virtual bool Write ( ISession& session )
// 	{
// 		WriteChar ( session, ( CHAR* )&id, sizeof( UINT32_T ) );
// 		WriteString ( session, this->name );
// 		return true;
// 	}
// 	virtual bool Read ( ISession& session )
// 	{
// 		ReadChar ( session, ( CHAR* )&id, sizeof( UINT32_T ) );
// 		ReadString ( session, this->name );
// 		return true;
// 	}
// 
// public:
// 	UINT32 id;
// 	std::string name;
// };
// 
// class ServerThread: public Thread
// {
// public:
// 	virtual void run ()
// 	{
// 		while ( 1 )
// 		{
// 			TestMessage msg;
// 			msg.id = 1024;
// 			msg.name = "hello\0";
// 			msg.Write ( *session );
// 			Sleep ( 1000 );
// 		}
// 	}
// };
Server *server_ = NULL;
int _tmain ( int argc, _TCHAR* argv[] )
{
// 	if ( session == NULL )
// 		session = new ISession ( 2048, 2048 );
// 
// 	Thread *th = new ServerThread ();
// 	th->start ();
// 	while ( 1 )
// 	{
// 		TestMessage msg1;
// 		msg1.Read ( *session );
// 		std::cout << "id ==" << msg1.id << std::endl;
// 		std::cout << "name len ==" << msg1.name.size () << std::endl;
// 		std::cout << "name ==" << msg1.name.c_str () << std::endl;
// 		Sleep ( 1000 );
// 	}
	if (server_ == NULL)
	{
		server_ = new Server ( );
		server_->SetPort ( 1001 );
		server_->Start ();
	}
	 
	while ( 1 )
	{
		server_->SelectEvent ();
		server_->HandleEvent ();
		Sleep ( 100 );
	}
	return 0;
}

