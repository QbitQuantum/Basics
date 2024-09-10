bool NerveTool::extract_codes( String& s , StringList *z ) {
	String so;

	// [zzz,code],[zzz,code]
	s.trim();
	while( !s.isEmpty() ) {
		if( !s.startsFrom( "[" ) )
			return( false );

		int idx = s.find( "]" );
		if( idx < 0 )
			return( false );

		String a = s.getMid( 1 , idx - 1 );
		s.remove( 0 , idx + 1 );
		s.trim();

		idx = a.find( "," );
		if( idx < 0 )
			return( false );

		a = a.getMid( idx + 1 );
		a.trim();
		if( a.isEmpty() )
			return( false );

		idx = s.find( "," );
		if( idx >= 0 ) {
			s.remove( 0 , idx + 1 );
			s.trim();

			if( s.isEmpty() )
				return( false );
		}

		// add to list
		z -> add( a );
	}

	return( true );
}