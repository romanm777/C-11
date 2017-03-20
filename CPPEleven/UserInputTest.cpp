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


void user_to_file_test( )
{
	std::string path( "C:/Users/mrychko/_Work/C++/CPPEleven/file.txt" );
	std::ofstream FILE( path, std::ios::out | std::ofstream::binary );
	std::copy( std::istream_iterator<char>( std::cin ), std::istream_iterator<char>( ), std::ostreambuf_iterator<char>( FILE ) );

	//std::copy( iter.begin( ), iter.end( ), std::back_inserter( newVector ) );

	//std::copy( std::istream_iterator<wchar_t>( std::cin ), std::istream_iterator<wchar_t>( ), TOFILE );
}