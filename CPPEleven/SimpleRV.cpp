#include "stdafx.h"
#include "SimpleRV.h"

SimpleRV::SimpleRV( const std::string& name )
{
	for(int i = 0; i < Count; ++i)
	{
		m_names.push_back(name);
	}

	//std::cout << "constructor" << std::endl;
}

SimpleRV::SimpleRV( const SimpleRV& rvt )
{
	m_names = rvt.m_names;
	//std::cout << "copy constructor" << std::endl;
}

SimpleRV& SimpleRV::operator=( const SimpleRV& rvt )
{
	m_names = rvt.m_names;

	//std::cout << "assign op" << std::endl;

	return *this;
}

SimpleRV::SimpleRV( SimpleRV&& rvt )
{
	m_names = std::move( rvt.m_names );

	//std::cout << "move constructor" << std::endl;
}

SimpleRV& SimpleRV::operator=( SimpleRV&& rvt )
{
	m_names = std::move( rvt.m_names );

	//std::cout << "move assign op" << std::endl;

	return *this;
}

SimpleRV::~SimpleRV( )
{
}