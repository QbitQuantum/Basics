/**
  Parse the argument list, return the index of the first non-switch
  arguments.
 */
static int fish_parse_opt( int argc, char **argv, const char **cmd_ptr )
{
	int my_optind;
	int force_interactive=0;
		
	while( 1 )
	{
		static struct option
			long_options[] =
			{
				{
					"command", required_argument, 0, 'c' 
				}
				,
				{
					"debug-level", required_argument, 0, 'd' 
				}
				,
				{
					"interactive", no_argument, 0, 'i' 
				}
				,
				{
					"login", no_argument, 0, 'l' 
				}
				,
				{
					"no-execute", no_argument, 0, 'n' 
				}
				,
				{
					"profile", required_argument, 0, 'p' 
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
			
			case 'c':		
			{
				*cmd_ptr = optarg;				
				is_interactive_session = 0;
				break;
			}
			
			case 'd':		
			{
				char *end;
				int tmp;

				errno = 0;
				tmp = strtol(optarg, &end, 10);
				
				if( tmp >= 0 && tmp <=10 && !*end && !errno )
				{
					debug_level=tmp;
				}
				else
				{
					debug( 0, _(L"Invalid value '%s' for debug level switch"), optarg );
					exit_without_destructors(1);
				}
				break;
			}
			
			case 'h':
			{
				*cmd_ptr = "__fish_print_help fish";
				break;
			}
			
			case 'i':
			{
				force_interactive = 1;
				break;				
			}
			
			case 'l':
			{
				is_login=1;
				break;				
			}
			
			case 'n':
			{
				no_exec=1;
				break;				
			}
			
			case 'p':
			{
				profile = optarg;
				break;				
			}
			
			case 'v':
			{
				fwprintf( stderr, 
						  _(L"%s, version %s\n"), 
						  PACKAGE_NAME,
						  PACKAGE_VERSION );
				exit_without_destructors( 0 );				
			}
			
			case '?':
			{
				exit_without_destructors( 1 );
			}
			
		}		
	}

	my_optind = optind;
	
	is_login |= (strcmp( argv[0], "-fish") == 0);
		
	/*
	  We are an interactive session if we have not been given an
	  explicit command to execute, _and_ stdin is a tty.
	 */
	is_interactive_session &= (*cmd_ptr == 0);
	is_interactive_session &= (my_optind == argc);
	is_interactive_session &= isatty(STDIN_FILENO);	

	/*
	  We are also an interactive session if we have are forced-
	 */
	is_interactive_session |= force_interactive;

	return my_optind;
}