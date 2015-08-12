#ifndef _IO_BUFFER_H
#define _IO_BUFFER_H

#include "commondef.h"

class CIOBuffer
{
public:
	CIOBuffer ( UINT32_T capacity );
	~CIOBuffer ();
public:
	bool Write ( CHAR *data, UINT32_T len ); //д�����ݵ�������
	bool Read ( CHAR *buf, UINT32_T len );   //�ӻ�������ȡ����
	bool IsPacketReady ();		   //�ж��Ƿ���Զ�ȡ������
public:
	void PopRef ( CHAR **buf, UINT32_T *len, bool send );
	void flush (UINT32_T len, bool send);
private:
	CHAR*				buf_;
	UINT32_T			head_;
	UINT32_T			tail_;
	UINT32_T			length_;
	UINT32_T			capacity_;
	UINT32_T			check_len_;
};
#endif