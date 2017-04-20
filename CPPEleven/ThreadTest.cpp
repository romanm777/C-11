#include "stdafx.h"
#include "ThreadTest.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <future>

void mutex_test( )
{
	//thread_test( );
	//timed_mutex_test( );
	//lock_guard_test( );
	promice_test( );
	//packaged_task_test( );

	//async_async_test( );
	//*future_test( );
}

const int Count = 100;
const int Middle = Count / 2;

int SomeValue = 0;		// shared resource
CRITICAL_SECTION cs;

int OtherValue = 0;
std::mutex mt;

void first_thread( int* year )
{
	for ( int i = 0; i < Count; ++i )
	{
		std::cout << "First thread." << i << std::endl;
		
		EnterCriticalSection( &cs );
		--SomeValue;
		LeaveCriticalSection( &cs );

		mt.lock( );
		++OtherValue;
		mt.unlock( );
	}

	*year = *year - 1;
	std::cout << "First thread end." << std::endl;
}

void second_thread( )
{
	for ( int i = 0; i < Count; ++i )
	{
		std::cout << "Second thread." << i << std::endl;

		EnterCriticalSection( &cs );
		--SomeValue;
		LeaveCriticalSection( &cs );

		mt.lock( );
		++OtherValue;
		mt.unlock( );
	}

	std::cout << "Second thread end." << std::endl;
}

void thread_test( )
{
	std::cout << "================================ Thread test =================================" << std::endl;

	// init critical section
	InitializeCriticalSection( &cs );

	std::shared_ptr<std::thread> first; 
	std::shared_ptr<std::thread> second;
	int year = 1991;

	for ( int i = 0; i < Count; ++i )
	{
		std::cout << "Main thread " << i << std::endl;

		if ( i == Middle / 2 )
		{
			std::cout << "Middle / 2 has been reached ( i == " << i << ")." << std::endl;
			first = std::shared_ptr<std::thread>( new std::thread( first_thread, &year ) );
		}

		if ( i == Middle )
		{
			std::cout << "Middle has been reached ( i == " << i << ")." << std::endl;
			second = std::shared_ptr<std::thread>( new std::thread( second_thread ) );
		}
	}

	std::cout << "Fist thread joinabling - " << first->joinable( ) << std::endl;
	first->join( );
	std::cout << "Fist thread joinabling - " << first->joinable( ) << std::endl;

	//second->detach( );
	second->join( );

	std::cout << "Main thread end." << std::endl;
	std::cout << "Year is " << year << std::endl;

	// delete critical section
	DeleteCriticalSection( &cs );
	std::cout << "SomeValue is " << SomeValue << std::endl;

	std::cout << "OhterValue is " << OtherValue << std::endl;
}

////////////////////////////////////////// timed_mutex ///////////////////////////////////////
std::timed_mutex mtx;

void fireworks( int i ) {
	// waiting to get a lock: each thread prints "-" every 200ms:
	while ( !mtx.try_lock_for( std::chrono::milliseconds( 1000 ) ) ) {
		std::cout << i /*<< "-"*/;
	}
	// got a lock! - wait for 1s, then this thread prints "*"
	std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
	std::cout << i << "*\n";
	mtx.unlock( );
}

void timed_mutex_test( )
{
	std::cout << "================================ timed_mutex test =================================" << std::endl;

	std::thread threads[5];
	// spawn 10 threads:
	for ( int i = 0; i < 5; ++i )
		threads[i] = std::thread( fireworks, i );

	for ( auto& th : threads ) th.join( );
}

////////////////////////////////////////// std::lock_guard ///////////////////////////////////////
std::mutex lmtx;           // mutex for critical section

void print_thread_id( int id ) {
	lmtx.lock( );
	std::lock_guard<std::mutex> lck( lmtx, std::adopt_lock );
	std::cout << "thread #" << id << '\n';
}

void lock_guard_test( )
{
	std::cout << "================================ lock_guard test =================================" << std::endl;

	std::thread threads[10];
	// spawn 10 threads:
	for ( int i = 0; i<10; ++i )
		threads[i] = std::thread( print_thread_id, i + 1 );

	for ( auto& th : threads ) th.join( );
}

////////////////////////////////////////// std::promice test ///////////////////////////////////////

struct Car
{
	Car( ) {}

	Car( const std::string& mark, const std::string& model, const int year )
		: m_mark( mark )
		, m_model( model )
		, m_year( year )
	{}

	std::string	m_mark;
	std::string m_model;
	int			m_year;
};

void print_int( std::future<Car>& fut ) 
{
	std::cout << "Enter in thread.\n";

	Car& x_car = fut.get( );
	std::cout << "Mark: " << x_car.m_mark << '\n'
				<< "Model: " << x_car.m_model << '\n'
				<< "Year: " << x_car.m_year << '\n';
}

void get_input( std::promise<Car>& input )
{
	Car car;
	std::cout << "Enter car mark: \n";
	std::cin >> car.m_mark;

	std::cout << "Enter car model: \n";
	std::cin >> car.m_model;

	std::cout << "Enter car year: \n";
	std::cin >> car.m_year;

	input.set_value_at_thread_exit( car );

	for ( int i = 0; i < Count * 100; ++i )
	{
	}
}

void promice_test( )
{
	std::cout << "================================ std::promice test =================================" << std::endl;

	Car car( "Opel", "Vectra", 1997 );

	std::promise<Car> prom;                      // create promise
	std::future<Car> fut = prom.get_future( );    // engagement with future

	std::thread th1( print_int, std::ref( fut ) );  // send future to new thread
	std::thread th2( get_input, std::ref( prom ) );
													// (synchronizes with getting the future)
	th1.join( );
	th2.join( );
}

////////////////////////////////////////// std::packaged_task test ///////////////////////////////////////

// count down taking a second for each value:
int countdown( int from, int to ) {
	std::cout << "countdown test has started!\n";

	for ( int i = from; i != to; --i ) {
		std::cout << i << '\n';
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}
	std::cout << "Lift off!\n";
	return from - to;
}

void packaged_task_test( )
{
	std::cout << "================================ packaged_task_test =================================" << std::endl; 

	std::packaged_task<int( int, int )> tsk( countdown );   // set up packaged_task
	std::future<int> ret = tsk.get_future( );            // get future

	std::thread th( std::move( tsk ), 5, 0 );   // spawn thread to count down from 10 to 0

	const int count = 5;
	for ( int i = 0; i < count; ++i )
	{
		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}

	int value = ret.get( );                  // wait for the task to finish and get result

	std::cout << "The countdown lasted for " << value << " seconds.\n";

	th.join( );
}

//////////////////////////////////// std::async test /////////////////////////////////////

void print_ten( char c, int ms ) {
	for ( int i = 0; i<10; ++i ) {
		std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
		std::cout << c;
	}
}

void async_async_test( )
{
	try
	{
		std::cout << "with launch::async:\n";
		std::future<void> foo = std::async( std::launch::async, print_ten, '*', 100 );
		std::future<void> bar = std::async( std::launch::async, print_ten, '@', 200 );

		for ( int i = 0; i<10; ++i )
			std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

		// async "get" (wait for foo and bar to be ready):
		foo.get( );
		bar.get( );
		std::cout << "\n\n";

		std::cout << "with launch::deferred:\n";
		foo = std::async( std::launch::deferred, print_ten, '*', 100 );
		bar = std::async( std::launch::deferred, print_ten, '@', 200 );

		std::chrono::milliseconds span( 4000 );
		std::future_status ret = foo.wait_for( span );

		// deferred "get" (perform the actual calls):
		foo.get( );
		bar.get( );
		std::cout << "End of main thread.\n";
	}
	catch ( std::future_error& err )
	{
		const std::error_code& code = err.code( );
		std::cout << code << std::endl;
	}
}


//////////////////////////////////// std::future test /////////////////////////////////////

// a non-optimized way of checking for prime numbers:
bool is_prime( int x ) {
	for ( int i = 2; i<x; ++i ) if ( x%i == 0 ) return false;
	return true;
}

void future_test( )
{
	// call function asynchronously:
	std::future<bool> fut = std::async( is_prime, 700020007 );

	// do something while waiting for function to set future:
	std::cout << "checking, please wait";
	std::chrono::milliseconds span( 100 );
	while ( fut.wait_for( span ) == std::future_status::timeout )		// waits for future_status::ready
		std::cout << '.';

	bool x = fut.get( );
	bool is_valid = fut.valid( );

	std::cout << "\n700020007 " << ( x ? "is" : "is not" ) << " prime.\n";
}