        //-----------------------------------------------------------------------
		// Return the ceiling of the passed in coord based on valid LOD.
		int Ceil( int localPageCoord ) const
		{
			if( Floor( localPageCoord ) == localPageCoord )
				return localPageCoord;	// Already at ceiling.
			else
				return Floor( localPageCoord + lodStep_ );
        }