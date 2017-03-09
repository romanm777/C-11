#include "stdafx.h"
#include "RValueTest.h"


void init_strings(Strings& strs)
{
	for(int i = 0; i < Count; ++i) 
	{
		strs.push_back( "str" );
	}
}


RValueTest::RValueTest( const int i )
	: m_num( i )
{
	init_strings(m_strings);

	std::cout << "RValueTest constructor with i" << std::endl;
}

RValueTest::RValueTest( const RValueTest& rvt )
{
	const Strings& strs = rvt.get_strings( );
	m_strings.assign( strs.cbegin(), strs.cend() );
	m_num = rvt.get_num( );

	std::cout << "RValueTest copy constructor" << std::endl;
}

RValueTest& RValueTest::operator=( const RValueTest& rvt )
{
	if(this == &rvt)
		return *this;

	const Strings& strs = rvt.get_strings( );
	m_strings.assign( strs.cbegin(), strs.cend() );
	m_num = rvt.get_num( );

	std::cout << "RValueTest operator=" << std::endl;

	return *this;
}

RValueTest::RValueTest( RValueTest&& rvt )
{
	m_strings = std::move( rvt.get_strings( ) );
	m_num = rvt.get_num( );

	std::cout << "RValueTest move constructor" << std::endl;
}

RValueTest& RValueTest::operator=( RValueTest&& rvt )
{
	m_strings = std::move( rvt.get_strings( ) );
	m_num = rvt.get_num( );

	std::cout << "RValueTest move operator=" << std::endl;

	return *this;
}

Strings& RValueTest::get_strings( )
{
	return const_cast<Strings&>( static_cast<const RValueTest&>(*this).get_strings( ) );
}

const Strings& RValueTest::get_strings( ) const
{
	return m_strings;
}
