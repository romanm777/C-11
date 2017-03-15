#include "stdafx.h"
#include "NoRV.h"

const int Count = 10000;

NoRV::NoRV( const std::string& name )
{
	for(int i = 0; i < Count; ++i)
	{
		m_names.push_back(name);
	}
}

NoRV::NoRV( const NoRV& rvt )
{
	m_names = rvt.m_names;
}

NoRV& NoRV::operator=( const NoRV& rvt )
{
	m_names = rvt.m_names;

	return *this;
}