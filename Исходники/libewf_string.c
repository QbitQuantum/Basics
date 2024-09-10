/* Converts a string to an EWF header2
 * Returns 1 if successful, 0 if header2 was not set, or -1 on error
 */
int8_t libewf_string_copy_to_header2( LIBEWF_CHAR *string, size_t size_string, EWF_HEADER2 *header2, size_t size_header2 )
{
#ifdef HAVE_WIDE_CHARACTER_TYPE
	mbstate_t conversion_state;
#endif

	if( string == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: invalid string.\n" );

		return( -1 );
	}
	if( header2 == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: invalid header2.\n" );

		return( -1 );
	}
	if( ( size_string > (size_t) SSIZE_MAX ) || ( size_header2 > (size_t) SSIZE_MAX ) )
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: invalid size value exceeds maximum.\n" );

		return( -1 );
	}
	if( size_header2 < ( ( size_string * 2 ) + 2 ) )
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: header2 too small.\n" );

		return( -1 );
	}
#ifdef HAVE_WIDE_CHARACTER_TYPE
	if( libewf_common_memset( &conversion_state, 0, sizeof( mbstate_t ) ) == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: unable to clear converion state.\n" );

		return( -1 );
	}
	if( mbsinit( &conversion_state ) == 0 )
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: unable to initialize converion state.\n" );

		return( -1 );
	}
	if( wcsrtombs( (char *) &header2[ 2 ], (const wchar_t **) &string, size_header2, &conversion_state ) != ( size_string - 1 ) )
#else
	if( libewf_string_copy_ascii_to_utf16( string, size_string, (LIBEWF_CHAR *) header2, size_header2, LIBEWF_STRING_LITTLE_ENDIAN ) != 1 )
#endif
	{
		LIBEWF_WARNING_PRINT( "libewf_string_copy_to_header2: unable to copy string to header2.\n" );

		return( -1 );
	}
#ifdef HAVE_WIDE_CHARACTER_TYPE
	if( header2[ 4 ] == (EWF_HEADER2) '\0' )
	{
		header2[ 0 ] = (EWF_HEADER2) 0xfe;
		header2[ 1 ] = (EWF_HEADER2) 0xff;
	}
	else
	{
		header2[ 0 ] = (EWF_HEADER2) 0xff;
		header2[ 1 ] = (EWF_HEADER2) 0xfe;
	}
#endif
	return( 1 );
}