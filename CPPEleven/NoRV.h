class NoRV
{
public:
	NoRV( const std::string& name );
	NoRV( const NoRV& rvt );

	NoRV& operator=( const NoRV& rvt );

	std::vector<std::string> m_names;
};