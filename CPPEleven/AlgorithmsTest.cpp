#include "stdafx.h"
#include "AlgorithmsTest.h"
#include "SimpleRV.h"


const int size = 100;

SRValues get_data( )
{
	SRValues vals;

	for ( int i = 0; i < size; ++i )
	{
		vals.push_back( SimpleRV( "Item " + std::to_string( i ) ) );
	}

	return vals;
}

int op_increase( int i ) { return ++i; };

bool myfunction( int i, int j ) {
	return ( i == j );
}

bool my_sort_function( int i, int j ) {
	return ( i == j );
}

bool IsOdd( int i ) { return ( i % 2 ) == 1; }

void algoritms_test( )
{
	std::cout << "================================ Algorithm test =================================" << std::endl;

	SimpleRV::init_id( -2 );

	SRValues vals = get_data( );

	// std::any_of
	bool is_identical = std::all_of( vals.begin( ), vals.end( ), 
		[]( const SimpleRV& item )
	{
		return item.m_id > -1;
	}
	);

	// std::all_of
	bool is_any = std::any_of( vals.begin( ), vals.end( ), 
		[]( const SimpleRV& item )
	{
		return item.m_id == 20;
	}
	);

	// std::for_each
	bool show_id = true;
	std::for_each( vals.begin( ), vals.end( ), 
		[&vals, &show_id]( SimpleRV& item )
	{
		if ( show_id )
		{
			std::cout << "Item ids: " << item.m_id;
			show_id = false;
		}
		else
		{
			std::cout << ", " << item.m_id;
		}
	}
		);

	std::cout << "." << std::endl;

	// std::find_if_not
	{
		SRValues::iterator found = std::find_if_not( vals.begin( ), vals.end( ),
			[]( const SimpleRV& item )
		{
			return item.m_id > 0;
		} );

		// std::find_first_of
		std::vector<int> example = { 4, 9, 1 };
		std::vector<int> for_search = { 5, 7, -3, 0, 11, 2, 10, 9, 12, -3, 0, 11, 2, 10 };	// 9 - [7]

		std::vector<int>::iterator found1 = std::find_first_of( for_search.begin( ), for_search.end( ), example.begin( ), example.end( ) );
	}

	// std::search_n
	{
		int myints[] = { 10, 20, 30, 30, 30, 20, 10, 10, 20 };
		std::vector<int> myvector( myints, myints + 8 );

		// using default comparison:
		std::vector<int>::iterator found2 = std::search_n( myvector.begin( ), myvector.end( ), 2, 30 );
		size_t pos = found2 - myvector.begin( );
	}

	// std::copy_backward
	{
		std::vector<int> myvector1;

		// set some values:
		for ( int i = 1; i <= 5; i++ )
			myvector1.push_back( i * 10 );          // myvector: 10 20 30 40 50

		myvector1.resize( myvector1.size( ) + 3 );  // allocate space for 3 more elements

		std::copy_backward( myvector1.begin( ), myvector1.begin( ) + 4, myvector1.end( ) );

		std::cout << "myvector contains:";
		for ( std::vector<int>::iterator it = myvector1.begin( ); it != myvector1.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}
	
	// std::move
	{
		std::vector<std::string> foo = { "air","water","fire","earth" };
		std::vector<std::string> bar( 4 );

		// moving ranges:
		std::cout << "Moving ranges...\n";
		std::move( foo.begin( ), foo.begin( ) + 2, bar.begin( ) );
		std::move( foo.begin( ), foo.begin( ) + 2, bar.begin( ) );

		std::cout << "foo contains " << foo.size( ) << " elements:";
		std::cout << " (each in an unspecified but valid state)";
		std::cout << '\n';

		int z = 10, y = 4;
		z = std::move( y );

		std::cout << z << ", " << y << std::endl;
	}

	// std::move_backward
	{
		std::string elems[10] = { "air","water","fire","earth" };

		// insert new element at the beginning:
		std::move_backward( elems, elems + 4, elems + 5 );
		elems[0] = "ether";

		std::cout << "elems contains:";
		for ( int i = 0; i<10; ++i )
			std::cout << " [" << elems[i] << "]";
		std::cout << '\n';
	}

	// std::transform
	{
		std::vector<int> foo;
		std::vector<int> bar;

		// set some values:
		for ( int i = 1; i<6; i++ )
			foo.push_back( i * 10 );                         // foo: 10 20 30 40 50

		bar.resize( foo.size( ) );                         // allocate space

		std::transform( foo.begin( ), foo.end( ), bar.begin( ), op_increase );
		// bar: 11 21 31 41 51

		// std::plus adds together its two arguments:
		std::transform( foo.begin( ), foo.end( ), bar.begin( ), foo.begin( ), std::plus<int>( ) );
		// foo: 21 41 61 81 101

		std::cout << "foo contains:";
		for ( std::vector<int>::iterator it = foo.begin( ); it != foo.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::replace
	{
		int myints[] = { 10, 20, 30, 30, 20, 10, 10, 20 };
		std::vector<int> myvector( myints, myints + 8 );            // 10 20 30 30 20 10 10 20

		std::replace( myvector.begin( ), myvector.end( ), 20, 99 ); // 10 99 30 30 99 10 10 99

		std::cout << "myvector contains:";
		for ( std::vector<int>::iterator it = myvector.begin( ); it != myvector.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::unique_copy
	{
		int myints[] = { 10,20,20,20,30,30,20,20,10 };
		std::vector<int> myvector( 9 );                            // 0  0  0  0  0  0  0  0  0

																   // using default comparison:
		std::vector<int>::iterator it;
		it = std::unique_copy( myints, myints + 9, myvector.begin( ) );   // 10 20 30 20 10 0  0  0  0
																		  //                ^

		std::sort( myvector.begin( ), it );                          // 10 10 20 20 30 0  0  0  0
																	 //                ^

																	 // using predicate comparison:
		it = std::unique_copy( myvector.begin( ), it, myvector.begin( ), myfunction );
		// 10 20 30 20 30 0  0  0  0
		//          ^

		myvector.resize( std::distance( myvector.begin( ), it ) );    // 10 20 30

																	  // print out content:
		std::cout << "myvector contains:";
		for ( it = myvector.begin( ); it != myvector.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::rotate_copy
	{
		int myints[] = { 10,20,30,40,50,60,70 };

		std::vector<int> myvector( 7 );

		std::rotate_copy( myints, myints + 3, myints + 7, myvector.begin( ) );

		// print out content:
		std::cout << "myvector contains:";
		for ( std::vector<int>::iterator it = myvector.begin( ); it != myvector.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::is_partitioned
	{
		std::array<int, 7> foo = { 1,2,3,4,5,6,7 };

		// print contents:
		std::cout << "foo:"; for ( int& x : foo ) std::cout << ' ' << x;
		if ( std::is_partitioned( foo.begin( ), foo.end( ), IsOdd ) )
			std::cout << " (partitioned)\n";
		else
			std::cout << " (not partitioned)\n";

		// partition array:
		std::partition( foo.begin( ), foo.end( ), IsOdd );

		// print contents again:
		std::cout << "foo:"; for ( int& x : foo ) std::cout << ' ' << x;
		if ( std::is_partitioned( foo.begin( ), foo.end( ), IsOdd ) )
			std::cout << " (partitioned)\n";
		else
			std::cout << " (not partitioned)\n";
	}

	// std::partial_sort
	{
		int myints[] = { 9,8,7,6,5,4,3,2,1 };
		std::vector<int> myvector( myints, myints + 9 );

		// using default comparison (operator <):
		std::partial_sort( myvector.begin( ), myvector.begin( ) + 5, myvector.end( ) );

		// using function as comp
		std::partial_sort( myvector.begin( ), myvector.begin( ) + 5, myvector.end( ), my_sort_function );

		// print out content:
		std::cout << "myvector contains:";
		for ( std::vector<int>::iterator it = myvector.begin( ); it != myvector.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::is_sorted_until
	{
		std::array<int, 4> foo { 2,4,1,3 };
		std::array<int, 4>::iterator it;

		it = std::is_sorted_until( foo.begin( ), foo.end( ) );

		std::cout << "Is sorted to: " << *it << std::endl;
	}

	// std::nth_element
	{
		std::vector<int> myvector;

		// set some values:
		for ( int i = 1; i<20; i += 2 ) myvector.push_back( i );   // 1 2 3 4 5 6 7 8 9

		std::random_shuffle( myvector.begin( ), myvector.end( ) );

		// using default comparison (operator <):
		std::nth_element( myvector.begin( ), myvector.begin( ) + 5, myvector.end( ) );

		// using function as comp
		std::nth_element( myvector.begin( ), myvector.begin( ) + 5, myvector.end( ), my_sort_function );

		// print out content:
		std::cout << "myvector contains:";
		for ( std::vector<int>::iterator it = myvector.begin( ); it != myvector.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::lower_bound, std::upper_bound
	{
		int myints[] = { 10,20,30,30,20,10,10,20 };
		std::vector<int> v( myints, myints + 8 );           // 10 20 30 30 20 10 10 20

		std::sort( v.begin( ), v.end( ) );                // 10 10 10 20 20 20 30 30

		std::vector<int>::iterator low, up;
		low = std::lower_bound( v.begin( ), v.end( ), 20 );
		up = std::upper_bound( v.begin( ), v.end( ), 20 );

		std::cout << "Range: 10 10 10 20 20 20 30 30. Lower_bound of 21: " << *low << std::endl;
		std::cout << "Range: 10 10 10 20 20 20 30 30. Upper_bound of 21: " << *up << std::endl;
	}

	// std::set_union
	{
		int first[] = { 5,10,15,20,25 };
		int second[] = { 50,40,30,20,10 };
		std::vector<int> v( 10 );                      // 0  0  0  0  0  0  0  0  0  0
		std::vector<int>::iterator it;

		std::sort( first, first + 5 );     //  5 10 15 20 25
		std::sort( second, second + 5 );   // 10 20 30 40 50

		it = std::set_union( first, first + 5, second, second + 5, v.begin( ) );
		// 5 10 15 20 25 30 40 50  0  0
		v.resize( it - v.begin( ) );                      // 5 10 15 20 25 30 40 50

		std::cout << "The union has " << ( v.size( ) ) << " elements:\n";
		for ( it = v.begin( ); it != v.end( ); ++it )
			std::cout << ' ' << *it;
		std::cout << '\n';
	}

	// std::make_heap, push_heap, pop_heap
	{
		int myints[] = { 10,20,30,5,15 };
		std::vector<int> v( myints, myints + 5 );

		std::make_heap( v.begin( ), v.end( ) );
		std::cout << "initial max heap   : " << v.front( ) << '\n';

		std::pop_heap( v.begin( ), v.end( ) ); v.pop_back( );
		std::cout << "max heap after pop : " << v.front( ) << '\n';

		v.push_back( 99 ); std::push_heap( v.begin( ), v.end( ) );
		std::cout << "max heap after push: " << v.front( ) << '\n';

		std::sort_heap( v.begin( ), v.end( ) );

		std::cout << "final sorted range :";
		for ( unsigned i = 0; i<v.size( ); i++ )
			std::cout << ' ' << v[i];

		std::cout << '\n';
	}

	
	std::cout << "End of test." << std::endl;
}