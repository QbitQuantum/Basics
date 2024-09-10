	bool find( const T &t )
	{
		extern bool intersects( const T &t1, const T &t2 );

		std::vector<T>::reverse_iterator it = family.rbegin(), end = family.rend();

		for( ; it != end ; ++it )
			if( intersects(*it, t) )
				return search = it, true;

		return search = end, false;
	}