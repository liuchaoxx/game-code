#ifndef _OX_COMMONDEF_H
#define _OX_COMMONDEF_H

#include "platform.h"

///////////////////////////////////////////////////////////////////////
//��׼�������Ͷ���
///////////////////////////////////////////////////////////////////////

typedef char INT8_T;
typedef unsigned char UINT8_T;
typedef short INT16_T;
typedef unsigned short UINT16_T;
typedef long INT32_T;
typedef unsigned long UINT32_T;
typedef long long INT64_T;
typedef unsigned long long UINT64_T;

typedef char CHAR;
typedef unsigned char UCHAR;
typedef short SHORT;
typedef unsigned short USHORT;
typedef int INT;
typedef unsigned int UINT;
typedef long LONG;
typedef unsigned long ULONG;

typedef ULONG			IP_t;

#define MAX_BUFFER_CAPACITY        8192

//����ָ��ֵɾ���ڴ�
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=NULL ) { delete (x); (x)=NULL; }
#endif
//����ָ��ֵɾ�����������ڴ�
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=NULL ) { delete[] (x); (x)=NULL; }
#endif
//����ָ�����free�ӿ�
#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=NULL ) { free(x); (x)=NULL; }
#endif
//����ָ�����Release�ӿ�
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)	if( (x)!=NULL ) { (x)->Release(); (x)=NULL; }
#endif

#ifndef GET_ARRAY_LEN
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}
#endif


//��Ч�ľ��
#define INVALID_HANDLE	-1
//��Ч��IDֵ
#define INVALID_ID		-1


//IP��ַ���ַ���󳤶�
#define IP_SIZE			24
#define KEY_SIZE			64
#define MAX_WORLDCOUNT			256
#define TIMELENTH			23

#define ACCEPT_ONESTEP 50

#endif