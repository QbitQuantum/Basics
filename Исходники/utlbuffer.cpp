//-----------------------------------------------------------------------------
// Converts a buffer from a CRLF buffer to a CR buffer (and back)
// Returns false if no conversion was necessary (and outBuf is left untouched)
// If the conversion occurs, outBuf will be cleared.
//-----------------------------------------------------------------------------
bool CUtlBuffer::ConvertCRLF( CUtlBuffer &outBuf )
{
	if ( !IsText() || !outBuf.IsText() )
		return false;

	if ( ContainsCRLF() == outBuf.ContainsCRLF() )
		return false;

	int nInCount = TellMaxPut();

	outBuf.Purge();
	outBuf.EnsureCapacity( nInCount );

	bool bFromCRLF = ContainsCRLF();

	// Start reading from the beginning
	int nGet = TellGet();
	int nPut = TellPut();
	int nGetDelta = 0;
	int nPutDelta = 0;

	const char *pBase = (const char*)Base();
	int nCurrGet = 0;
	while ( nCurrGet < nInCount )
	{
		const char *pCurr = &pBase[nCurrGet];
		if ( bFromCRLF )
		{
			const char *pNext = Q_strnistr( pCurr, "\r\n", nInCount - nCurrGet );
			if ( !pNext )
			{
				outBuf.Put( pCurr, nInCount - nCurrGet );
				break;
			}

			int nBytes = (size_t)pNext - (size_t)pCurr;
			outBuf.Put( pCurr, nBytes );
			outBuf.PutChar( '\n' );
			nCurrGet += nBytes + 2;
			if ( nGet >= nCurrGet - 1 )
			{
				--nGetDelta;
			}
			if ( nPut >= nCurrGet - 1 )
			{
				--nPutDelta;
			}
		}
		else
		{
			const char *pNext = Q_strnchr( pCurr, '\n', nInCount - nCurrGet );
			if ( !pNext )
			{
				outBuf.Put( pCurr, nInCount - nCurrGet );
				break;
			}

			int nBytes = (size_t)pNext - (size_t)pCurr;
			outBuf.Put( pCurr, nBytes );
			outBuf.PutChar( '\r' );
			outBuf.PutChar( '\n' );
			nCurrGet += nBytes + 1;
			if ( nGet >= nCurrGet )
			{
				++nGetDelta;
			}
			if ( nPut >= nCurrGet )
			{
				++nPutDelta;
			}
		}
	}

	Assert(	nPut + nPutDelta <= outBuf.TellMaxPut() );

	outBuf.SeekGet( SEEK_HEAD, nGet + nGetDelta ); 
	outBuf.SeekPut( SEEK_HEAD, nPut + nPutDelta ); 

	return true;
}