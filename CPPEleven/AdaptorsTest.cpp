#include "stdafx.h"


using PriorQueue = std::priority_queue<int>;

void priority_queue_test()
{
	std::cout << "=============== Priority_queue test =======================" << std::endl;

	PriorQueue pqueue;

	pqueue.push( 7 );
	pqueue.push( 1 );
	pqueue.push( 2 );
	pqueue.push( 19 );
	pqueue.push( 3 );
	pqueue.push( 0 );
	pqueue.push( 2 );
	pqueue.push( 4 );
	pqueue.push( 2 );
	pqueue.push( 5 );
	pqueue.push( 13 );
	pqueue.push( 8 );

	for ( size_t i = pqueue.size( ); i > 0; --i ) {
		const int& val = pqueue.top( );
		pqueue.pop( );
	}

	std::cout << "Prior queue size is: " << pqueue.size( ) << std::endl;
}