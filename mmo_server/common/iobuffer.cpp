#include "iobuffer.h"
#include <string.h>

CIOBuffer::CIOBuffer ( UINT32_T capacity )
{
	capacity_ = capacity;
	buf_ = new CHAR[capacity_];
	head_ = 0;
	tail_ = 0;
	length_ = 0;
	check_len_ = 0;
}


CIOBuffer::~CIOBuffer ()
{
	SAFE_DELETE_ARRAY ( buf_ );
}

bool CIOBuffer::Write ( CHAR* data, UINT32_T len )
{
	UINT32_T curtail = tail_;
	UINT32_T cursize = head_ >= curtail ? ( capacity_ - head_ + curtail - 1 ) : curtail - head_ - 1;
	if ( cursize < len )
	{
		return false;
	}

	UINT32_T curtailsize = capacity_ - head_;
	if ( curtailsize > len )
	{
		memcpy ( &buf_[head_], data, len );
	} else
	{
		memcpy ( &buf_[head_], data, curtailsize );
		memcpy ( &buf_[0], data + curtailsize, len - curtailsize );
	}

	head_ += len;
	head_ %= capacity_;
	return true;
}

bool CIOBuffer::Read ( CHAR* bufptr, UINT32_T len )
{
	UINT32_T curhead = head_;
	UINT32_T cursize = curhead >= tail_ ? curhead - tail_ : capacity_ - tail_ + curhead;
	if ( len > cursize )
		return false;

	UINT32_T curtailsize = capacity_ - tail_;
	if ( curtailsize > len )
	{
		memcpy ( bufptr, &buf_[tail_], len );
	} else
	{
		memcpy ( bufptr, &buf_[tail_], curtailsize );
		memcpy ( bufptr + len - curtailsize, &buf_[0], len - curtailsize );
	}

	tail_ += len;
	tail_ %= capacity_;
	return true;
}

bool CIOBuffer::IsPacketReady ()
{
	if ( check_len_ == 0 )
	{
		if ( Read ( ( CHAR* )&this->check_len_, sizeof( UINT32_T ) ) )
		{
			return false;
		}
	}
	UINT32_T curhead = head_;
	UINT32_T cursize = curhead >= tail_ ? curhead - tail_ : capacity_ - tail_ + curhead;
	return check_len_ >= cursize;
}

void CIOBuffer::PopRef ( CHAR **buf, UINT32_T *len, bool send )
{
	if ( send )
	{
		UINT32_T curhead = head_;
		UINT32_T cursize = curhead >= tail_ ? curhead - tail_ : capacity_ - tail_ + curhead;
		*len = 0;
		if ( cursize > 0 )
		{
			*len = curhead > tail_ ? curhead - tail_ : capacity_ - tail_;
			*buf = &buf_[tail_];
		}
	} else
	{
		UINT32_T curtail = tail_;
		UINT32_T cursize = head_ >= curtail ? ( capacity_ - head_ + curtail - 1 ) : curtail - head_ - 1;
		*len = 0;
		if ( cursize > 0 )
		{
			*len = curtail > head_ ? curtail - head_ - 1 : capacity_ - head_;
			*buf = &buf_[head_];
		}
	}
}

void CIOBuffer::flush ( UINT32_T len, bool send )
{
	if ( send )
	{
		UINT32_T curhead = head_;
		UINT32_T flen = curhead > tail_ ? curhead - tail_ : capacity_ - tail_;
		if ( flen >= len)
		{
			tail_ += len;
		}
	} else
	{
		UINT32_T curtail = tail_;
		UINT32_T flen = curtail > head_ ? curtail - head_ - 1 : capacity_ - head_;
		if ( flen >= len )
		{
			head_ += len;
		}
	}
}