#include "stdafx.h"
#include "TypeDeductionTest.h"

template <typename> struct TD;
void someFunc( int, double ) {}	// someFunc - function, its type is
								// void( int, double )

void foo( int& i )
{
	std::cout << "foo(int& i)" << std::endl;
}

void foo( int&& i )
{
	std::cout << "foo(int&& i)" << std::endl;
}

void show_red_color( )
{
	std::cout << "Red" << std::endl;
}

void show_black_color( )
{
	std::cout << "Black" << std::endl;
}

template <typename T>
void foo_t1( T param )
{
	param = show_black_color;
	std::cout << "foo_t1 param type: " << typeid( param ).name( ) << std::endl;
}

template <typename T>
void foo_t2( T&& param )
{
	param = show_black_color;
	std::cout << "foo_t2 param type: " << typeid( param ).name( ) << std::endl;
}

template <typename T>
void foo_t3( T& param )
{
	param = show_black_color;
	std::cout << "foo_t3 param type: " << typeid( param ).name( ) << std::endl;
}

std::string MyStr = "my string";
const std::string& get_str( ) { return MyStr; }

template <typename T>
void change_str( T str ) 
{
	str = "your string";
}

void type_deduct_test( )
{
	std::cout << std::endl << "=================== Template type deduction =========================" << std::endl;

	void( *func1 )( ) = show_red_color;
	void( *func2 )( ) = show_red_color;
	void( *func3 )( ) = show_red_color;

	foo_t1( func1 );
	foo_t2( func2 );
	foo_t3( func3 );

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::cout << std::endl << "=================== Auto type deduction =========================" << std::endl;

	change_str( get_str( ) );
	auto s1 = get_str( );
	s1 = "best string";

	auto& s2 = get_str( );
	//s2 = "other string";

	auto&& s3 = get_str( );
	//s3 = "other string";

	auto x = 27;
	const auto cx = x;
	const auto& rx = x;

	/** Universal refernce */
	auto&& uref1 = x;
	auto&& uref2 = cx;
	auto&& uref22 = rx;
	auto&& uref3 = 27;

	//	TD<decltype( uref22 )> _;

	std::cout << typeid( uref1 ).name( ) << std::endl;

	/** Functions */
	const char name[] =		// name type - const char[13]
		"R. N. Briggs";
	auto arr1 = name;		// arr1 type - const 
	auto& arr2 = name;		// arr2 type - const char (&)[13]

	const auto func5 = someFunc;			// func1 type - void (*)(int, double)
	const auto& func6 = someFunc;			// func2 type - void (&)(int, double)

	//	TD<decltype(func6)> _;			
}
