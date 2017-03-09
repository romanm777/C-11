// CPPEleven.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <time.h>
#include "RValueTest.h"
#include "SimpleRV.h"
#include "NoRV.h"
#include <algorithm>
//#include <chrono>
#include <unordered_map>


const int Size = 10000000;

Strings make_vec( );
void make_vec( Strings& strs );

void test_1( );
void test_2( );
void test_3( );

void foo(int& i)
{
	std::cout << "foo(int& i)" << std::endl;
}

void foo(int&& i) 
{
	std::cout << "foo(int&& i)" << std::endl;
}

__int64 get_time( ) 
{
	//return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	time_t temp;
	time(&temp);

	return (__int64)temp;
}

void rvalue_sorting( );
void rvalue_test( );
void norv_test( );
void uref_test( );
void uref_test2( );
void lambda_test( );
void unordered_map_test( );

int _tmain(int argc, _TCHAR* argv[])
{
	//int w = 3;
	//int& x = w;
	//int&& y = 5;

	//decltype(y) z = 4;

	//std::cout << "start" << std::endl;

	////test_2( );
	////test_3( );	
	////test_1( );

	//int i = 4;
	//foo(i);
	//foo(5);

	///** Rvalue test */
	//__int64 start = get_time( );
	//rvalue_test( );
	//__int64 end = get_time( );

	//std::cout << "rvalue_test(): " << end - start << std::endl;

	///** No rvalue test */
	//start = get_time( );
	//norv_test( );
	//end = get_time( );

	//std::cout << "norv_test(): " << end - start << std::endl;

	///** Universal references */
	//uref_test( );
	//uref_test2( );
	//lambda_test( );
	unordered_map_test( );

	return 0;
}

using StrSRvMap = std::unordered_map<std::string, SimpleRV>;
using StrSRvPair = std::pair<std::string, SimpleRV>;

void unordered_map_test( )
{
	StrSRvMap my_map;

	const int count = 100;
	for ( int i = 0; i < count; ++i ) {
		StrSRvPair pair = StrSRvPair( "key " + std::to_string( i ) , SimpleRV( "item " + std::to_string( i ) ) );
		my_map.insert( pair );
	}

	// at()
	std::cout << "at( )" << std::endl;
	try
	{
		const SimpleRV& val = my_map.at( "key 3" );
		std::cout << *val.m_names.begin( ) << std::endl;
	}
	catch ( std::out_of_range& exc )
	{
		std::cout << exc.what() << std::endl;
	}

	// bucket()
	std::cout << "bucket( )" << std::endl;
	std::vector< int > buckets;
	for ( int i = 0; i < count / 10; ++i )
	{
		int bucket = my_map.bucket( "key " + std::to_string( i ) );
		std::cout << bucket << std::endl;

		buckets.push_back( bucket );
	}
	
	// bucket_cout
	int bucket_count = my_map.bucket_count( );
	std::cout << "bucket_count( ): " << bucket_count << std::endl;

	//	unordered_map::bucket_size
	for ( int bucket : buckets )
	{
		std::cout << "bucket_size( ) of bucket " << bucket << ": " << my_map.bucket_size( bucket ) << std::endl;
	}

	//	unordered_map::count
	std::cout << "count( ) of key 34: " << my_map.count( "key 34" ) << std::endl;

	//	unordered_map::emplace
	my_map.emplace( StrSRvPair( "key 27", SimpleRV( "emplace item" ) ) );
	std::cout << "emplace( ): \"key 27\", SimpleRV( \"emplace item\" " << std::endl;
	std::cout << "item with a key \"key 27\" is " << "\"" << *( my_map.at( "key 27" ).m_names.begin( ) ) << "\"" << std::endl;

	my_map.emplace( StrSRvPair( "key 27e", SimpleRV( "emplace item extend" ) ) );
	std::cout << "emplace( ): \"key 27e\", SimpleRV( \"emplace item extend\" " << std::endl;
	std::cout << "item with a key \"key 27\" is " << "\"" << *(my_map.at( "key 27e" ).m_names.begin( )) << "\"" << std::endl;

	//	unordered_map::emplace_hint
	const std::string key( "key 17 emplace_hint" );
	my_map.emplace_hint( my_map.end(), key, SimpleRV( "item 17 emplace_hint" ) );
	std::cout << "item with a key \"" << key << "\" is \"" << *( my_map.at( key ).m_names.begin( ) ) << "\"" << std::endl;

	//	unordered_map::equal_range
	std::pair< StrSRvMap::iterator, StrSRvMap::iterator > range = my_map.equal_range( "key 20" );

	//	unordered_map::erase
	//	unordered_map::find
	//	unordered_map::get_allocator
	//	unordered_map::hash_function
	//	unordered_map::insert
	//	unordered_map::key_eq
	//	unordered_map::load_factor
	//	unordered_map::max_bucket_count
	//	unordered_map::max_load_factor
	//	unordered_map::max_size
	//	unordered_map::operator=
	//	unordered_map::operator[]
	//	unordered_map::rehash
	//	unordered_map::reserve
	//	unordered_map::size
	//	unordered_map::swap
}

void lambda_test( )
{
	SRValues vals { SimpleRV( "first" ), SimpleRV( "second" ), SimpleRV( "third" ) };

	std::string name( "third" );
	auto found = std::find_if( vals.begin( ), vals.end( ), 
			[&name](const SimpleRV& some) 
			{
				return name == *(some.m_names.cbegin()) ? true : false;
			}
	);

	if ( found != vals.end( ) ) {
		std::cout << "Found strings" << std::endl;
		
		[&found]( ) {
			const SimpleRV& obj = *found;

			for ( const auto& x : obj.m_names ) {
				std::cout << x << std::endl;
			}
		}( );
	}
}

void rvalue_test( )
{
	typedef std::vector<SimpleRV> SimpleRvs;

	SimpleRV test1( "first" );	// constructor

	SimpleRvs rvs;
	rvs.push_back( std::move(test1) );		// move constructor
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
	rvs.push_back( std::move(test1) );		// copy constructor
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
	if ( true ) {
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

	for( int i = Val_Count - 1; i >= 0; --i )
	{
		rvals.push_back( RValueTest( i ) );
	}

	std::cout << "Sorting RValues" << std::endl;

	time_t start, end;
	time(&start);

	std::sort( rvals.begin(), rvals.end() );

	time(&end);
	std::cout << "Sorting duration " << end - start << std::endl;
}

Strings make_vec( )
{
	Strings local;

	for(int i = 0; i < Size; ++i)
	{
		local.push_back("some");
	}

	return local;
}

void make_vec( Strings& strs )
{
	for(int i = 0; i < Size; ++i)
	{
		strs.push_back("some");
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