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

template <typename Container, typename Index>
auto GetItem( Container&& c, Index i ) -> decltype( c[i] );

std::vector<int> get_ints( );

void type_deduct_test( )
{
	std::cout << std::endl << "=================== Template type deduction =========================" << std::endl;

	void( *func1 )( ) = show_red_color;
	void( *func2 )( ) = show_red_color;
	void( *func3 )( ) = show_red_color;

	foo_t1( func1 );		// T param -> void (*func1)( ) copy
	foo_t2( func2 );		// T&& param -> void (&func1)( ) reference
	foo_t3( func3 );		// T& param -> void (&func1)( ) reference

	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::cout << std::endl << "=================== Auto type deduction =========================" << std::endl;

	change_str( get_str( ) );
	auto s1 = get_str( );		// const std::string&	->	std::string
	s1 = "best string";

	auto& s2 = get_str( );		// const std::string&	-> const std::string&
	//s2 = "other string";

	auto&& s3 = get_str( );		// const std::string&	-> const std::string&
	//s3 = "other string";

	int a1 = 40;
	int& a2 = a1;
	auto a3 = a2;

	auto x = 27;				// int
	const auto cx = x;			// const int
	const auto& rx = x;			// const int&

	/** Universal refernce */
	auto&& uref1 = x;			// int			->	int&
	auto&& uref2 = cx;			// const int	->	const int&
	auto&& uref22 = rx;			// const int&	->	const int&
	auto&& uref3 = 27;			// 27			->	int&&

	//	TD<decltype( a3 )> _;

	std::cout << typeid( uref1 ).name( ) << std::endl;

	/** Functions */
	const char name[] =		// name type - const char[13]
		"R. N. Briggs";
	auto arr1 = name;		// arr1 type - const char*
	auto& arr2 = name;		// arr2 type - const char (&)[13]

	auto func5 = someFunc;			// func1 type - void (*)(int, double)
	auto& func6 = someFunc;			// func2 type - void (&)(int, double)

	//	TD<decltype(func6)> _;	
	
	std::cout << std::endl << "=================== Decltype deduction =========================" << std::endl;

	decltype( get_str( ) ) val = get_str( );	// const std::string&
	auto val_copy = val;
	val_copy = "something";

	// TD<decltype(val)> _;

	std::vector<int> ints = { 2, 3, 5 };
	auto o1 = GetItem( get_ints( ), 2 );
	auto&& o2 = GetItem( ints, 2 );
	
	o1 = 100;
	o2 = 101;

	// TD<decltype( o1 )> _;
	// TD<decltype( o2 )> _;
	o1 == o2;
}

std::vector<int> get_ints( )
{
	std::vector<int> ints = { 2, 3, 5 };
	return ints;
}

template <typename Container, typename Index>
auto GetItem( Container&& c, Index i ) -> decltype( c[i] )
{
	return c[i];
}
