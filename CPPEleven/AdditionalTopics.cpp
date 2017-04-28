#include "stdafx.h"
#include "AdditionalTopics.h"
#include "windows.h"
#include "psapi.h"
#include "stdlib.h"
#include <algorithm>
#include <memory>
#include <functional>

bool enable_bpoint = false;

void additional_topics( )
{
	// placement new
	//placement_new_test( );

	// try catch constructor
	try_catch_ctor_dtor_test( );

	// virtual template methods test
	virtual_template_methods_test( );

	// lambda test
	lambda_save_test( );

	// move new test
	move_new_test( );

	// default test
	default_test( );

	// iterators test
	iterators_test( );

	// type info test
	type_info_test( );

	// slicing test
	slicing_test( );
}

////////////////////////////////////
///		work functions

class A
{
public:
	A( )
	{
		;
	}

	A( double digit )
		: m_digit( digit )
	{
	}

	A& operator=( const A& a )
	{
		m_digit = a.get_digit( );

		return *this;
	}

	~A( )
	{
		std::cout << "Dtor run get_digit( ): " << get_digit( ) << "\n";
	}

	double get_digit( ) const
	{
		return m_digit;
	}

private:
	double m_digit;
};

void placement_new_test( )
{
	std::cout << "============================================= placement new test ======================================================\n";

	A a1( 1.0 );
	int size = sizeof( a1 );

	A a2 = a1;
	
	A a3;
	a3 = a1;

	enable_bpoint = false;

	{
		PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo( GetCurrentProcess( ), ( PROCESS_MEMORY_COUNTERS* )&pmc, sizeof( pmc ) );
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

		std::cout << "before placement new: " << physMemUsedByMe << std::endl;

		const int count = 30;

		/////////////////////////////////////////////////////////////
		// placement new
		A* memory = ( A* ) malloc( sizeof( A ) * count );

		std::vector<A*>	pa_vec;

		for ( int i = 0; i < count; ++i )
		{	
			A* pa = nullptr;
			{
				pa = new( memory + i ) A( i );
				double digit = pa->get_digit( );
				std::cout << i << " is allocated.\n";

				// delete pa; - does not free memory and run destructor
				//pa->~A( );

				pa_vec.push_back( pa );
			}
		}

		{
			PROCESS_MEMORY_COUNTERS_EX pmc;
			GetProcessMemoryInfo( GetCurrentProcess( ), ( PROCESS_MEMORY_COUNTERS* )&pmc, sizeof( pmc ) );
			SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

			std::cout << "during placement new: " << physMemUsedByMe << std::endl;
		}

		std::for_each( pa_vec.begin( ), pa_vec.end( ), []( A*& pa )
		{
			pa->~A( );
		} );

		pa_vec.clear( );

		free( memory );
	}

	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo( GetCurrentProcess( ), ( PROCESS_MEMORY_COUNTERS* )&pmc, sizeof( pmc ) );
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;

	std::cout << "after placement new: " << physMemUsedByMe << std::endl;
	std::cout << "The end.\n";
}



/////////////////////////////////////////////////////////////////////////////////////
///////////////////////		try catch and constructor	/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class MyExcept : public std::exception
{
public:
	MyExcept( const char* message )
	{
		m_message = message;
	}

	virtual const char* what( ) const throw( )
	{
		return m_message;
	}

	virtual ~MyExcept( ) throw( ) {}

private:
	const char* m_message;
};

//////////////////////////////////////////////////////////////
const int pa_count = 1000;

int init( )
{
	throw MyExcept( "My exception occured...\n" );
	return 0;
}


class TestExcept 
{
public:
	TestExcept( )
		try : m_digit( 4.0 )
	{
		m_as = std::shared_ptr< A >( new A( 7.0 ) );

		m_int = init( );
	}
	catch ( MyExcept& exc )
	{
		std::cout << exc.what( );
	}

	~TestExcept( )
	{
		try
		{
			throw MyExcept( "Exception in dtor.\n" );
		}
		catch ( MyExcept& exc )
		{
			std::cout << exc.what( );
		}
	}

	int get_int( ) { return m_int; }

private:
	double	m_digit = 0.0;
	std::shared_ptr<A>	m_as = nullptr;
	int		m_int = 0;
};

void try_catch_ctor_dtor_test( )
{
	std::cout << "============================================= try cathc and constructor test ======================================================\n";

	try
	{
		TestExcept test;
		std::cout << "my_int is equal to " << test.get_int( ) << "\n";
	}
	catch ( MyExcept& exc )
	{
		std::cout << exc.what( ) << "\n";
	}

	std::cout << "End of try_catch_ctor_dtor_test( ).\n";

	//double digit = global_pa->get_digit( );
	//std::cout << "Digit is " << digit << "\n";
}



/////////////////////////////////////////////////////////////////////////////////////
///////////////////////		virtual template methods	/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class Common
{
public:
	template <typename T, typename U>
	void some_method( T& val, U other, bool is_true )
	{
		std::cout << "val is " << val << ", other is " << other << std::endl;
	}

	template <typename U>
	void some_method( double& val, U other, bool is_true )
	{
		std::cout << "Double spec. val is " << val << ", other is " << other << std::endl;
	}

	template <>
	void some_method<double, int>( double& val, int other, bool is_true )
	{
		std::cout << "Double spec. val is " << val << ", other is " << other << std::endl;
	}

	template <typename U>
	void some_method( std::string& val, U other, bool is_true )
	{
		std::cout << "String spec. both values is " << val << " and " << other << std::endl;
	}
};

template <typename T, typename U>
void some_func( const T& t, const U& u ) { std::cout << "<typename T, typename U> void some_func( const T& t, const U& u ) { }\n"; }

//template <typename U>
//void some_func<double, U>( const double& t, const U& u ) { std::cout << "<typename U> void some_func( const double& t, const U& u ) { }\n"; }

template <>
void some_func<double, int>( const double& t, const int& u ) { std::cout << "<> void some_func( const double& t, const int& u ) { }\n"; }

void virtual_template_methods_test( )
{
	std::cout << "============================================= virtual template methods ======================================================\n";

	Common obj;
	
	double val = 3.0;
	obj.some_method<double, int>( val, 4, false );
	obj.some_method( val, 4, false );

	std::string str = "My string";
	obj.some_method( str, 5, true );

	// functions
	// In the case of a functon template or member function template, 
	// only FULL specialization is allowed by the C++ standard
	std::string str1 = "string";
	int ival = 9;
	some_func( str1, ival );
	some_func( val, ival );
	some_func<double, int>( val, ival );
}

/////////////////////////////////////////////////////////////////////////////////////
///////////////////////			lambda test				/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

struct TestStruct
{
	std::string m_str = "TestStruct";
};

std::function <double( double, double )> get_lambda( )
{
	std::vector<double> doubles { 4.0, 11.0, 10.0, 2.0, 3.0, 8.0, 15.0 };
	double x = 17.0;
	double* px = &x;
	TestStruct ts;

	return [=]( double val1, double val2 )
	{
		std::string str = ts.m_str + " lambda";

		*px = 21.0;
		return *px + doubles[2] + val1 + val2;
	};
}

///////////////////////////////////////////////////////////////////////////////////
using Ints = std::deque<int>;
using Lambda = std::function<int( )>;

Lambda get_lambda2( Ints& ints )
{
	return [&ints]( )
	{
		return ints[4];
	};
}

Lambda get_lambda1( Ints& ints )
{
	return get_lambda2( ints );
}

class LambdaUser
{
public:
	LambdaUser( Lambda& lambda, std::string& str )
		: m_lambda( std::forward< Lambda >( lambda ) )
		, m_str( std::forward< std::string >( str ) )
	{

	}

	Lambda get_lambda( )
	{
		return m_lambda;
	}

private:
	Lambda m_lambda;
	std::string m_str;
};


void lambda_save_test( )
{
	std::cout << "============================================= lambda test test ======================================================\n";

	std::function< double( double, double ) > out_lambda = get_lambda( );
	
	double res1 = out_lambda( 7.0, 7.0 );
	std::cout << "Result of lambda: " << res1 << std::endl;

	// test capture by reference
	Ints ints { 4, 11, 10, 2, 3, 8, 15 };
	Lambda lambda2 = get_lambda1( ints );

	int res2 = lambda2( );

	std::cout << "Result of lambda2: " << res2 << std::endl;

	////////////////////////////////////////////////////////////////
	// test lambda as class member
	std::string str( "my string" );
	LambdaUser user( get_lambda1( ints ), str );

	int res3 = user.get_lambda( )( );

	std::cout << "Result of user.get_lambda( )( ) " << res3 << std::endl;


	////////////////////////////////
	// test lambda with auto
	auto lambda3 = user.get_lambda( );
	auto& lambda4 = [=]( ) -> int
	{
		return res3 * 2;
	};
}


/////////////////////////////////////////////////////////////////////////////////////
///////////////////////			move new test			/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

using IntVec = std::vector<int>;

class Move
{
public:
	Move( )
	{
		m_ints = new IntVec( { 4, 7, 9, 2, 5 } );
	}

	Move( Move&& move )
	{
		// or m_ints = std::move( move.m_ints );
		std::swap( m_ints, move.m_ints );
		move.m_ints = nullptr;
	}

	Move& operator=( Move&& move )
	{
		if ( this != &move )
		{
			delete m_ints;
			m_ints = move.m_ints;
			move.m_ints = nullptr;
		}

		return *this;
	}

	virtual ~Move( )
	{
		delete m_ints;
	}

private:
	IntVec*	m_ints = nullptr;
};

void move_new_test( )
{
	std::cout << "============================================= move_new_test ======================================================\n";

	Move m1;
	Move m2 = std::move( m1 );

	std::cout << "End move new test.\n";
}


/////////////////////////////////////////////////////////////////////////////////////
///////////////////////			default test			/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


class DefClass
{
public:
	DefClass( ) = default;
	DefClass( const DefClass& dc ) = default;
//	{
//		m_str = dc.m_str;
//	}

	DefClass& operator=( const DefClass& dc ) = default;
//	{
//		m_str = dc.m_str;
//	}

	DefClass( DefClass&& dc )// = default;
	{
		m_str = std::move( dc.m_str );
	}

	DefClass& operator=( DefClass&& dc )// = default;
	{
		return *this;
	}

	~DefClass( ) = default;
//	{
//		;
//	}

	DefClass( const std::string& str )
		: m_str( std::move( str ) )
	{
	}

private:
	int get_int( ) const { return 4; }
	std::string m_str;
};

void default_test( )
{
#if defined( _DEBUG )
	enable_bpoint = false;
#endif

	DefClass dc( std::string( "some str" ) );
	//DefClass dc1 = dc;
	DefClass dc2 = std::move( DefClass( std::string( "Move me1!" ) ) );
	DefClass dc3 = std::move( DefClass( std::string( "Move me2!" ) ) );
	DefClass dc4 = std::move( dc2 );
	dc4 = DefClass( std::string( "Move me2!" ) );
}


/////////////////////////////////////////////////////////////////////////////////////
///////////////////////			iterators test			/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

void iterators_test( )
{
	std::cout << "====================================== iterators test ===============================================\n";

	Ints ints { 4, 7, 9 };
	Ints::iterator it = ints.begin( );
	
	int val1 = *it++ = 3;
	int val2 = *++it = 6;
	int val3 = *it;

	//////////////////////////////////////////////
	Ints ints1 { 4, 7, 9 };

	Ints::iterator begin = ints1.begin( );
	Ints::iterator end = ints1.end( );

	__int64 dist = begin - end;
	Ints::iterator it2 = begin + 1;
	int val4 = it2[0];
	int val5 = it2[1];

	//////////////////////////////
	__int64 dist1 = std::distance( begin, it2 );

	// back_insert_iterator
	std::back_insert_iterator< std::deque< int > > bit( ints1 );
	std::copy( ints1.begin( ), ints1.end( ), bit );

	// list back_inserter
	std::list< int > ilist { 4, 7, 3, 0 };
	std::back_insert_iterator< std::list< int > > lbit( ilist );
	std::copy( ints1.begin( ), ints1.end( ), lbit );

	// front_insert_iterator
	Ints ints2 { 11, 12, 13, 14 };
	std::front_insert_iterator< std::deque< int > > fit( ints1 );
	std::copy( ints2.begin( ), ints2.end( ), fit );

	// back_inserter
	Ints ints3, ints3_1;
	std::copy( ints2.begin( ), ints2.end( ), std::back_inserter( ints3 ) );
	std::replace_copy( ints2.begin( ), ints2.end( ), std::back_inserter( ints3_1 ), 12, 120 );

	// front_inserter
	std::copy( ints2.begin( ) + 1, ints2.begin( ) + 3, std::front_inserter( ints3 ) );

	// inserter
	Ints ints4 { 77, 78, 79, 80 };
	std::copy( ints4.begin( ), ints4.end( ), std::inserter( ints3, ints3.begin( ) + 2 ) );

	// insert_iterator
	std::insert_iterator< Ints > ii( ints3, ints3.end( ) );
	std::copy( ints4.begin( ), ints4.begin( ) + 1, ii );

	// reverse_iterator ( random-access iterator )
	using ints_it_type = Ints::iterator;
	std::reverse_iterator< ints_it_type > rev_it = ints4.rbegin( );
	int val6 = rev_it[1];

	// istream_iterator ( input iterator )
	std::cout << "Enter double:\n";
	std::istream_iterator< double > eos;
/*	std::istream_iterator< double > iit( std::cin );

	double val_d = 0.0;
	if ( iit != eos )
	{
		val_d = *iit;
		iit++;
	}
*/
	// ostream_iterator ( output iterator )
	std::ostream_iterator<int> out_it( std::cout, ", " );
	std::copy( ints4.begin( ), ints4.end( ), out_it );

	// istreambuf_iterator ( input iterator )
	std::istreambuf_iterator< char > isb_eos;
	std::istreambuf_iterator< char > isb_it( std::cin.rdbuf( ) );
	std::string my_str;

	std::cout << "Enter your name: ";

	/*while ( isb_it != isb_eos && *isb_it != '\n' )
	{
		my_str += *isb_it;
		isb_it++;
	}*/

	std::cout << "The name is " << my_str << ".\n";

	// ostreambuf_iterator ( output iterator )
	std::string my_str1( "Some text here...\n" );
	std::ostreambuf_iterator< char > out_it1( std::cout );

	std::copy( my_str1.begin( ), my_str1.end( ), out_it1 );

	// move iterator ( adaptor )
	Ints ints5( 7 );
	using It = Ints::iterator;
	std::copy( std::move_iterator< It >( ints4.begin( ) ), std::move_iterator< It >( ints4.end( ) ), ints5.begin( ) );

	std::cout << "Ints5 after moving elements: ";
	std::copy( ints5.begin( ), ints5.end( ), std::ostream_iterator< int >( std::cout, ", " ) );

	// make move iterator ( adaptor )
	Ints ints6( 10 );
	std::copy( std::make_move_iterator( ints4.begin( ) ), std::make_move_iterator( ints4.end( ) ), ints6.begin( ) );
	
	std::cout << "Ints6 after make_move_iterator on its elements: "; 
	std::copy( ints6.begin( ), ints6.end( ), std::ostream_iterator< int >( std::cout, ", " ) );
}


/////////////////////////////////////////////////////////////////////////////////////
///////////////////////			type info test			/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class A1
{
public:
	virtual ~A1( ) {}

	virtual void super( ) const { std::cout << "A1\n"; }
};

class B1 : public A1
{
public:
	virtual ~B1( ) {}

	virtual void super( ) const { std::cout << "B1\n"; }
};

class C1
{
public:
	virtual ~C1( ) {}

	virtual void super( ) const { std::cout << "C1\n"; }
};

void type_info_test( )
{
	std::cout << "====================================== type info test ===============================================\n";

	bool a_before_b = typeid( A1 ).before( typeid( HeaderClass ) );
	bool hash_equal = typeid( A1 ).hash_code( ) == typeid( B1 ).hash_code( );

	std::cout << "A before B: " << ( a_before_b ? "true" : "false" ) << std::endl;
	std::cout << "Name of class is \"" << typeid( HeaderClass ).name( ) << "\"\n";
	
	try
	{
		B1 b;
		A1* pa = &b;
		B1* pb = dynamic_cast< B1* >( pa );

		std::cout << "Nullptr pointer name is : " << typeid( *pb ).name( ) << ".\n";
	}
	// !!! exception is thrown only for polymorphic classes !!!
	catch ( std::exception& exc )
	{
		std::cout << exc.what( ) << std::endl;
	}
}


/////////////////////////////////////////////////////////////////////////////////////
///////////////////////			slicing test			/////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

class A2
{
public:
	A2( const std::string& str ) : m_str( str )	{}

	void show_str( ) const { std::cout << m_str << std::endl; }

private:
	std::string	m_str;
};

class B2 : public A2
{
public:
	B2( const std::string& der, const std::string& base ) : A2( base ), m_str2( der ) {}

	void show_str( ) const 
	{ 
		std::cout << m_str2; 
		A2::show_str( ); 
	}

private:
	std::string m_str2;
};

void some( A2 a1 )
{
	a1.show_str( );
}

void slicing_test( )
{
	std::string name_der( "object B2"), name_base( "obj A2" );
	B2 one( name_der, name_base );
	A2* pa = &one;

	// slicing #1
	some( *pa );
	std::cout << "-----------------------------\n";

	// slicing #2
	B2 another( "another B2", "another A2" );
	A2& a2 = one;
	a2 = another;

	a2.show_str( );
}