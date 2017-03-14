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
