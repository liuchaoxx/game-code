#ifndef _SESSION_H
#define _SESSION_H

#include "commondef.h"

class ISession
{
public:
	virtual ~ISession () {}
	virtual UINT32_T GetSessionID ( ) const = 0;
	//-------------------------------------------------------
	//翔发送缓冲区写数据
	virtual void Write ( CHAR* buf, UINT32_T len ) = 0;
	//-------------------------------------------------------
	//接受缓冲区读取数据
	virtual void Read ( CHAR* buf, UINT32_T len ) = 0;
	//-------------------------------------------------------
	//发送缓冲区数据
	virtual void MessageSent () = 0;
	//-------------------------------------------------------
	//接受数据到缓冲区
	virtual void MessageReveive () = 0;
};

#endif