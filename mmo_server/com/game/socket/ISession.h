#ifndef _ISESION_H
#define _ISESION_H

#include "common.h"

class ISession
{
public:
	virtual ~ISession () {}
	virtual uint32 getSessionID () const = 0;
	//-------------------------------------------------------
	//翔发送缓冲区写数据
	virtual void write ( char* buf, uint32 len ) = 0;
	//-------------------------------------------------------
	//接受缓冲区读取数据
	virtual void read ( char* buf, uint32 len ) = 0;
	//-------------------------------------------------------
	//发送缓冲区数据
	virtual void send() = 0;
	//-------------------------------------------------------
	//接受数据到缓冲区
	virtual void recv() = 0;
};
#endif