// nearly straight from the SDK
BOOL Sid2Text( PSID ps, char *buf, int bufSize )
{
	PSID_IDENTIFIER_AUTHORITY psia;
	DWORD dwSubAuthorities;
	DWORD dwSidRev = SID_REVISION;
	DWORD i;
	int n, size;
	char *p;

	// Validate the binary SID.

	if ( ! IsValidSid( ps ) )
		return FALSE;

	// Get the identifier authority value from the SID.

	psia = GetSidIdentifierAuthority( ps );

	// Get the number of subauthorities in the SID.

	dwSubAuthorities = *GetSidSubAuthorityCount( ps );

	// Compute the buffer length.
	// S-SID_REVISION- + IdentifierAuthority- + subauthorities- + NULL

	size = 15 + 12 + ( 12 * dwSubAuthorities ) + 1;

	// Check input buffer length.
	// If too small, indicate the proper size and set last error.

	if ( bufSize < size )
	{
		SetLastError( ERROR_INSUFFICIENT_BUFFER );
		return FALSE;
	}

	// Add 'S' prefix and revision number to the string.

	size = wsprintf( buf, "S-%lu-", dwSidRev );
	p = buf + size;

	// Add SID identifier authority to the string.

	if ( psia->Value[0] != 0 || psia->Value[1] != 0 )
	{
		n = wsprintf( p, "0x%02hx%02hx%02hx%02hx%02hx%02hx",
		(USHORT) psia->Value[0], (USHORT) psia->Value[1],
		(USHORT) psia->Value[2], (USHORT) psia->Value[3],
		(USHORT) psia->Value[4], (USHORT) psia->Value[5] );
		size += n;
		p += n;
	}
	else
	{
		n = wsprintf( p, "%lu", ( (ULONG) psia->Value[5] ) +
		( (ULONG) psia->Value[4] << 8 ) + ( (ULONG) psia->Value[3] << 16 ) +
		( (ULONG) psia->Value[2] << 24 ) );
		size += n;
		p += n;
	}

	// Add SID subauthorities to the string.

	for ( i = 0; i < dwSubAuthorities; ++ i )
	{
		n = wsprintf( p, "-%lu", *GetSidSubAuthority( ps, i ) );
		size += n;
		p += n;
	}

	return TRUE;
}