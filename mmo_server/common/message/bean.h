#ifndef _BEAN_H
#define _BEAN_H

#include "commondef.h"
#include "session.h"
#include <string>

//////////////////////////////////////////////////////////////////////////
//普通消息结构的定义
class Bean
{
public:
	virtual ~Bean ( void )
	{
	};
	virtual bool Write ( ISession& session ) = 0;
	virtual bool Read ( ISession& session ) = 0;
protected:
	inline void ReadChar ( ISession& session, CHAR* val, UINT32_T len )
	{
		session.Read ( val, len );
	}

	inline void WriteChar ( ISession& session, CHAR* val, UINT32_T len )
	{
		session.Write ( val, len );
	}

	inline void ReadString ( ISession& session, std::string& val )
	{
		UINT32_T len = 0;
		session.Read ( ( CHAR* )&len, sizeof( UINT32_T ) );
		val.resize ( len );
		session.Read ( ( CHAR* )val.c_str ( ), len );
	}

	inline void WriteString ( ISession& session, const std::string& val )
	{
		UINT32_T len = strlen ( val.c_str () );
		session.Write ( ( CHAR* )&len, sizeof( UINT32_T ) );
		session.Write ( ( CHAR* )val.c_str ( ), len );
	}

	inline void ReadBean ( ISession& session, Bean& val )
	{
		val.Read ( session );
	}

	inline void Writebean ( ISession& session, Bean& val )
	{
		val.Write ( session );
	}
};

#endif