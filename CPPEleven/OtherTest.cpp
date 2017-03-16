#include "stdafx.h"
#include "OtherTest.h"
#include "SimpleRV.h"
#include "NoRV.h"
#include "RValueTest.h"

void lambda_test( )
{
	SRValues vals{ SimpleRV( "first" ), SimpleRV( "second" ), SimpleRV( "third" ) };

	std::string name( "third" );
	auto found = std::find_if( vals.begin( ), vals.end( ),
		[&name]( const SimpleRV& some )
	{
		return name == *(some.m_names.cbegin( )) ? true : false;
	}
	);

	if ( found != vals.end( ) ) {
		std::cout << "Found strings" << std::endl;

		[&found]( ) {
			const SimpleRV& obj = *found;

			for ( const auto& x : obj.m_names ) {
				std::cout << x << std::endl;
			}
		}();
	}
}

// rvalue testing to the purpose
void rvalue_test( )
{
	SimpleRV test1( "first" );	// constructor

	SRValues rvs;
	rvs.reserve( 10 );	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	rvs.push_back( std::move( test1 ) );		// move constructor
	rvs.push_back( SimpleRV( "second" ) );	// constructor, move constructor

	SimpleRV test3( "third" );
	rvs.push_back( test3 );					// copy constructor

	SimpleRV test4( "fourth" );				// constructor
	test4 = SimpleRV( "five" );				// constructor, move assignment operator

	test3 = test4;							//
}

void norv_test( )
{
	typedef std::vector<NoRV> NoRvs;

	NoRV test1( "first" );	// constructor

	NoRvs rvs;
	rvs.reserve( 10 );

	rvs.push_back( std::move( test1 ) );		// copy constructor
	rvs.push_back( NoRV( "second" ) );		// constructor, copy constructor

	NoRV test3( "third" );
	rvs.push_back( test3 );					// copy constructor

	NoRV test4( "fourth" );					// constructor
	test4 = NoRV( "five" );					// constructor, assignment operator

	test3 = test4;							// assignment operator
}

/** Universal references and std::forward */
template <typename T>
T get_value( T&& val )
{
	if ( false ) {
		T res = std::forward<T>( val );
		return res;
	}
	else {
		T res = std::move( val );
		return res;
	}
};

void uref_test( )
{
	int test1 = get_value<int>( 4 );

	int num = 8;
	int test2 = get_value<int>( std::forward<int>( num ) );
	int test2_1 = get_value<int>( std::move<int>( int( 10 ) ) );

	SimpleRV test3( "three" );
	SimpleRV res3 = get_value( test3 );

	const SimpleRV test3_1( "three_one" );
	SimpleRV res3_1 = get_value( test3_1 );

	SimpleRV res3_2 = get_value( SimpleRV( "three_two" ) );

	NoRV test4( "four" );
	NoRV res4 = get_value( test4 );

	NoRV res4_1 = get_value( NoRV( "four_one" ) );

	SimpleRV test5( "five" );
	SimpleRV res5 = std::forward<SimpleRV>( test5 );

	NoRV test6( "six" );
	NoRV res6 = std::move( test6 );

	NoRV test7 = test6;
}

/** Universal references and std::forward [2] */
void process( const SimpleRV& some )
{
	return;
}

void process( SimpleRV&& some )
{
	return;
}

template <typename T>
void get_value_2( T&& val )
{
	if ( false ) {
		process( std::move( val ) );
		0 == 1;
		T val1 = std::forward<T>( val );
		0 == 1;
	}
	else {
		process( std::forward<T>( val ) );
		0 == 1;
		T val1 = std::forward<T>( val );
		0 == 1;
		process( std::forward<T>( val ) );
	}
}

void uref_test2( )
{
	std::cout << "get_value2()" << std::endl;

	SimpleRV test1( "first" );
	get_value_2( test1 );

	std::cout << "get_value2()" << std::endl;

	get_value_2( SimpleRV( "second" ) );
}

void rvalue_sorting( )
{
	const int Val_Count = 50;
	RValues rvals;
	rvals.reserve( Val_Count );

	std::cout << "Creating RValues" << std::endl;

	for ( int i = Val_Count - 1; i >= 0; --i )
	{
		rvals.push_back( RValueTest( i ) );
	}

	std::cout << "Sorting RValues" << std::endl;

	time_t start, end;
	time( &start );

	std::sort( rvals.begin( ), rvals.end( ) );

	time( &end );
	std::cout << "Sorting duration " << end - start << std::endl;
}

const int Size = 100;

Strings make_vec( )
{
	Strings local;

	for ( int i = 0; i < Size; ++i )
	{
		local.push_back( "some" );
	}

	return local;
}

void make_vec( Strings& strs )
{
	for ( int i = 0; i < Size; ++i )
	{
		strs.push_back( "some" );
	}
}

void test_1( )
{
	time_t start, end;
	time( &start );
	Strings nums( std::move( make_vec( ) ) );
	time( &end );

	std::cout << "res1 = " << end - start << std::endl;
}

void test_2( )
{
	time_t start, end;

	time( &start );
	Strings nums2 = make_vec( );
	time( &end );

	std::cout << "res2 = " << end - start << std::endl;
}

void test_3( )
{
	time_t start, end;

	Strings strs3;
	time( &start );
	make_vec( strs3 );
	time( &end );

	std::cout << "res3 = " << end - start << std::endl;
}