#ifndef _PLIST_H
#define _PLIST_H

#include "common.h"

template<class T>
class IList
{
public:
	virtual T* poll() = 0;
	virtual void add (T* obj) = 0;
	virtual void clear () = 0;
	virtual uint size () = 0;
};

template<class T>
struct PNode 
{
	PNode<T>* next_;
	PNode<T>* prev_;
	T* data_;
};

template<class T>
class PList : public IList<T>
{
public:
	PList ();
	virtual ~PList ();
public:
	T* poll ();
	void add ( T* obj );
	void clear ();
	uint size ();
private:
	PNode<T>* phead;
	PNode<T>* ptail;
	uint count_;
};

template<class T>
PList<T>::PList ()
{
	phead = NULL;
	ptail = NULL;
	count_ = 0;
}

template<class T>
PList<T>::~PList ( )
{
	clear ();
}

template<class T>
T* PList<T>::poll ( )
{
	if ( NULL == phead || NULL == ptail )
		return NULL;
	PNode<T>* pnode = phead;
	if (phead == ptail)
		phead = ptail = NULL;
	else
	{
		phead->next_->prev_= ptail;
		ptail->next_ = phead->next_;
		phead = phead->next_;
	}
	T* data_ = pnode->data_;
	delete pnode;
	count_--;
	return data_;
}

template<class T>
void PList<T>::add ( T* obj )
{
	PNode<T> *node_ = new PNode<T> ();
	node_->data_ = obj;
	if ( NULL == phead || NULL == ptail )
	{
		node_->prev_ = node_;
		node_->next_ = node_;
		phead = ptail = node_;
	} else
	{
		ptail->next_ = node_;
		phead->prev_ = node_;
		node_->next_ = phead;
		node_->prev_ = ptail;
		ptail = node_;
	}
	count_++;
}

template<class T>
void PList<T>::clear ()
{
	if ( NULL == phead || NULL == ptail )
		return;

	while (phead == ptail)
	{
		PNode<T>* node_ = phead;
		phead = phead->next_;
		delete node_;
	}

	delete phead;
	count_ = 0;
	phead = ptail = NULL;
}

template<class T>
uint PList<T>::size ()
{
	return count_;
}

#endif