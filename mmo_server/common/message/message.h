#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "commondef.h"
#include "bean.h"
#include "session.h"
#include <list>
//////////////////////////////////////////////////////////////////////////
//消息包的定义
using namespace std;

class Message : public Bean
{
public:
    virtual ~Message(){};

	inline void setSendID ( UINT32_T sendID )
    {
        sendID_ = sendID;
    }

	inline UINT32_T getSendID ( )const
    {
        return sendID_;
    }

	inline void addRoleID ( UINT32_T roleID )
    {
        roleID_.push_back(roleID);
    }

	inline list<UINT32_T>& getRoleID ( )const
    {
		return ( list<UINT32_T> & ) roleID_;
    }

    inline void setSession(const ISession& session)
    {
		session_ = (ISession*)&session;
    }

    inline ISession* getSession()const
    {
        return session_;
    }
private:
	UINT32_T          sendID_;
	list<UINT32_T>    roleID_;
    ISession*	    session_;
};

class ReqLoginMessage: public Message
{
public:
	virtual bool Write ( ISession& session )
	{
		WriteChar ( session, ( CHAR* )&id, sizeof( UINT32_T ) );
		WriteString ( session, this->name );
		return true;
	}
	virtual bool Read ( ISession& session )
	{
		ReadChar ( session, ( CHAR* )&id, sizeof( UINT32_T ) );
		ReadString ( session, this->name );
		return true;
	}
public:
	UINT32_T id;
	std::string name;
};


#endif