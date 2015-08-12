// mmo_client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "session.h"
#include "message.h"
#include "server.h"

Socket *_client = NULL;
ISession *_session = NULL;

int _tmain(int argc, _TCHAR* argv[])
{
#if defined(__WINDOWS__)
	WORD wVersionRequested;
	WSADATA wsaData;
	INT err;
	wVersionRequested = MAKEWORD ( 2, 2 );
	err = WSAStartup ( wVersionRequested, &wsaData );
#endif

// 	if ( _client == NULL )
// 	{
// 		_client = new Socket( );
// 		_client->create ();
// 		CHAR ipstr[IP_SIZE];
// 		sprintf ( ipstr, "%s", "127.0.0.1" );
// 		if ( _client->connect ( ipstr, 1001 ) )
// 		{
// 			_session = new ISession();
// 			_session->Initialize ( _client, 1024, 1024 );
// 		}
// 	}
// 	while (1)
// 	{
// 		ReqLoginMessage msg;
// 		msg.id = 10000;
// 		msg.name = "liuchao";
// 		msg.Write ( *_session );
// 		_session->_Send ();
// 		printf ( "send message finish" );
// 		Sleep ( 2000 );
// 	}

#if defined(__WINDOWS__)
	WSACleanup ();
#endif
	return 0;
}

 