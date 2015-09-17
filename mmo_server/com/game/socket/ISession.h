#ifndef _ISESION_H
#define _ISESION_H

#include "common.h"

class ISession
{
public:
	virtual ~ISession () {}
	virtual uint32 getSessionID () const = 0;
	//-------------------------------------------------------
	//�跢�ͻ�����д����
	virtual void write ( char* buf, uint32 len ) = 0;
	//-------------------------------------------------------
	//���ܻ�������ȡ����
	virtual void read ( char* buf, uint32 len ) = 0;
	//-------------------------------------------------------
	//���ͻ���������
	virtual void send() = 0;
	//-------------------------------------------------------
	//�������ݵ�������
	virtual void recv() = 0;
};
#endif