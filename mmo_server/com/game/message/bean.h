#ifndef _BEAN_H
#define _BEAN_H

#include "common.h"
#include "ISession.h"
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////
//普通消息结构的定义
class Bean
{
public:
	virtual bool write ( ISession& session ) = 0;
	virtual bool read ( ISession& session ) = 0;
protected:
	void read_char ( ISession& session, char* val, uint32 len );
	void write_char ( ISession& session, char* val, uint32 len );
	void read_string ( ISession& session, string& val );
	void write_string ( ISession& session, const string& val );
	void read_bean ( ISession& session, Bean& val );
	void write_bean ( ISession& session, Bean& val );
};

void Bean::read_char ( ISession& session, char* val, uint32 len )
{
	session.read ( val, len );
}

void Bean::write_char ( ISession& session, char* val, uint32 len )
{
	session.write ( val, len );
}

void Bean::read_string ( ISession& session, string& val )
{
	uint32 len = 0;
	session.read ( ( char* )&len, sizeof( uint32 ) );
	val.resize ( len );
	session.read ( ( char* )val.c_str (), len );
}

void Bean::write_string ( ISession& session, const string& val )
{
	uint32 len = val.length();
	session.write ( ( char* )&len, sizeof( uint32 ) );
	session.write ( ( char* )val.c_str (), len );
}

void Bean::read_bean ( ISession& session, Bean& val ) 
{ 
	val.read ( session ); 
}

void Bean::write_bean ( ISession& session, Bean& val ) 
{ 
	val.write ( session ); 
}

#endif