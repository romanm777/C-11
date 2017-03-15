#include "stdafx.h"
#include "ListMapDequeTest.h"

#include "GetTime.h"

const int Count = 10000;

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

	std::cout << "Vector random access " << static_cast<int>(indices.size( )) << " times. Time: " << end.m_time - start.m_time << ", clock: " << end.m_clock - start.m_clock << std::endl;

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
		SimpleRV& newVal = first_map.at( "danny" );
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