/**
   The set builtin. Creates, updates and erases environment variables
   and environemnt variable arrays.
*/
static int builtin_set( parser_t &parser, wchar_t **argv ) 
{
	
	/**
	   Variables used for parsing the argument list
	*/
	static const struct woption
		long_options[] = 
		{
			{ 
				L"export", no_argument, 0, 'x' 
			}
			,
			{ 
				L"global", no_argument, 0, 'g' 
			}
			,
			{ 
				L"local", no_argument, 0, 'l'  
			}
			,
			{ 
				L"erase", no_argument, 0, 'e'  
			}
			,
			{ 
				L"names", no_argument, 0, 'n' 
			} 
			,
			{ 
				L"unexport", no_argument, 0, 'u' 
			} 
			,
			{ 
				L"universal", no_argument, 0, 'U'
			}
            ,
			{ 
				L"long", no_argument, 0, 'L'
			} 
			,
			{ 
				L"query", no_argument, 0, 'q' 
			} 
			,
			{ 
				L"help", no_argument, 0, 'h' 
			} 
			,
			{ 
				0, 0, 0, 0 
			}
		}
	;
	
	const wchar_t *short_options = L"+xglenuULqh";

	int argc = builtin_count_args(argv);

	/*
	  Flags to set the work mode
	*/
	int local = 0, global = 0, exportv = 0;
	int erase = 0, list = 0, unexport=0;
	int universal = 0, query=0;
	bool shorten_ok = true;

	/*
	  Variables used for performing the actual work
	*/
	wchar_t *dest = 0;
	int retcode=0;
	int scope;
	int slice=0;
	int i;
	
	wchar_t *bad_char;
	
	
	/* Parse options to obtain the requested operation and the modifiers */
	woptind = 0;
	while (1) 
	{
		int c = wgetopt_long(argc, argv, short_options, long_options, 0);

		if (c == -1) 
		{
			break;
		}
    
		switch(c) 
		{
			case 0:
				break;

			case 'e':
				erase = 1;
				break;

			case 'n':
				list = 1;
				break;

			case 'x':
				exportv = 1;
				break;

			case 'l':
				local = 1;
				break;

			case 'g':
				global = 1;
				break;

			case 'u':
				unexport = 1;
				break;

			case 'U':
				universal = 1;
				break;
            
            case 'L':
                shorten_ok = false;
                break;

			case 'q':
				query = 1;
				break;

			case 'h':
				builtin_print_help( parser, argv[0], stdout_buffer );
				return 0;

			case '?':
				builtin_unknown_option( parser, argv[0], argv[woptind-1] );
				return 1;

			default:
				break;
		}
	}

	/*
	  Ok, all arguments have been parsed, let's validate them
	*/

	/*
	  If we are checking the existance of a variable (-q) we can not
	  also specify scope
	*/

	if( query && (erase || list) )
	{
		append_format(stderr_buffer,
				  BUILTIN_ERR_COMBO,
				  argv[0] );
		
		builtin_print_help( parser, argv[0], stderr_buffer );
		return 1;
	}
	

	/* We can't both list and erase varaibles */
	if( erase && list ) 
	{
		append_format(stderr_buffer,
				  BUILTIN_ERR_COMBO,
				  argv[0] );		

		builtin_print_help( parser, argv[0], stderr_buffer );
		return 1;
	}

	/*
	  Variables can only have one scope
	*/
	if( local + global + universal > 1 ) 
	{
		append_format(stderr_buffer,
				   BUILTIN_ERR_GLOCAL,
				   argv[0] );
		builtin_print_help( parser, argv[0], stderr_buffer );
		return 1;
	}

	/*
	  Variables can only have one export status
	*/
	if( exportv && unexport ) 
	{
		append_format(stderr_buffer,
				   BUILTIN_ERR_EXPUNEXP,
				   argv[0] );
		builtin_print_help( parser, argv[0], stderr_buffer );
		return 1;
	}

	/*
	  Calculate the scope value for variable assignement
	*/
	scope = (local ? ENV_LOCAL : 0) | (global ? ENV_GLOBAL : 0) | (exportv ? ENV_EXPORT : 0) | (unexport ? ENV_UNEXPORT : 0) | (universal ? ENV_UNIVERSAL:0) | ENV_USER; 

	if( query )
	{
		/*
		  Query mode. Return the number of variables that do not exist
		  out of the specified variables.
		*/
		int i;
		for( i=woptind; i<argc; i++ )
		{
			wchar_t *arg = argv[i];
			int slice=0;

			if( !(dest = wcsdup(arg)))
			{
				DIE_MEM();		
			}

			if( wcschr( dest, L'[' ) )
			{
				slice = 1;
				*wcschr( dest, L'[' )=0;
			}
			
			if( slice )
			{
				std::vector<long> indexes;
				wcstring_list_t result;
				size_t j;
				
                env_var_t dest_str = env_get_string(dest);
                if (! dest_str.missing())
                    tokenize_variable_array( dest_str, result );
								
				if( !parse_index( indexes, arg, dest, result.size() ) )
				{
					builtin_print_help( parser, argv[0], stderr_buffer );
					retcode = 1;
					break;
				}
				for( j=0; j < indexes.size() ; j++ )
				{
					long idx = indexes[j];
					if( idx < 1 || (size_t)idx > result.size() )
					{
						retcode++;
					}
				}
			}
			else
			{
				if( !env_exist( arg, scope ) )
				{
					retcode++;
				}
			}
			
			free( dest );
			
		}
		return retcode;
	}
	
	if( list ) 
	{
		/* Maybe we should issue an error if there are any other arguments? */
		print_variables(0, 0, shorten_ok, scope);
		return 0;
	} 
	
	if( woptind == argc )
	{
		/*
		  Print values of variables
		*/

		if( erase ) 
		{
			append_format(stderr_buffer,
					   _(L"%ls: Erase needs a variable name\n"), 
					   argv[0] );
			
			builtin_print_help( parser, argv[0], stderr_buffer );
			retcode = 1;
		}
		else
		{
			print_variables( 1, 1, shorten_ok, scope );
		}
		
		return retcode;
	}

	if( !(dest = wcsdup(argv[woptind])))
	{
		DIE_MEM();		
	}

	if( wcschr( dest, L'[' ) )
	{
		slice = 1;
		*wcschr( dest, L'[' )=0;
	}
	
	if( !wcslen( dest ) )
	{
		free( dest );
		append_format(stderr_buffer, BUILTIN_ERR_VARNAME_ZERO, argv[0] );
		builtin_print_help( parser, argv[0], stderr_buffer );
		return 1;
	}
	
	if( (bad_char = wcsvarname( dest ) ) )
	{
		append_format(stderr_buffer, BUILTIN_ERR_VARCHAR, argv[0], *bad_char );
		builtin_print_help( parser, argv[0], stderr_buffer );
		free( dest );
		return 1;
	}
	
	if( slice && erase && (scope != ENV_USER) )
	{
		free( dest );
		append_format(stderr_buffer, _(L"%ls: Can not specify scope when erasing array slice\n"), argv[0] );
		builtin_print_help( parser, argv[0], stderr_buffer );
		return 1;
	}
	
	/*
	  set assignment can work in two modes, either using slices or
	  using the whole array. We detect which mode is used here.
	*/
	
	if( slice )
	{

		/*
		  Slice mode
		*/
		int idx_count, val_count;
		wcstring_list_t values;
		std::vector<long> indexes;
		wcstring_list_t result;
		
        const env_var_t dest_str = env_get_string(dest);
        if (! dest_str.missing())
            tokenize_variable_array( dest_str, result );
		
		for( ; woptind<argc; woptind++ )
		{			
			if( !parse_index( indexes, argv[woptind], dest, result.size() ) )
			{
				builtin_print_help( parser, argv[0], stderr_buffer );
				retcode = 1;
				break;
			}
			
			val_count = argc-woptind-1;
			idx_count = indexes.size();

			if( !erase )
			{
				if( val_count < idx_count )
				{
					append_format(stderr_buffer, _(BUILTIN_SET_ARG_COUNT), argv[0] );
					builtin_print_help( parser, argv[0], stderr_buffer );
					retcode=1;
					break;
				}
				if( val_count == idx_count )
				{
					woptind++;
					break;
				}
			}
		}		

		if( !retcode )
		{
			/*
			  Slice indexes have been calculated, do the actual work
			*/

			if( erase )
			{
				erase_values(result, indexes);
				my_env_set( dest, result, scope);
			}
			else
			{
				wcstring_list_t value;
//				al_init(&value);

				while( woptind < argc ) 
				{
					value.push_back( argv[woptind++] );
				}

				if( update_values( result, 
								   indexes,
								   value ) )
				{
					append_format(stderr_buffer, L"%ls: ", argv[0] );
					append_format(stderr_buffer, ARRAY_BOUNDS_ERR );
					stderr_buffer.push_back(L'\n');
				}
				
				my_env_set(dest, result, scope);
								
//				al_destroy( &value );
								
			}			
		}

//		al_foreach( &result, &free );
//		al_destroy( &result );

//		al_destroy(&indexes);
//		al_destroy(&values);
		
	}
	else
	{
		woptind++;
		
		/*
		  No slicing
		*/
		if( erase )
		{
			if( woptind != argc )
			{
				append_format(stderr_buffer, 
						   _(L"%ls: Values cannot be specfied with erase\n"),
						   argv[0] );
				builtin_print_help( parser, argv[0], stderr_buffer );
				retcode=1;
			}
			else
			{
				retcode = env_remove( dest, scope );
			}
		}
		else
		{
            wcstring_list_t val;
			for( i=woptind; i<argc; i++ )
                val.push_back(argv[i]);
			retcode = my_env_set( dest, val, scope );
		}		
	}
	
	free( dest );
	
	return retcode;

}