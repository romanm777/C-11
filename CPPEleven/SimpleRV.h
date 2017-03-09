#pragma once

class SimpleRV
{
public:
	SimpleRV( const std::string& name );
	SimpleRV( const SimpleRV& rvt );

	SimpleRV& operator=( const SimpleRV& rvt );

	SimpleRV( SimpleRV&& rvt );
	SimpleRV& operator=( SimpleRV&& rvt );

	std::vector<std::string> m_names;
};

using SRValues = std::vector<SimpleRV>;