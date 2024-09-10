/* Retrieves a descriptive string of the error number
 * This function uses the Visual Studio C runtime library functions
 * Returns the string_length if successful or -1 on error
 */
int libcerror_system_copy_string_from_error_number(
     libcstring_system_character_t *string,
     size_t string_size,
     uint32_t error_number )
{
	size_t string_length = 0;

	if( string == NULL )
	{
		return( -1 );
	}
	if( string_size > (size_t) INT_MAX )
	{
		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( _wcserror_s(
	     string,
	     string_size,
	     (int) error_number ) != 0 )
#else
	if( strerror_s(
	     string,
	     string_size,
	     (int) error_number ) != 0 )
#endif
	{
		return( -1 );
	}
	string[ string_size - 1 ] = 0;

	string_length = libcstring_system_string_length(
	                 string );

	return( (int) string_length );
}