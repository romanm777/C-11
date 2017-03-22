#include "stdafx.h"
#include "UserInputTest.h"

#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>

#include <set>                  // or vector, or list, or...(not map!)


struct Point
{
	float x;
	float y;

	Point( ) : x( 0.0f ), y( 0.0f ) { }
	Point( float xx, float yy ) : x( xx ), y( yy ) { }

	// Compiler supplies copy-constructor and assignment operator.              

	// So we can store Points in a std::set.                                     
	bool operator<( const Point& other ) const {
		return ( ( x < other.x ) || ( !( other.x < x ) && y < other.y ) );
	}
};

//                                                                              
// Inserter                                                                     
//                                                                              
std::ostream& operator<<( std::ostream& s, const Point& p )
{
	return s << '(' << p.x << ',' << p.y << ')';
}

//                                                                              
// Extractor -- assume the format produced by the inserter.                     
//                                                                              
std::istream& operator >> ( std::istream& s, Point& p )
{
	// A Point must be expressed as "(x,y)" (whitespace is ignored).             
	float x = 0.0f, y = 0.0f;
	char c = '\0';

	bool got_a_point = false;

	s >> c;
	if ( c == '(' ) {
		s >> x >> c;
		if ( c == ',' ) {
			s >> y >> c;
			if ( c == ')' ) {
				got_a_point = true;
			}
		}
	}
	else {
		s.putback( c );
	}

	if ( got_a_point ) {
		p.x = x;
		p.y = y;
	}
	else {
		s.clear( std::ios_base::badbit );
	}

	return s;
}

void user_input_test( )
{
	std::set<Point> input;

	//                                                                          
	// Read from standard input until encountering non-Point data.             
	//                                                                          
	std::cout << "Enter some points in the form '(x,y)': " << std::endl;
	std::copy( std::istream_iterator<Point>( std::cin ),
		std::istream_iterator<Point>( ),
		std::inserter( input, input.begin( ) ) );

	//                                                                          
	// Write back to standard output, one Point per line.                          
	//                                                                          
	std::cout << "You entered: " << std::endl;
	std::copy( input.begin( ),
		input.end( ),
		std::ostream_iterator<Point>( std::cout, "\n" ) );
}

//std::istream& operator >> ( std::istream& s, char& character )
//{
//	char c = '\0';
//
//	s >> c;
//	if( c == 'Q' )
//	{
//		s.putback( c );
//		s.clear( std::ios_base::badbit );
//	}
//	else
//	{
//		character = c;
//	}
//
//	return s;
//}

void user_to_file_test( )
{
	std::string path( "C:/Users/mrychko/_Work/C++/CPPEleven/file.txt" );

	if( false )
	{
		const int DIM = 6;
		int array[DIM] = { 1,2,3,4,5,6 };
		std::vector<int> my_vector( array, array + DIM );

		std::ofstream out_file;
		out_file.open( path, std::ios::out | std::ofstream::binary );

		if ( out_file.is_open( ) )
		{
			std::copy( my_vector.begin( ), my_vector.end( ), std::ostreambuf_iterator<char>( out_file ) );

			out_file.close( );
		}
	}

	if ( true ) 
	{
		std::cout << "===================== User input to a file ==========================" << std::endl;
		std::cout << "Enter something: " << std::endl;

		std::ofstream out_file2( path, std::ios::out );

		std::copy_if( std::istream_iterator<char>( std::cin ), std::istream_iterator<char>( ), std::ostreambuf_iterator<char>( out_file2 ),
			[&out_file2]( char c )
		{
			if ( c == 'Q' ) {
				out_file2.close( );
				std::cin.clear( std::ios_base::eofbit );
			}

			return true;
		} );
	}

	//std::ofstream FILE2( path, std::ios::out | std::ofstream::binary );
	//std::copy( std::istream_iterator<char>( std::cin ), std::istream_iterator<char>( ), std::ostreambuf_iterator<char>( FILE2 ) );

	//std::copy( iter.begin( ), iter.end( ), std::back_inserter( newVector ) );

	//std::copy( std::istream_iterator<wchar_t>( std::cin ), std::istream_iterator<wchar_t>( ), TOFILE );
}