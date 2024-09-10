/* Retrieves a ctime formatted string
 * The string must be at least 32 characters of size including the end of string character
 * Returns 1 if successful or -1 on error
 */
int process_status_get_ctime_string(
     const time_t *timestamp,
     libcstring_system_character_t *string,
     size_t string_size,
     libcerror_error_t **error )
{
	static char *function                                    = "process_status_get_ctime_string";

#if ( defined( HAVE_CTIME ) && !defined( HAVE_CTIME_R ) ) || ( defined( WINAPI ) && !defined( _MSC_VER ) )
	const libcstring_system_character_t *static_ctime_string = NULL;
	size_t static_ctime_string_length                        = 0;
#endif

	if( timestamp == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid timestamp.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( string_size < 32 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: string too small.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( _wctime_s(
	     string,
	     string_size,
	     timestamp ) != 0 )
#else
	if( ctime_s(
	     string,
	     string_size,
	     timestamp ) != 0 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}

#elif defined( HAVE_CTIME_R )
/* Sanity check
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character ctime_r function
#endif

#if defined( HAVE_CTIME_R_SIZE )
	if( ctime_r(
	     timestamp,
	     string,
	     string_size ) == NULL )
#else
	if( ctime_r(
	     timestamp,
	     string ) == NULL )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}

#else
/* Sanity check
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) && !defined( WINAPI )
#error Missing wide character ctime function
#endif

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	static_ctime_string = _wctime(
	                       timestamp );
#else
	static_ctime_string = ctime(
	                       timestamp );
#endif
	if( static_ctime_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create static ctime string.",
		 function );

		return( -1 );
	}
	static_ctime_string_length = libcstring_system_string_length(
	                              static_ctime_string );

	if( libcstring_system_string_copy(
	     string,
	     static_ctime_string,
	     static_ctime_string_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	string[ static_ctime_string_length ] = 0;
#endif

	return( 1 );
}