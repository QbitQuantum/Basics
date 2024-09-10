int main( int argc, char **argv )
{
	int i;
	int is_quoted=0;	
	wcstring_list_t comp;
	wchar_t *prefix = 0;

	int mangle_descriptors = 0;
	int result_fd = -1;
	set_main_thread();
    setup_fork_guards();
    
	/*
	  This initialization is made early, so that the other init code
	  can use global_context for memory managment
	*/
	program_name = L"fish_pager";


	wsetlocale( LC_ALL, L"" );

	/*
	  The call signature for fish_pager is a mess. Because we want
	  to be able to upgrade fish without breaking running
	  instances, we need to support all previous
	  modes. Unfortunatly, the two previous ones are a mess. The
	  third one is designed to be extensible, so hopefully it will
	  be the last.
	*/

	if( argc > 1 && argv[1][0] == '-' )
	{
		/*
		  Third mode
		*/
			
		int completion_fd = -1;
		FILE *completion_file;
			
		while( 1 )
		{
			static struct option
				long_options[] =
				{
					{
						"result-fd", required_argument, 0, 'r' 
					}
					,
					{
						"completion-fd", required_argument, 0, 'c' 
					}
					,
					{
						"prefix", required_argument, 0, 'p' 
					}
					,
					{
						"is-quoted", no_argument, 0, 'q' 
					}
					,
					{
						"help", no_argument, 0, 'h' 
					}
					,
					{
						"version", no_argument, 0, 'v' 
					}
					,
					{ 
						0, 0, 0, 0 
					}
				}
			;
		
			int opt_index = 0;
		
			int opt = getopt_long( argc,
					       argv, 
					       GETOPT_STRING,
					       long_options, 
					       &opt_index );
		
			if( opt == -1 )
				break;
		
			switch( opt )
			{
				case 0:
				{
					break;
				}
			
				case 'r':
				{
					result_fd = get_fd( optarg );
					break;
				}
			
				case 'c':
				{
					completion_fd = get_fd( optarg );
					break;
				}

				case 'p':
				{
					prefix = str2wcs(optarg);
					break;
				}

				case 'h':
				{
					print_help( argv[0], 1 );
					exit(0);						
				}

				case 'v':
				{
					debug( 0, L"%ls, version %s\n", program_name, PACKAGE_VERSION );
					exit( 0 );				
				}
					
				case 'q':
				{
					is_quoted = 1;
				}
			
			}
		}

		if( completion_fd == -1 || result_fd == -1 )
		{
			debug( 0, _(L"Unspecified file descriptors") );
			exit( 1 );
		}
			

		if( (completion_file = fdopen( completion_fd, "r" ) ) )
		{
			read_array( completion_file, comp );
			fclose( completion_file );
		}
		else
		{
			debug( 0, _(L"Could not read completions") );
			wperror( L"fdopen" );
			exit( 1 );
		}

		if( !prefix )
		{
			prefix = wcsdup( L"" );
		}
			
			
	}
	else
	{
		/*
		  Second or first mode. These suck, but we need to support
		  them for backwards compatibility. At least for some
		  time.

		  Third mode was implemented in January 2007, and previous
		  modes should be considered deprecated from that point
		  forward. A reasonable time frame for removal of the code
		  below has yet to be determined.
		*/
			
		if( argc < 3 )
		{
			print_help( argv[0], 1 );
			exit( 0 );
		}
		else
		{
			mangle_descriptors = 1;
			
			prefix = str2wcs( argv[2] );
			is_quoted = strcmp( "1", argv[1] )==0;
			
			if( argc > 3 )
			{
				/*
				  First mode
				*/
				for( i=3; i<argc; i++ )
				{
					wcstring wcs = str2wcstring( argv[i] );
                    comp.push_back(wcs);
				}
			}
			else
			{
				/*
				  Second mode
				*/
				read_array( stdin, comp );
			}
		}
			
	}
		
//		debug( 3, L"prefix is '%ls'", prefix );
		
	init( mangle_descriptors, result_fd );

	mangle_descriptions( comp );

	if( wcscmp( prefix, L"-" ) == 0 )
		join_completions( comp );

	std::vector<comp_t *> completions = mangle_completions( comp, prefix );

	/**
	   Try to print the completions. Start by trying to print the
	   list in PAGER_MAX_COLS columns, if the completions won't
	   fit, reduce the number of columns by one. Printing a single
	   column never fails.
	*/
	for( i = PAGER_MAX_COLS; i>0; i-- )
	{
		switch( completion_try_print( i, prefix, is_quoted, completions ) )
		{

			case PAGER_RETRY:
				break;

			case PAGER_DONE:
				i=0;
				break;

			case PAGER_RESIZE:
				/*
				  This means we got a resize event, so we start
				  over from the beginning. Since it the screen got
				  bigger, we might be able to fit all completions
				  on-screen.
				*/
				i=PAGER_MAX_COLS+1;
				break;

		}		
	}
	
	free(prefix );

	fwprintf( out_file, L"%ls", out_buff.c_str() );
	if( is_ca_mode )
	{
		writembs(exit_ca_mode);
		pager_flush();
	}
	destroy();

}