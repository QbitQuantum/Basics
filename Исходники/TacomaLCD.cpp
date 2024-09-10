///////////////////////////////////////////////////////////////////////////////
// Raw primitive to output a particular 8 char area on the LCD.  You provide
// the string, the LCD index (strip index) and the Row Index (0=top, 1=bot)
void CTacomaSurface::showText( LPCSTR pszIn, int ixLcd, int ixRow, 
											size_t cChars, //= 8
											bool bForce )	//= false
{
	if ( ixLcd < 0 || ixLcd > 12 )
		return;
	if ( ixRow < 0 || ixRow > 1 )
		return;

//	CString strDbg(pszIn );
//	TRACE( _T("showing lcd ix %d: %s\n"), ixLcd, strDbg );
//	if ( ixLcd == 12 )
//		ixLcd = ixLcd;	// breakpointable no-op

	char psz[128];
	cChars = min( cChars, 128 );
	::strncpy( psz, pszIn, cChars );
	psz[cChars] = '\0';

	// pad out with blanks
	size_t cLen = ::strlen( pszIn );
	for ( size_t ic = cLen; ic < cChars; ic++ )
		psz[ic] = ' ';

	// compare against the cache for this row/col to see if we
	// should send
	if ( !bForce && 0 == ::memcmp( (LPBYTE)&m_aaLCDChars[ixRow][ixLcd*8], (LPBYTE)psz, cChars ) )
		return;

	// set in the cache
	::memcpy( (LPBYTE)&m_aaLCDChars[ixRow][ixLcd*8], (LPBYTE)psz, cChars );

	MAYBE_TRACE( "showText \"%s\" ixLcd:%d ixRow:%d\n", psz, ixLcd, ixRow );

	BYTE byCS = 0;

	// Determine the Display Addresses based on the lcd column (index)
	BYTE byMSB = 0;
	if ( ixLcd > 7 )
		byMSB = 0x08;
	else if ( ixLcd > 3 )
		byMSB = 0x04;

	BYTE byLSB = (ixLcd % 4) * 8;
	// special case
	if ( ixLcd == 12 )	// master
		byLSB = 0x20;

	// offset for bottom row
	if ( 1 == ixRow )
		byLSB += 0x40;		// always offset by this much (thank you)

	cLen = ::strlen( psz );
	cLen = min( cLen, 64 );

	//size_t cb = s_cbPrefix;
	//cb += 2;			// address bytes
	//cb += 1;			// checksum
	//cb += 1;			// the 0xF7
	//cb += cLen;		// the data itself
	const size_t cb = s_cbPrefix + 4 + cLen;	// total of the above items

	BYTE* pFill = s_byBuf + s_cbPrefix;

	::memcpy( s_byBuf, s_abyPrefix, s_cbPrefix );

	*pFill++ = byMSB;		// add the addressing bytes
	byCS += byMSB;
	*pFill++ = byLSB;
	byCS += byLSB;

	// the data itself
	for ( DWORD i = 0; i < cLen; i++ )
	{
		BYTE byChar = psz[i];
		byCS += byChar;
		*pFill++ = byChar;
	}

	// compute checksum.
	const BYTE byMod = byCS % 128;
	byCS = 128 - byMod;
	byCS &= 0x7f;

	*pFill++ = byCS;	// checksum

	*pFill++ = 0xF7;	// EOX

	ASSERT( pFill - s_byBuf == cb );	// if this fires, cb was not computed correctly

	// If testing on a mackie, this really makes the hardware angry
	if ( !m_bOnMackie )
		MidiOutLongMsg( (DWORD)cb, s_byBuf );
}