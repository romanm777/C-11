#pragma once

extern int global_id;

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

	static void init_id( const int orig ) { global_id = orig; }

	std::vector<std::string>	m_names;
	clock_t						m_clock;
	int							m_id;
};

using SRValues = std::vector<SimpleRV>;