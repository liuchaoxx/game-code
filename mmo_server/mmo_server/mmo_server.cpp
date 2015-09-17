// mmo_server.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "plist.h"
#include<windows.h>

struct Monster 
{
	uint id;
};

int _tmain ( int argc, _TCHAR* argv[] )
{
	IList<Monster> *list = new PList<Monster> ();
	for ( int i = 0; i < 100; i++ )
	{
		Monster *mon = new Monster ();
		mon->id = i;
		list->add ( mon );
		printf ( "list size == %d\n", list->size () );
	}

	Monster *mon = list->poll ();
	while ( mon != NULL )
	{
		printf ( "monster id = %d   list size == %d\n", mon->id, list->size ( ) );
		mon = list->poll ();
	}

	while (true)
	{
		Sleep ( 5000 );
	}
}

