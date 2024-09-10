	unsigned int fpe_test( unsigned int except )
	{
		return ( _statusfp() & except ) > 0;
	}