	//-------------------------------------------------------------------------
	MapDemoScreen::~MapDemoScreen( )
	//-------------------------------------------------------------------------
	{
		deleteobject( mMap );
		deleteobject( mOpenStreetMapSource );
		deleteobject( mGoogleStreetMapSource );
		deleteobject( mGoogleAerialMapSource );
		deleteobject( mGoogleHybridMapSource );
	}