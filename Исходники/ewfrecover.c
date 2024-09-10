int main( int argc, char * const argv[] )
#endif
{
#if defined( HAVE_GETRLIMIT )
	struct rlimit limit_data;
#endif
	system_character_t acquiry_operating_system[ 32 ];

	system_character_t * const *source_filenames   = NULL;
	libcerror_error_t *error                       = NULL;
	log_handle_t *log_handle                       = NULL;
	system_character_t *acquiry_software_version   = NULL;
	system_character_t *log_filename               = NULL;
	system_character_t *option_header_codepage     = NULL;
	system_character_t *option_process_buffer_size = NULL;
	system_character_t *option_target_path         = NULL;
	system_character_t *program                    = _SYSTEM_STRING( "ewfrecover" );
	system_integer_t option                        = 0;
	uint8_t calculate_md5                          = 1;
	uint8_t print_status_information               = 1;
	uint8_t use_chunk_data_functions               = 0;
	uint8_t verbose                                = 0;
	int number_of_filenames                        = 0;
	int result                                     = 1;

#if !defined( HAVE_GLOB_H )
	ewftools_glob_t *glob                        = NULL;
#endif

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
             "ewftools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( ewftools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		ewftools_output_version_fprint(
		 stderr,
		 program );

		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
#if defined( WINAPI ) && !defined( __CYGWIN__ )
#if defined( _MSC_VER )
	if( _setmode(
	     _fileno(
	      stdout ),
	     _O_BINARY ) == -1 )
#else
	if( setmode(
	     _fileno(
	      stdout ),
	     _O_BINARY ) == -1 )
#endif
	{
		ewftools_output_version_fprint(
		 stderr,
		 program );

		fprintf(
		 stderr,
		 "Unable to set stdout to binary mode.\n" );

		usage_fprint(
		 stdout );

		goto on_error;
	}
#endif
	while( ( option = ewftools_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "A:f:hl:p:qt:vVx" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				ewftools_output_version_fprint(
				 stderr,
				 program );

				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind ] );

				usage_fprint(
				 stderr );

				goto on_error;

			case (system_integer_t) 'A':
				option_header_codepage = optarg;

				break;

			case (system_integer_t) 'h':
				ewftools_output_version_fprint(
				 stderr,
				 program );

				usage_fprint(
				 stderr );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'l':
				log_filename = optarg;

				break;

			case (system_integer_t) 'p':
				option_process_buffer_size = optarg;

				break;

			case (system_integer_t) 'q':
				print_status_information = 0;

				break;

			case (system_integer_t) 't':
				option_target_path = optarg;

				break;

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				ewftools_output_version_fprint(
				 stderr,
				 program );

				ewftools_output_copyright_fprint(
				 stderr );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'x':
				use_chunk_data_functions = 1;

				break;
		}
	}
	if( optind == argc )
	{
		ewftools_output_version_fprint(
		 stderr,
		 program );

		fprintf(
		 stderr,
		 "Missing EWF image file(s).\n" );

		usage_fprint(
		 stderr );

		goto on_error;
	}
	ewftools_output_version_fprint(
	 stderr,
	 program );

	libcnotify_verbose_set(
	 verbose );

#if !defined( HAVE_LOCAL_LIBEWF )
	libewf_notify_set_verbose(
	 verbose );
	libewf_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if !defined( HAVE_GLOB_H )
	if( ewftools_glob_initialize(
	     &glob,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize glob.\n" );

		goto on_error;
	}
	if( ewftools_glob_resolve(
	     glob,
	     &( argv[ optind ] ),
	     argc - optind,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to resolve glob.\n" );

		goto on_error;
	}
	if( ewftools_glob_get_results(
	     glob,
	     &number_of_filenames,
	     (system_character_t ***) &source_filenames,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve glob results.\n" );

		goto on_error;
	}
#else
	source_filenames    = &( argv[ optind ] );
	number_of_filenames = argc - optind;
#endif

	if( export_handle_initialize(
	     &ewfrecover_export_handle,
	     calculate_md5,
	     use_chunk_data_functions,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create export handle.\n" );

		goto on_error;
	}
#if defined( HAVE_GETRLIMIT )
	if( getrlimit(
            RLIMIT_NOFILE,
            &limit_data ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to determine limit: number of open file descriptors.\n" );
	}
	if( limit_data.rlim_max > (rlim_t) INT_MAX )
	{
		limit_data.rlim_max = (rlim_t) INT_MAX;
	}
	if( limit_data.rlim_max > 0 )
	{
		limit_data.rlim_max /= 2;
	}
	if( export_handle_set_maximum_number_of_open_handles(
	     ewfrecover_export_handle,
	     (int) limit_data.rlim_max,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to set maximum number of open file handles.\n" );

		goto on_error;
	}
#endif
	if( ewftools_signal_attach(
	     ewfrecover_signal_handler,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to attach signal handler.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	result = export_handle_open_input(
	          ewfrecover_export_handle,
	          source_filenames,
	          number_of_filenames,
	          &error );

	if( ewfrecover_abort != 0 )
	{
		goto on_abort;
	}
	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open EWF file(s).\n" );

		goto on_error;
	}
#if !defined( HAVE_GLOB_H )
	if( ewftools_glob_free(
	     &glob,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free glob.\n" );

		goto on_error;
	}
#endif
	result = export_handle_input_is_corrupted(
	          ewfrecover_export_handle,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to determine if EWF file(s) are corrupted.\n" );

		goto on_error;
	}
	else if( result == 0 )
	{
		fprintf(
		 stderr,
		 "EWF file(s) are not corrupted.\n" );

		goto on_error;
	}
	ewfrecover_export_handle->output_format = EXPORT_HANDLE_OUTPUT_FORMAT_EWF;
	ewfrecover_export_handle->export_size   = ewfrecover_export_handle->input_media_size;

	if( option_header_codepage != NULL )
	{
		result = export_handle_set_header_codepage(
			  ewfrecover_export_handle,
		          option_header_codepage,
			  &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set header codepage.\n" );

			goto on_error;
		}
		else if( result == 0 )
		{
			fprintf(
			 stderr,
			 "Unsupported header codepage defaulting to: ascii.\n" );
		}
	}
	if( option_target_path != NULL )
	{
		if( export_handle_set_string(
		     ewfrecover_export_handle,
		     option_target_path,
		     &( ewfrecover_export_handle->target_path ),
		     &( ewfrecover_export_handle->target_path_size ),
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to set target path.\n" );

			goto on_error;
		}
	}
	else
	{
		/* Make sure the target filename is set
		 */
		if( export_handle_set_string(
		     ewfrecover_export_handle,
		     _SYSTEM_STRING( "recover" ),
		     &( ewfrecover_export_handle->target_path ),
		     &( ewfrecover_export_handle->target_path_size ),
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to set target filename.\n" );

			goto on_error;
		}
	}
	/* Make sure we can write the target file
	 */
	if( export_handle_check_write_access(
	     ewfrecover_export_handle,
	     ewfrecover_export_handle->target_path,
	     &error ) != 1 )
	{
#if defined( HAVE_VERBOSE_OUTPUT )
		libcnotify_print_error_backtrace(
		 error );
#endif
		libcerror_error_free(
		 &error );

		fprintf(
		 stdout,
		 "Unable to write target file.\n" );

		goto on_error;
	}
	if( option_process_buffer_size != NULL )
	{
		result = export_handle_set_process_buffer_size(
			  ewfrecover_export_handle,
			  option_process_buffer_size,
			  &error );

		if( result == -1 )
		{
			fprintf(
			 stderr,
			 "Unable to set process buffer size.\n" );

			goto on_error;
		}
		else if( ( result == 0 )
		      || ( ewfrecover_export_handle->process_buffer_size > (size_t) SSIZE_MAX ) )
		{
			ewfrecover_export_handle->process_buffer_size = 0;

			fprintf(
			 stderr,
			 "Unsupported process buffer size defaulting to: chunk size.\n" );
		}
	}
	/* Initialize values
	 */
	if( log_filename != NULL )
	{
		if( log_handle_initialize(
		     &log_handle,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to create log handle.\n" );

			goto on_error;
		}
		if( log_handle_open(
		     log_handle,
		     log_filename,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to open log file: %" PRIs_SYSTEM ".\n",
			 log_filename );

			goto on_error;
		}
	}
	if( export_handle_open_output(
	     ewfrecover_export_handle,
	     ewfrecover_export_handle->target_path,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open output.\n" );

		goto on_error;
	}
	if( platform_get_operating_system(
	     acquiry_operating_system,
	     32,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to determine operating system.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );

		acquiry_operating_system[ 0 ] = 0;
	}
	acquiry_software_version = _SYSTEM_STRING( LIBEWF_VERSION_STRING );

	if( export_handle_set_output_values(
	     ewfrecover_export_handle,
	     acquiry_operating_system,
	     program,
	     acquiry_software_version,
	     0,
	     1,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to set output values.\n" );

		goto on_error;
	}
	result = export_handle_export_input(
		  ewfrecover_export_handle,
		  0,
		  print_status_information,
		  log_handle,
		  &error );

	if( result != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to recover input.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( log_handle != NULL )
	{
		if( log_handle_close(
		     log_handle,
		     &error ) != 0 )
		{
			fprintf(
			 stderr,
			 "Unable to close log file: %" PRIs_SYSTEM ".\n",
			 log_filename );

			goto on_error;
		}
		if( log_handle_free(
		     &log_handle,
		     &error ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to free log handle.\n" );

			goto on_error;
		}
	}
on_abort:
	if( export_handle_close(
	     ewfrecover_export_handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close export handle.\n" );

		goto on_error;
	}
	if( ewftools_signal_detach(
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to detach signal handler.\n" );

		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( export_handle_free(
	     &ewfrecover_export_handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free export handle.\n" );

		goto on_error;
	}
	if( ewfrecover_abort != 0 )
	{
		fprintf(
		 stdout,
		 "%" PRIs_SYSTEM ": ABORTED\n",
		 program );

		return( EXIT_FAILURE );
	}
	if( result != 1 )
	{
		fprintf(
		 stdout,
		 "%" PRIs_SYSTEM ": FAILURE\n",
		 program );

		return( EXIT_FAILURE );
	}
	fprintf(
	 stdout,
	 "%" PRIs_SYSTEM ": SUCCESS\n",
	 program );

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( log_handle != NULL )
	{
		log_handle_close(
		 log_handle,
		 NULL );
		log_handle_free(
		 &log_handle,
		 NULL );
	}
	if( ewfrecover_export_handle != NULL )
	{
		export_handle_close(
		 ewfrecover_export_handle,
		 NULL );
		export_handle_free(
		 &ewfrecover_export_handle,
		 NULL );
	}
#if !defined( HAVE_GLOB_H )
	if( glob != NULL )
	{
		ewftools_glob_free(
		 &glob,
		 NULL );
	}
#endif
	return( EXIT_FAILURE );
}