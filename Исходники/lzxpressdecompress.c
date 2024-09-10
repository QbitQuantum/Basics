int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error                 = NULL;
	libcfile_file_t *destination_file        = NULL;
	libcfile_file_t *source_file             = NULL;
	system_character_t *option_target_path   = NULL;
	system_character_t *options_string       = NULL;
	system_character_t *source               = NULL;
	uint8_t *buffer                          = NULL;
	uint8_t *uncompressed_data               = NULL;
	char *program                            = "lzxpressdecompress";
	system_integer_t option                  = 0;
	size64_t source_size                     = 0;
	size_t buffer_size                       = 0;
	size_t uncompressed_data_size            = 0;
	ssize_t read_count                       = 0;
	ssize_t write_count                      = 0;
	off_t source_offset                      = 0;
	int decompression_method                 = 1;
	int result                               = 0;
	int verbose                              = 0;

#if defined( WINAPI )
	void *workspace                          = NULL;
	unsigned short winapi_compression_method = 0;
#endif

	assorted_output_version_fprint(
	 stdout,
	 program );

#if defined( WINAPI )
	options_string = _SYSTEM_STRING( "d:ho:s:t:vV1234" );
#else
	options_string = _SYSTEM_STRING( "d:ho:s:t:vV12" );
#endif
	while( ( option = assorted_getopt(
	                   argc,
	                   argv,
	                   options_string ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM "\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) '1':
				decompression_method = 1;

				break;

			case (system_integer_t) '2':
				decompression_method = 2;

				break;

#if defined( WINAPI )
			case (system_integer_t) '3':
				decompression_method = 3;

				break;

			case (system_integer_t) '4':
				decompression_method = 4;

				break;

#endif
			case (system_integer_t) 'd':
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				uncompressed_data_size = _wtol( optarg );
#else
				uncompressed_data_size = atol( optarg );
#endif
				break;

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'o':
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				source_offset = _wtol( optarg );
#else
				source_offset = atol( optarg );
#endif
				break;

			case (system_integer_t) 's':
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				source_size = _wtol( optarg );
#else
				source_size = atol( optarg );
#endif
				break;

			case (system_integer_t) 't':
				option_target_path = optarg;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				assorted_output_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 verbose );

	/* Open the source file
	 */
	if( libcfile_file_initialize(
	     &source_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create source file.\n" );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libcfile_file_open_wide(
	          source_file,
	          source,
	          LIBCFILE_OPEN_READ,
	          &error );
#else
	result = libcfile_file_open(
	          source_file,
	          source,
	          LIBCFILE_OPEN_READ,
	          &error );
#endif
 	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open source file.\n" );

		goto on_error;
	}
	if( source_size == 0 )
	{
		if( libcfile_file_get_size(
		     source_file,
		     &source_size,
		     &error ) == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to determine size of source file.\n" );

			goto on_error;
		}
		if( source_size <= (size64_t) source_offset )
		{
			fprintf(
			 stderr,
			 "Invalid source size value is less equal than source offset.\n" );

			goto on_error;
		}
		source_size -= source_offset;
	}
	if( source_size == 0 )
	{
		fprintf(
		 stderr,
		 "Invalid source size value is zero.\n" );

		goto on_error;
	}
	if( source_size > (size_t) SSIZE_MAX )
	{
		fprintf(
		 stderr,
		 "Invalid source size value exceeds maximum.\n" );

		goto on_error;
	}
	/* Create the input buffer
	 */
	buffer_size = source_size;

	buffer = (uint8_t *) memory_allocate(
	                      sizeof( uint8_t ) * buffer_size );

	if( buffer == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create buffer.\n" );

		goto on_error;
	}
	if( uncompressed_data_size == 0 )
	{
		uncompressed_data_size = 65536;
	}
	uncompressed_data = (uint8_t *) memory_allocate(
	                                 sizeof( uint8_t ) * uncompressed_data_size );

	if( uncompressed_data == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to create uncompressed data buffer.\n" );

		goto on_error;
	}
	if( memory_set(
             uncompressed_data,
	     0,
	     uncompressed_data_size ) == NULL )
	{
		fprintf(
		 stderr,
		 "Unable to clear uncompressed data buffer.\n" );

		goto on_error;
	}
	/* Position the source file at the right offset
	 */
	if( libcfile_file_seek_offset(
	     source_file,
	     source_offset,
	     SEEK_SET,
	     &error ) == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to seek offset in source file.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Starting LZXPRESS decompression of: %" PRIs_SYSTEM " at offset: %" PRIjd " (0x%08" PRIjx ").\n",
	 source,
	 source_offset,
	 source_offset );

	read_count = libcfile_file_read_buffer(
		      source_file,
		      buffer,
		      source_size,
	              &error );

	if( read_count != (ssize_t) source_size )
	{
		fprintf(
		 stderr,
		 "Unable to read from source file.\n" );

		goto on_error;
	}
	/* Decompress the data
	 */
	if( option_target_path == NULL )
	{
		fprintf(
		 stderr,
		 "Compressed data:\n" );

		libcnotify_print_data(
		 buffer,
		 source_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
	if( decompression_method == 1 )
	{
		result = libfwnt_lzxpress_decompress(
		          buffer,
		          (size_t) source_size,
		          uncompressed_data,
		          &uncompressed_data_size,
		          &error );
	}
	else if( decompression_method == 2 )
	{
		result = libfwnt_lzxpress_huffman_decompress(
		          buffer,
		          (size_t) source_size,
		          uncompressed_data,
		          &uncompressed_data_size,
		          &error );
	}
#if defined( WINAPI )
	else if( ( decompression_method == 3 )
	      || ( decompression_method == 4 ) )
	{
		if( decompression_method == 3 )
		{
			winapi_compression_method = COMPRESSION_FORMAT_XPRESS;
		}
		else if( decompression_method == 4 )
		{
			winapi_compression_method = COMPRESSION_FORMAT_XPRESS_HUFF;
		}
/* TODO: determine workspace size: RtlGetCompressionWorkSpaceSize */
		workspace = (void *) memory_allocate(
		                      16 * 1024 * 1024 );

		if( workspace == NULL )
		{
			fprintf(
			 stderr,
			 "Unable to create workspace.\n" );

			goto on_error;
		}
		result = lzxpresscompress_RtlDecompressBufferEx(
		          winapi_compression_method,
		          (unsigned char *) uncompressed_data,
		          (unsigned long) uncompressed_data_size,
		          (unsigned char *) buffer,
		          (unsigned long) source_size,
		          (unsigned long *) &uncompressed_data_size,
		          workspace );

		memory_free(
		 workspace );

		if( result != 0 )
		{
			result = -1;
		}
		else
		{
			result = 1;
		}
	}
#endif
	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to decompress data.\n" );

		libcnotify_print_data(
		 uncompressed_data,
		 uncompressed_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		goto on_error;
	}
	if( option_target_path == NULL )
	{
		fprintf(
		 stderr,
		 "Uncompressed data:\n" );

		libcnotify_print_data(
		 uncompressed_data,
		 uncompressed_data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
	else
	{
		if( libcfile_file_initialize(
		     &destination_file,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to create destination file.\n" );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libcfile_file_open_wide(
		          destination_file,
		          option_target_path,
		          LIBCFILE_OPEN_WRITE,
		          &error );
#else
		result = libcfile_file_open(
		          destination_file,
		          option_target_path,
		          LIBCFILE_OPEN_WRITE,
		          &error );
#endif
	 	if( result != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to open destination file.\n" );

			goto on_error;
		}
		write_count = libcfile_file_write_buffer(
			       destination_file,
			       uncompressed_data,
			       uncompressed_data_size,
			       &error );

		if( write_count != (ssize_t) uncompressed_data_size )
		{
			fprintf(
			 stderr,
			 "Unable to write to destination file.\n" );

			goto on_error;
		}
		if( libcfile_file_close(
		     destination_file,
		     &error ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to close destination file.\n" );

			goto on_error;
		}
		if( libcfile_file_free(
		     &destination_file,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free destination file.\n" );

			goto on_error;
		}
	}
	/* Clean up
	 */
	if( libcfile_file_close(
	     source_file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close source file.\n" );

		goto on_error;
	}
	if( libcfile_file_free(
	     &source_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free source file.\n" );

		goto on_error;
	}
	memory_free(
	 uncompressed_data );

	uncompressed_data = NULL;

	memory_free(
	 buffer );

	buffer = NULL;

	fprintf(
	 stdout,
	 "LZXPRESS decompression:\tSUCCESS\n" );

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( destination_file != NULL )
	{
		libcfile_file_free(
		 &destination_file,
		 NULL );
	}
	if( uncompressed_data != NULL )
	{
		memory_free(
		 uncompressed_data );
	}
	if( buffer != NULL )
	{
		memory_free(
		 buffer );
	}
	if( source_file != NULL )
	{
		libcfile_file_free(
		 &source_file,
		 NULL );
	}
	fprintf(
	 stdout,
	 "LZXPRESS decompression:\tFAILURE\n" );

	return( EXIT_FAILURE );
}