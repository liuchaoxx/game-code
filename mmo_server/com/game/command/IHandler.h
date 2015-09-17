#ifndef _IHANDLER_H
#define _IHANDLER_H

#include "common.h"
#include "ICommand.h"
#include "message.h"

template<class T_OBJ, class T_MSG>
class IHandler : ICommand
{
public:
	uint32 getID () const = 0;
	T_MSG* getMessage ( )const { return message; };
	void setMessage ( T_MSG* message ) { this = message; };
	T_OBJ* getObject ( )const { return this->object; }
	void setObject ( T_OBJ *object ) { this->object = object; }
protected:
	T_MSG* message;
	T_OBJ* object;
};

#endif