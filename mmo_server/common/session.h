#ifndef _SESSION_H
#define _SESSION_H

#include "commondef.h"

class ISession
{
public:
	virtual ~ISession () {}
	virtual UINT32_T GetSessionID ( ) const = 0;
	//-------------------------------------------------------
	//�跢�ͻ�����д����
	virtual void Write ( CHAR* buf, UINT32_T len ) = 0;
	//-------------------------------------------------------
	//���ܻ�������ȡ����
	virtual void Read ( CHAR* buf, UINT32_T len ) = 0;
	//-------------------------------------------------------
	//���ͻ���������
	virtual void MessageSent () = 0;
	//-------------------------------------------------------
	//�������ݵ�������
	virtual void MessageReveive () = 0;
};

#endif