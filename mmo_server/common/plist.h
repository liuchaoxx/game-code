#ifndef _PLIST_H
#define _PLIST_H

#include "commondef.h"

struct PListNode
{
	PListNode *next;
	PListNode *prev;
};

class PList: public PListNode
{
public:
	PList ()
	{
		Init ();
	}

	bool Empty ()
	{
		return this->prev == this;
	}

	void Init ()
	{
		this->next = this;
		this->prev = this;
		this->count = 0;
	}

	void Add ( PListNode *node )
	{
		this->next->prev = node ;
		node->next = this->next ;
		node->prev = this ;
		this->next = node;
		this->count++;
	}

	void AddTail ( PListNode *node )
	{
		PListNode *p = prev;
		this->prev = node ;
		node->next = this ;
		node->prev = p ;
		p->next = node ;
		count++;
	}

	void Remove ( PListNode *node )
	{
		node->prev->next = node->next;
		node->next->prev = node->prev ;
		node->prev = NULL;
		node->next = NULL;
		count--;
	}

	PListNode* Pop ()
	{
		if ( prev == this )
			return NULL;

		PListNode *node = this->next;
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->prev = NULL;
		node->next = NULL;
		count--;

		return node;
	}

	void AddListTail ( PList *list )
	{
		if ( list->next == list )
			return;

		PListNode *first = list->next;
		PListNode *last = list->prev;
		PListNode *at = this->prev;

		at->next = first;
		first->prev = at;

		this->prev = last;
		last->next = this;

		this->count += list->count;
		list->Init ();
	}
private:
	UINT32_T count;
};

#endif