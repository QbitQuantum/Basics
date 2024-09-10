/* Retrieves the size of the file
 * This function uses the POSIX fstat function or equivalent
 * Returns 1 if successful or -1 on error
 */
int libcfile_stream_get_size(
     libcfile_stream_t *stream,
     size64_t *size,
     libcerror_error_t **error )
{
#if defined( _MSC_VER )
	struct __stat64 file_statistics;
#elif defined( __BORLANDC__ )
	struct stati64 file_statistics;
#else
	struct stat file_statistics;
#endif

	libcfile_internal_stream_t *internal_stream = NULL;
	static char *function                       = "libcfile_stream_get_size";
	size_t file_statistics_size                 = 0;
	int file_descriptor                         = 0;

#if defined( S_ISBLK ) && defined( S_ISCHR )
	off64_t current_offset                      = 0;
	off64_t offset                              = 0;
#endif

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
	internal_stream = (libcfile_internal_stream_t *) stream;

	if( internal_stream->stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid stream - missing stream.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
	file_statistics_size = sizeof( struct __stat64 );
#elif defined( __BORLANDC__ )
	file_statistics_size = sizeof( struct stati64 );
#else
	file_statistics_size = sizeof( struct stat );
#endif

	if( memory_set(
	     &file_statistics,
	     0,
	     file_statistics_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file statistics.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	file_descriptor = _fileno(
	                   internal_stream->stream );
#else
	file_descriptor = fileno(
	                   internal_stream->stream );
#endif

	if( file_descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file descriptor of stream.",
		 function );

		return( -1 );
	}
#if defined( _MSC_VER )
	if( _fstat64(
	     file_descriptor,
	     &file_statistics ) != 0 )
#elif defined( __BORLANDC__ )
	if( _fstati64(
	     file_descriptor,
	     &file_statistics ) != 0 )
#else
	if( fstat(
	     file_descriptor,
	     &file_statistics ) != 0 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file statistics.",
		 function );

		return( -1 );
	}
/* TODO implement device support ? */
/* TODO does not work on Mac OS X or WINAPI */
#if defined( S_ISBLK ) && defined( S_ISCHR )
	if( S_ISBLK( file_statistics.st_mode )
	 || S_ISCHR( file_statistics.st_mode ) )
	{
		if( libcfile_stream_get_offset(
		     stream,
		     &current_offset,
		     error ) != 1  )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve current offset.",
			 function );

			return( -1 );
		}
		/* If the file is a device try to seek the end of the file
		 */
		offset = libcfile_stream_seek_offset(
		          stream,
		          0,
		          SEEK_END,
		          error );

		if( offset == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek end of file.",
			 function );

			return( -1 );
		}
		*size = (size64_t) offset;

		offset = libcfile_stream_seek_offset(
		          stream,
		          current_offset,
		          SEEK_SET,
		          error );

		if( offset == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek offset: %" PRIi64 ".",
			 function,
			 current_offset );

			return( -1 );
		}
	}
	else
#endif
	{
		*size = (size64_t) file_statistics.st_size;
	}
	return( 1 );
}