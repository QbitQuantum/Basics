TPtrC8 Cdmatest::LastURISeg( const TDesC8& aURI )
	{
	TInt i;
	for( i = aURI.Length() - 1; i >= 0; i-- ) 
		{
		if( aURI[i] == '/' )
			{
			break;
			}
		}

	if( i == 0 )
		{
		return aURI;
		}
	else
		{
		return aURI.Mid( i+1 );
		}
	}