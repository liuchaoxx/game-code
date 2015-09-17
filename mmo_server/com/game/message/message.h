#ifndef _MESSAGE_H
#define _MESSAGE_H

#include "common.h"
#include "bean.h"
#include "ISession.h"
#include <list>
//////////////////////////////////////////////////////////////////////////
//消息包的定义
using namespace std;

class Message : public Bean
{
public:
	void setSendID ( uint32 sendID );
	uint32 getSendID ()const;
	void addRoleID ( uint32 roleID );
	list<uint32>& getRoleID ()const;
private:
	uint32          sendID_;
	list<uint32>    roleID_;
};

void Message::setSendID ( uint32 sendID )
{
	sendID_ = sendID;
}

uint32 Message::getSendID ()const
{
	return sendID_;
}

void Message::addRoleID ( uint32 roleID )
{
	roleID_.push_back ( roleID );
}

list<uint32>& Message::getRoleID ()const
{
	return ( list<uint32> & ) roleID_;
}

#endif