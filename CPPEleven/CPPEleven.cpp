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
#include <iterator>


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

struct MyTime
{
	__int64 m_time;
	clock_t m_clock;
};

__int64 get_time( ) 
{
	//return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	time_t temp;
	time(&temp);

	return (__int64)temp;
}

MyTime get_time_ex( )
{
	MyTime temp;

	time( &temp.m_time );
	temp.m_clock = clock( );

	return temp;
}

void rvalue_sorting( );
void rvalue_test( );
void norv_test( );
void uref_test( );
void uref_test2( );
void lambda_test( );
void unordered_map_test( );
void vector_test( );
void list_test( );
void compare_perf( );
void map_multimap_test( );
void map_unord_map_compare( );
void stack_test( );
void type_deduct_test( );


int _tmain(int argc, _TCHAR* argv[])
{
	try
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
		//unordered_map_test( );
		//vector_test( );
		//list_test( );
		//compare_perf( );
		//map_multimap_test( );
		map_unord_map_compare( );
		//stack_test( );
		//type_deduct_test( );

	}
	catch ( std::exception& exc )
	{
		std::cout << "Exception: " << exc.what( ) << std::endl;
	}

	return 0;
}


template <typename> struct TD;
void someFunc( int, double ) {}	// someFunc - function, its type is
								// void( int, double )

void type_deduct_test( )
{
	std::cout << std::endl << "=================== Type deduction =========================" << std::endl;

	auto x = 27;
	const auto cx = x;
	const auto& rx = x;

	/** Universal refernce */
	auto&& uref1 = x;
	auto&& uref2 = cx;
	auto&& uref3 = 27;

	std::cout << typeid(uref1).name( ) << std::endl;

	/** Functions */
	const char name[] =		// name type - const char[13]
		"R. N. Briggs";
	auto arr1 = name;		// arr1 type - const 
	auto& arr2 = name;		// arr2 type - const char (&)[13]

	auto func1 = someFunc;			// func1 type - void (*)(int, double)
	auto& func2 = someFunc;			// func2 type - void (&)(int, double)

//	TD<decltype(arr2)> _;			
}

using SimpleVec = std::vector<SimpleRV>;
using SimpleList = std::list<SimpleRV>;
using SimpleDeque = std::deque<SimpleRV>;

using IntVec = std::vector<int>;
using IntList = std::list<int>;
using IntDeque = std::deque<int>;

void compare_perf( )
{
	std::cout << std::endl << "=================== Compare performance =========================" << std::endl;

	const int cont_size = 100;

	//SimpleVec vector;
	//SimpleList	list;
	//SimpleDeque deque;
	
	///** Filling */
	//__int64 start = get_time( );
	//for ( int i = 0; i < cont_size; ++i )
	//{
	//	SimpleRV temp( "item " + std::to_string( i ) );

	//	/** Vector */
	//	vector.push_back( temp );
	//}
	//__int64 end = get_time( );

	//std::cout << "Vector fill: " << end - start << std::endl;


	//start = get_time( );
	//for ( int i = 0; i < cont_size; ++i )
	//{
	//	SimpleRV temp( "item " + std::to_string( i ) );

	//	/** List */
	//	list.push_back( temp );
	//}
	//end = get_time( );

	//std::cout << "List fill: " << end - start << std::endl;

	//start = get_time( );
	//for ( int i = 0; i < cont_size; ++i )
	//{
	//	SimpleRV temp( "item " + std::to_string( i ) );

	//	/** Deque */
	//	deque.push_back( temp );
	//}
	//end = get_time( );

	//std::cout << "Deque fill: " << end - start << std::endl;

	SimpleVec vector;
	SimpleList list;
	SimpleDeque deque;

	for ( int i = 0; i < cont_size; i++ ) {
		int num = rand( ) % 100000;

		vector.push_back( SimpleRV( "item " + std::to_string( num ) ) );
		list.push_back( SimpleRV( "item " + std::to_string( num ) ) );
		deque.push_back( SimpleRV( "item " + std::to_string( num ) ) );
	}

	/** Sorting */
	MyTime start = get_time_ex( );
	std::sort( vector.begin( ), vector.end( ) );
	MyTime end = get_time_ex( );

	std::cout << "Vector sort. Clock: " << end.m_clock - start.m_clock << ", time: " << end.m_time - start.m_time << std::endl;

	start = get_time_ex( );
	list.sort( );
	end = get_time_ex( );

	std::cout << "List sort. Clock: " << end.m_clock - start.m_clock << ", time: " << end.m_time - start.m_time << std::endl;

	start = get_time_ex( );
	std::sort( deque.begin( ), deque.end( ) );
	end = get_time_ex( );

	std::cout << "Deque sort. Clock: " << end.m_clock - start.m_clock << ", time: " << end.m_time - start.m_time << std::endl;

	IntVec indices;
	for ( int j = 0; j < cont_size; ++j ) 
	{
		if ( j % 3 == 0 )
		{
			indices.push_back( j );
		}
	}

	/** Random access */
	start = get_time_ex( );
	for ( int i : indices )
	{
		SimpleRV& some = vector.at( i );
	}
	end = get_time_ex( );

	std::cout << "Vector random access " << static_cast<int>( indices.size( ) ) << " times. Time: " << end.m_time - start.m_time << ", clock: " << end.m_clock - start.m_clock << std::endl;

	start = get_time_ex( );
	for ( int i : indices )
	{
		auto it = list.begin( );
		std::advance( it, i );
		SimpleRV& i = *it;
	}
	end = get_time_ex( );

	std::cout << "List random access " << static_cast<int>(indices.size( )) << " times.  Time: " << end.m_time - start.m_time << ", clock: " << end.m_clock - start.m_clock << std::endl;

	start = get_time_ex( );
	for ( int i : indices )
	{
		SimpleRV& some = deque.at( i );
	}
	end = get_time_ex( );

	std::cout << "deque random access " << static_cast<int>(indices.size( )) << " times.  Time: " << end.m_time - start.m_time << ", clock: " << end.m_clock - start.m_clock << std::endl;
}

using MyStack = std::stack<int>;

void stack_test( )
{
	std::cout << std::endl << "=================== Stack test =========================" << std::endl;

	MyStack stack;

	/** emplace( ) */
	stack.emplace( 1 );

	std::cout << "Item on top: " << stack.top( ) << std::endl;

	/** push( ) */
	stack.push( 2 );

	std::cout << "Item on top: " << stack.top( ) << std::endl;

	stack.emplace( 3 );
	stack.emplace( 4 );
	stack.emplace( 5 );

	stack.push( 6 );
	stack.push( 7 );
}

using SimpleMap = std::map< std::string, SimpleRV >;
using SimpleMultimap = std::multimap< std::string, SimpleRV >;

void map_multimap_test( )
{
	std::cout << std::endl << "=================== Map multimap test =========================" << std::endl;

	SimpleMap first_map, second_map;
	SimpleMultimap multimap;

	/** filling the first*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "First map size before filling: " << first_map.size( ) << std::endl;
	for ( int i = 0; i < Count; ++i )
	{
		first_map.emplace( std::make_pair( "first key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) ) );
	}
	std::cout << "First map size after filling: " << first_map.size( ) << std::endl;


	/** filling the second*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Second map size before filling: " << second_map.size( ) << std::endl;
	for ( int i = 0; i < Count; ++i )
	{
		second_map.emplace( std::make_pair( "second key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) ) );
	}
	std::cout << "Second map size after filling: " << second_map.size( ) << std::endl;

	/** Multimap filling */
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "Multimap size before filling: " << multimap.size( ) << std::endl;
	for ( int i = 0; i < Count; ++i )
	{
		multimap.emplace( std::make_pair( "first key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) ) );
		multimap.emplace( std::make_pair( "first key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) ) );
	}
	std::cout << "Multimap size after filling: " << multimap.size( ) << std::endl;


	std::cout << "--- Map insert/delete/access methods ---" << std::endl;

	/** count( ) */
	std::cout << "Count( ). First map count of items with \"first key 7\": " << first_map.count( "first key 7" ) << std::endl;

	/** emplace( ) */
	first_map.emplace( std::make_pair( "first key 4.1", SimpleRV( "item 4.1" ) ) );
	std::cout << "Emplace( ). First map count of items with \"first key 4.1\"" << first_map.count( "first key 4.1" ) << std::endl;
	std::cout << "First map size: " << first_map.size( ) << std::endl;

	/** insert( ) */
	SimpleMap::iterator from = second_map.begin( );
	SimpleMap::iterator to = second_map.begin( );
	std::advance( from, 4 );
	std::advance( to, 7 );

	first_map.insert( from, to );
	std::cout << "Insert( ). First map size: " << first_map.size( ) << std::endl;

	/** erase( ) */
	first_map.erase( first_map.begin( ) );
	std::cout << "Erase( ). First map size: " << first_map.size( ) << std::endl;

	/** operator[]( ) */
	//SimpleRV& newVal = first_map["first key 4.1"]; // does not compile because of there is no default constructor available
	
	/** at( ) */
	try
	{
		SimpleRV& newVal = first_map.at("danny");
	}
	catch ( std::out_of_range& exc )
	{
		std::cout << "There is no item with key \"danny\"! " << exc.what( ) << std::endl;
	}

	std::cout << "--- Multimap insert/delete/access methods ---" << std::endl;

	/** emplace( ) */
	std::cout << "Multimap before emplace: " << multimap.size( ) << std::endl;
	multimap.emplace( std::make_pair( "superior key", SimpleRV( "mmap item" ) ) );
	std::cout << "Multimap after emplace: " << multimap.size( ) << std::endl;

	/** insert( ) */
	from = second_map.begin( );
	to = second_map.begin( );
	std::advance( from, 4 );
	std::advance( to, 7 );

	multimap.insert( from, to );
	std::cout << "Multimap after insert: " << multimap.size( ) << std::endl;

	/** erase */
	multimap.erase( "superior key" );
	std::cout << "Multimap after erase: " << multimap.size( ) << std::endl;

	/** equal range */
	std::pair< SimpleMultimap::iterator, SimpleMultimap::iterator > res = multimap.equal_range( "first key 10" );
	
	std::string temp;
	for ( SimpleMultimap::iterator it = res.first; it != res.second; ++it )
	{
		temp += (it->first + ", ");
	}

	std::cout << "Multimap equal range result: " << temp << std::endl;

	/** find( ) */
	MyTime start_time = get_time_ex( );
	SimpleMultimap::iterator found = multimap.find( "first key 500" );
	MyTime end_time = get_time_ex( );

	std::string found_str = found != multimap.end( ) ? found->first : "not found";
	std::cout << "find( ). Found pair is: " << found_str << ", found time: " << end_time.m_time - start_time.m_time << std::endl;

	/** lower_bound( ) */
	start_time = get_time_ex( );
	found = multimap.lower_bound( "first key 500" );
	end_time = get_time_ex( );

	found_str = found != multimap.end( ) ? found->first : "not found";
	std::cout << "lower_bound( ). Found pair is: " << found_str << ", found time: " << end_time.m_time - start_time.m_time << std::endl;
}

void list_test( )
{
	std::cout << std::endl << "=================== List test =========================" << std::endl;

	const int list_size = 500;
	SimpleList list;
	
	// resize( ) is not accessed, when there is no default constructor

	std::cout << "List size: " << list.size( ) << std::endl;
	//list.resize( list_size );
	std::cout << "List size after resize( ): " << list.size( ) << std::endl;

	for ( int i = 0; i < list_size; ++i ) 
	{
		list.push_back( SimpleRV( "list item " + std::to_string( i ) ) );
	}

	;
}

void vector_test( )
{
	std::cout << std::endl << "=================== Vector test =========================" << std::endl;
	
	const int val_count = 1000;
	SimpleVec values;

	// capcity( )
	std::cout << "capacity( ) " << values.capacity( ) << std::endl;

	// reserve( )
	values.reserve( val_count / 2 );

	// capcity( )
	std::cout << "capacity( ) " << values.capacity( ) << std::endl;

	// fill
	__int64 start = get_time( );
	for ( int i = 0; i < val_count; ++i ) {
		values.push_back( SimpleRV( "vec key" + std::to_string( i ) ) );
	}
	__int64 end = get_time( );

	std::cout << val_count << " elements was appended for " << end - start << " seconds." << std::endl;

	// capcity( )
	std::cout << "capacity( ) " << values.capacity( ) << std::endl;

	// second fill
	start = get_time( );
	for ( int i = 0; i < val_count / 2; ++i ) {
		values.push_back( SimpleRV( "other vec key" + std::to_string( i ) ) );
	}
	end = get_time( );

	std::cout << val_count / 2 << " additional elements was appended for " << end - start << " seconds." << std::endl;

	// capcity( )
	std::cout << "capacity( ) " << values.capacity( ) << std::endl;

}

using SimpleUnorderMap = std::unordered_map<std::string, SimpleRV>;
using StrSRvPair = std::pair<std::string, SimpleRV>;

void unordered_map_test( )
{
	std::cout << std::endl << "=================== Unordered_map test =========================" << std::endl;

	const int count = 508;//100;
	SimpleUnorderMap my_map;

	// bucket count
	int bucket_count = my_map.bucket_count( );
	std::cout << "bucket_count( ): " << bucket_count << std::endl;

	// reserve
	std::cout << "reserve()" << std::endl;
	my_map.reserve( count + 2 );

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
		std::string key( "key " + std::to_string( i ) );
		int bucket = my_map.bucket( key );
		std::cout << "\"" << key << "\" is in bucket " << bucket << std::endl;

		buckets.push_back( bucket );
	}
	
	// bucket_cout
	bucket_count = my_map.bucket_count( );
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
	std::pair< SimpleUnorderMap::iterator, SimpleUnorderMap::iterator > range = my_map.equal_range( "key 20" );

	//	unordered_map::hash_function
	SimpleUnorderMap::hasher fn = my_map.hash_function( );
	std::cout << "this " << fn( "this" ) << std::endl;
	std::cout << "bla-bla " << fn( "bla-bla" ) << std::endl;

	//	unordered_map::load_factor
	//	unordered_map::max_bucket_count
	//	unordered_map::max_load_factor
	//	unordered_map::max_size
	std::cout << "size = " << my_map.size( ) << std::endl;
	std::cout << "max_size = " << static_cast< int >( my_map.max_size( ) ) << std::endl;
	std::cout << "bucket_count = " << my_map.bucket_count( ) << std::endl;
	std::cout << "max_bucket_count = " << my_map.max_bucket_count( ) << std::endl;
	std::cout << "load_factor = " << my_map.load_factor( ) << std::endl;
	std::cout << "max_load_factor = " << my_map.max_load_factor( ) << std::endl;

	//	unordered_map::operator=
	//	unordered_map::operator[]
	//	unordered_map::rehash
	//	unordered_map::reserve
	//	unordered_map::size
	//	unordered_map::swap
}

void map_unord_map_compare( )
{
	std::cout << std::endl << "=================== Map vs unordered_map test =========================" << std::endl;

	SimpleMap map;
	SimpleUnorderMap u_map;

	/** filling the first*/
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	MyTime start = get_time_ex( );
	for ( int i = 0; i < Count; ++i )
	{
		map.emplace( std::make_pair( "first key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) ) );
	}
	MyTime end = get_time_ex( );
	std::cout << "Map fill time: " << end.m_clock - start.m_clock << std::endl;

	end = get_time_ex( );
	for ( int i = 0; i < Count; ++i )
	{
		u_map.emplace( std::make_pair( "first key " + std::to_string( i ), SimpleRV( "item " + std::to_string( i ) ) ) );
	}
	end = get_time_ex( );
	std::cout << "Unorder map fill time: " << end.m_clock - start.m_clock << std::endl;

	start = get_time_ex( );
	SimpleRV& map_val = map.at( "first key 800" );
	end = get_time_ex( );
	std::cout << "Map access time: " << end.m_clock - start.m_clock << std::endl;

	start = get_time_ex( );
	SimpleRV& unord_map_val = u_map.at( "first key 800" );
	end = get_time_ex( );
	std::cout << "Unord_map access time: " << end.m_clock - start.m_clock << std::endl;
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

// rvalue testing to the purpose
void rvalue_test( )
{
	SimpleRV test1( "first" );	// constructor

	SimpleVec rvs;
	rvs.reserve( 10 );	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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
	rvs.reserve( 10 );

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