/* Copies the source string (of wchar_t) into the destination string (of char) for a certain size
 * Terminates the destination string with \0 at ( size - 1 )
 * Returns 1 if successful, -1 on error
 */
int8_t libewf_common_copy_wchar_to_char( char *destination, const wchar_t *source, size_t size )
{
	size_t iterator = 0;

	if( source == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_common_copy_wchar_to_char: invalid source.\n" );

		return( -1 );
	}
	if( destination == NULL )
	{
		LIBEWF_WARNING_PRINT( "libewf_common_copy_wchar_to_char: invalid destination.\n" );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		LIBEWF_WARNING_PRINT( "libewf_common_copy_wchar_to_char: invalid size value exceeds maximum.\n" );

		return( -1 );
	}
	for( iterator = 0; iterator < size; iterator++ )
	{
		destination[ iterator ] = (char) wctob( (wint_t) source[ iterator ] );

		/* If character is out of the basic ASCII range use '_' as a place holder
		 */
		if( destination[ iterator ] == EOF )
		{
			destination[ iterator ] = '_';
		}
	}
	destination[ size - 1 ] = (char) '\0';

	return( 1 );
}