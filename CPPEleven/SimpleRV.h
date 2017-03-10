#pragma once

class SimpleRV
{
public:
	SimpleRV( const std::string& name );
	SimpleRV( const SimpleRV& rvt );

	SimpleRV& operator=( const SimpleRV& rvt );

	SimpleRV( SimpleRV&& rvt );
	SimpleRV& operator=( SimpleRV&& rvt );

	bool operator<( const SimpleRV& rvt ) const;

	~SimpleRV( );

	std::vector<std::string>	m_names;
	clock_t						m_clock;
};

using SRValues = std::vector<SimpleRV>;