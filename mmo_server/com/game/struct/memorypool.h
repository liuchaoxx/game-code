#ifndef _MEMORY_POOL_H
#define _MEMORY_POOL_H

#include <list>
#include <queue>
#include "common.h"

using std::list;
using std::queue;

class ICacheObject
{
public:
	virtual void release () = 0;
};
class TCache 
{
public:
	TCache ( uint default_size, uint max_size );
	~TCache ();
	ICacheObject* alloc ();
	void free ( ICacheObject* obj );
private:
	queue<ICacheObject*> free_;
	list<ICacheObject*> using_;
};

TCache::TCache ( uint default_size, uint max_size )
{
}

#endif