	String & String::operator=( String && other )
	{
		swap( std::move( other ) );
		return *this;
	}