HBufC8 *CemailTest::GetNextStringLC ( CStifItemParser& aItem, const TDesC &aName )
	{
	TPtrC nodename;
	nodename.Set( KNullDesC );

    TInt i( aItem.GetNextString ( nodename ) );
    if ( i != KErrNone ) 
	    {
	    iLog->Log( _L( "ERROR Reading '%S' argument: 0x%X" ), &aName, i );
	    }
	else
		{
		iLog->Log( _L("%S: %S"), &aName, &nodename);
		}
	
	HBufC8 *buf = HBufC8::NewLC( nodename.Length() ) ;
	buf->Des().Copy( nodename );
	
	return buf;
	}