// CPPEleven.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <time.h>
#include "RValueTest.h"
#include "SimpleRV.h"
#include "NoRV.h"
//#include <chrono>
#include <iterator>

#include "GetTime.h"
#include "UnorderedMapTest.h"


const int Size = 10000000;

Strings make_vec( );
void make_vec( Strings& strs );

void test_1( );
void test_2( );
void test_3( );







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

		//hasher_test( );
	}
	catch ( std::exception& exc )
	{
		std::cout << "Exception: " << exc.what( ) << std::endl;
	}

	return 0;
}