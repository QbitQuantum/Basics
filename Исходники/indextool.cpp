void CharsetFold ( CSphIndex * pIndex, FILE * fp )
{
	CSphVector<BYTE> sBuf1 ( 16384 );
	CSphVector<BYTE> sBuf2 ( 16384 );

	bool bUtf = pIndex->GetTokenizer()->IsUtf8();
	if ( !bUtf )
		sphDie ( "sorry, --fold vs SBCS is not supported just yet" );

	CSphLowercaser tLC = pIndex->GetTokenizer()->GetLowercaser();

#if USE_WINDOWS
	setmode ( fileno(stdout), O_BINARY );
#endif

	int iBuf1 = 0; // how many leftover bytes from previous iteration
	while ( !feof(fp) )
	{
		int iGot = fread ( sBuf1.Begin()+iBuf1, 1, sBuf1.GetLength()-iBuf1, fp );
		if ( iGot<0 )
			sphDie ( "read error: %s", strerror(errno) );

		if ( iGot==0 )
			if ( feof(fp) )
				if ( iBuf1==0 )
					break;


		const BYTE * pIn = sBuf1.Begin();
		const BYTE * pInMax = pIn + iBuf1 + iGot;

		if ( pIn==pInMax && feof(fp) )
			break;

		// tricky bit
		// on full buffer, and not an eof, terminate a bit early
		// to avoid codepoint vs buffer boundary issue
		if ( ( iBuf1+iGot )==sBuf1.GetLength() && iGot!=0 )
			pInMax -= 16;

		// do folding
		BYTE * pOut = sBuf2.Begin();
		BYTE * pOutMax = pOut + sBuf2.GetLength() - 16;
		while ( pIn < pInMax )
		{
			int iCode = sphUTF8Decode ( pIn );
			if ( iCode==0 )
				pIn++; // decoder does not do that!
			assert ( iCode>=0 );

			if ( iCode!=0x09 && iCode!=0x0A && iCode!=0x0D )
			{
				iCode = tLC.ToLower ( iCode ) & 0xffffffUL;
				if ( !iCode )
					iCode = 0x20;
			}

			pOut += sphUTF8Encode ( pOut, iCode );
			if ( pOut>=pOutMax )
			{
				fwrite ( sBuf2.Begin(), 1, pOut-sBuf2.Begin(), stdout );
				pOut = sBuf2.Begin();
			}
		}
		fwrite ( sBuf2.Begin(), 1, pOut-sBuf2.Begin(), stdout );

		// now move around leftovers
		BYTE * pRealEnd = sBuf1.Begin() + iBuf1 + iGot;
		if ( pIn < pRealEnd )
		{
			iBuf1 = pRealEnd - pIn;
			memmove ( sBuf1.Begin(), pIn, iBuf1 );
		}
	}
}