		cCallback (const AString & a_PlayerName, cPlayerListCallback & a_Callback) 
			: m_Callback( a_Callback )
			, BestMatch( NULL )
			, BestRating( 0 )
			, NumMatches( 0 )
			, NameLength( a_PlayerName.length() )
			, PlayerName( a_PlayerName )
		{}