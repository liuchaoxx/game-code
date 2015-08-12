// 
// #include <string.h>
// #include "session.h"
// 
// 
// CSession::CSession ()
// {
// 	sendbuf_ = NULL;
// 	recvbuf_ = NULL;
// }
// 
// CSession::~CSession ()
// {
// 	SAFE_DELETE ( sendbuf_ );
// 	SAFE_DELETE ( recvbuf_ );
// }
// 
// void CSession::Initialize ( Socket* sock, UINT32_T sendsize, UINT32_T recvsize )
// {
// 	sock_ = sock;
// 	sendbuf_ = new CIOBuffer ( sendsize );
// 	recvbuf_ = new CIOBuffer ( recvsize );
// }
// 
// void CSession::_Write ( CHAR* param, UINT32_T len )
// {
// 	sendbuf_->Write ( param, len );
// }
// 
// void CSession::_Read ( CHAR* param, UINT32_T len )
// {
// 	recvbuf_->Read ( param, len );
// }
// 
// void CSession::_Send ()
// {
// 	CHAR *buf = NULL; UINT32_T len = 0;
// 	sendbuf_->PopRef ( &buf, &len, true );
// 	if ( len > 0 )
// 	{
// #if defined(__WINDOWS__)
// 		UINT flag = MSG_DONTROUTE;
// #elif defined(__LINUX__)
// 		UINT flag = MSG_NOSIGNAL;
// #endif
// 		UINT32_T sendlen = sock_->send ( buf, len, flag );
// 		if ( sendlen > 0 )
// 		{
// 			sendbuf_->flush ( sendlen, true );
// 		}
// 	}
// }
// 
// void CSession::_Recv ()
// {
// 	CHAR *buf = NULL; UINT32_T len = 0;
// 	recvbuf_->PopRef ( &buf, &len, false );
// 	if ( len > 0 )
// 	{
// 		UINT32_T recvlen = sock_->receive ( buf, len );
// 		if ( recvlen > 0 )
// 		{
// 			recvbuf_->flush ( recvlen, false );
// 		}
// 	}
// }
// 
// void CSession::_close ()
// {
// 	sock_->close ();
// 	SAFE_DELETE ( sock_ );
// }