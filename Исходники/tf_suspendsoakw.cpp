TInt CSuspendTest::ZeroFillBlock( TInt aBlockNumber )
	//
	// Zero-fills and entire block
	// The requires that writing works
	//
	{
	test.Printf( _L("Zero-filling block %d\n"), aBlockNumber );

	//
	// Create a buffer full of zeros
	//
	const TInt KZeroBufSize = 512;

	TBuf8<KZeroBufSize> buf;
	buf.FillZ( buf.MaxLength() );

	//
	// Write the data out to the Flash
	//
	TInt writeCount = iBlockSize / KZeroBufSize;
	TInt r = KErrNone;
	TUint blockBaseOffset = aBlockNumber * iBlockSize;
	TInt pos = blockBaseOffset;
	for( ; (writeCount > 0) && (KErrNone == r); writeCount-- )
		{
		r = iDrive.Write( pos, buf );
		if( r != KErrNone )
			{
			test.Printf( _L("... FAIL: write failed (%d) at offset 0x%x\n"), pos );
			}
		pos += KZeroBufSize;
		}

	return r;
	}