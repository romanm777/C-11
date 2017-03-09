#pragma once

#include <string>

typedef std::vector<std::string>	Strings;

class RValueTest
{
public:
	RValueTest( const int i );
	RValueTest( const RValueTest& rvt );

	RValueTest& operator=( const RValueTest& rvt );

	RValueTest( RValueTest&& rvt );
	RValueTest& operator=( RValueTest&& rvt );

	Strings& get_strings( );
	const Strings& get_strings( ) const;

	inline int get_num( ) const { return m_num; }

	bool operator<(const RValueTest& rvt ) const {	return m_num < rvt.get_num( ); } 

private:
	Strings	m_strings;
	int m_num;
};

typedef std::vector<RValueTest>		RValues;