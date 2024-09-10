	bool StringExtensions::CompareStrings( const std::string &lhs, const std::string &rhs )
	{
		return ( ToLower( lhs ) == ToLower( rhs ) );
	}