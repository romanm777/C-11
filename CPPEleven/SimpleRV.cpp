#include "stdafx.h"
#include "SimpleRV.h"

const int Count = 10000;

int global_id = 0;

SimpleRV::SimpleRV( const std::string& name )
{
	m_id = global_id++;

	for(int i = 0; i < Count / 100; ++i)
	{
		m_names.push_back(name);
	}

	m_clock = clock( );
	//std::cout << "constructor" << std::endl;
}

SimpleRV::SimpleRV( const SimpleRV& rvt )
{
	m_names = rvt.m_names;
	m_clock = rvt.m_clock;
	m_id = rvt.m_id;

	//std::cout << "copy constructor" << std::endl;
}

SimpleRV& SimpleRV::operator=( const SimpleRV& rvt )
{
	m_names = rvt.m_names;
	m_clock = rvt.m_clock;
	m_id = rvt.m_id;

	//std::cout << "assign op" << std::endl;

	return *this;
}

SimpleRV::SimpleRV( SimpleRV&& rvt )
{
	m_names = std::move( rvt.m_names );
	m_clock = rvt.m_clock;
	m_id = rvt.m_id;

	//std::cout << "move constructor" << std::endl;
}

SimpleRV& SimpleRV::operator=( SimpleRV&& rvt )
{
	m_names = std::move( rvt.m_names );
	m_clock = rvt.m_clock;
	m_id = rvt.m_id;

	//std::cout << "move assign op" << std::endl;

	return *this;
}

bool SimpleRV::operator<( const SimpleRV& rvt ) const
{
	return m_clock < rvt.m_clock;
}

SimpleRV::~SimpleRV( )
{
	m_names;
	m_clock;
	m_id;
}