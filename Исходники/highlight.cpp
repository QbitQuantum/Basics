// This function does I/O
static void tokenize( const wchar_t * const buff, std::vector<int> &color, const int pos, wcstring_list_t *error, const wcstring &working_directory, const env_vars &vars) {
    ASSERT_IS_BACKGROUND_THREAD();
    
	wcstring cmd;    
	int had_cmd=0;
	wcstring last_cmd;
	int len;

	int accept_switches = 1;
	
	int use_function = 1;
	int use_command = 1;
	int use_builtin = 1;
	
	CHECK( buff, );

	len = wcslen(buff);

	if( !len )
		return;

    std::fill(color.begin(), color.end(), -1); 

    tokenizer tok;
	for( tok_init( &tok, buff, TOK_SHOW_COMMENTS | TOK_SQUASH_ERRORS );
		tok_has_next( &tok );
		tok_next( &tok ) )
	{	
		int last_type = tok_last_type( &tok );
		
		switch( last_type )
		{
			case TOK_STRING:
			{
				if( had_cmd )
				{
					
					/*Parameter */
					wchar_t *param = tok_last( &tok );
					if( param[0] == L'-' )
					{
						if (wcscmp( param, L"--" ) == 0 )
						{
							accept_switches = 0;
							color.at(tok_get_pos( &tok )) = HIGHLIGHT_PARAM;
						}
						else if( accept_switches )
						{
							if( complete_is_valid_option( last_cmd.c_str(), param, error, false /* no autoload */ ) )
								color.at(tok_get_pos( &tok )) = HIGHLIGHT_PARAM;
							else
								color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
						}
						else
						{
							color.at(tok_get_pos( &tok )) = HIGHLIGHT_PARAM;
						}
					}
					else
					{
						color.at(tok_get_pos( &tok )) = HIGHLIGHT_PARAM;
					}					

					if( cmd == L"cd" )
					{
                        wcstring dir = tok_last( &tok );
                        if (expand_one(dir, EXPAND_SKIP_CMDSUBST))
						{
							int is_help = string_prefixes_string(dir, L"--help") || string_prefixes_string(dir, L"-h");
							if( !is_help && ! is_potential_cd_path(dir, working_directory, NULL))
							{
                                color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;							
							}
						}
					}
					
                    /* Highlight the parameter. highlight_param wants to write one more color than we have characters (hysterical raisins) so allocate one more in the vector. But don't copy it back. */
                    const wcstring param_str = param;
                    int tok_pos = tok_get_pos(&tok);
                    
                    std::vector<int>::const_iterator where = color.begin() + tok_pos;
                    std::vector<int> subcolors(where, where + param_str.size());
                    subcolors.push_back(-1);                
                    highlight_param(param_str, subcolors, pos-tok_pos, error);
                                        
                    /* Copy the subcolors back into our colors array */
                    std::copy(subcolors.begin(), subcolors.begin() + param_str.size(), color.begin() + tok_pos);
				}
				else
				{ 
					/*
					 Command. First check that the command actually exists.
					 */
                    cmd = tok_last( &tok );
                    bool expanded = expand_one(cmd, EXPAND_SKIP_CMDSUBST | EXPAND_SKIP_VARIABLES);
					if (! expanded || has_expand_reserved(cmd.c_str()))
					{
						color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
					}
					else
					{
						bool is_cmd = false;
						int is_subcommand = 0;
						int mark = tok_get_pos( &tok );
						color.at(tok_get_pos( &tok )) = HIGHLIGHT_COMMAND;
						
						if( parser_keywords_is_subcommand( cmd ) )
						{
							
							int sw;
							
							if( cmd == L"builtin")
							{
								use_function = 0;
								use_command  = 0;
								use_builtin  = 1;
							}
							else if( cmd == L"command")
							{
								use_command  = 1;
								use_function = 0;
								use_builtin  = 0;
							}
							
							tok_next( &tok );
							
							sw = parser_keywords_is_switch( tok_last( &tok ) );
							
							if( !parser_keywords_is_block( cmd ) &&
							   sw == ARG_SWITCH )
							{
								/* 
								 The 'builtin' and 'command' builtins
								 are normally followed by another
								 command, but if they are invoked
								 with a switch, they aren't.
								 
								 */
								use_command  = 1;
								use_function = 1;
								use_builtin  = 2;
							}
							else
							{
								if( sw == ARG_SKIP )
								{
									color.at(tok_get_pos( &tok )) = HIGHLIGHT_PARAM;
									mark = tok_get_pos( &tok );
								}
								
								is_subcommand = 1;
							}
							tok_set_pos( &tok, mark );
						}
						
						if( !is_subcommand )
						{
							/*
							 OK, this is a command, it has been
							 successfully expanded and everything
							 looks ok. Lets check if the command
							 exists.
							 */
							
							/*
							 First check if it is a builtin or
							 function, since we don't have to stat
							 any files for that
							 */
							if (! is_cmd && use_builtin )
								is_cmd = builtin_exists( cmd );
							
							if (! is_cmd && use_function )
								is_cmd = function_exists_no_autoload( cmd, vars );
							
							/*
							 Moving on to expensive tests
							 */
							
							/*
							 Check if this is a regular command
							 */
							if (! is_cmd && use_command )
                            {
                                wcstring tmp;
								is_cmd = path_get_path_string( cmd, tmp, vars );
                            }
							
                            /* Maybe it is a path for a implicit cd command. */
                            if (! is_cmd)
                            {
                                if (use_builtin || (use_function && function_exists_no_autoload( L"cd", vars)))
                                    is_cmd = path_can_be_implicit_cd(cmd, NULL, working_directory.c_str());
                            }
                            
							if( is_cmd )
							{								
								color.at(tok_get_pos( &tok )) = HIGHLIGHT_COMMAND;
							}
							else
							{
								if( error ) {
                                    error->push_back(format_string(L"Unknown command \'%ls\'", cmd.c_str()));
                                }
								color.at(tok_get_pos( &tok )) = (HIGHLIGHT_ERROR);
							}
							had_cmd = 1;
						}
						
						if( had_cmd )
						{
							last_cmd = tok_last( &tok );
						}
					}
					
				}
				break;
			}
				
			case TOK_REDIRECT_NOCLOB:
			case TOK_REDIRECT_OUT:
			case TOK_REDIRECT_IN:
			case TOK_REDIRECT_APPEND:
			case TOK_REDIRECT_FD:
			{
				if( !had_cmd )
				{
					color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
					if( error )
                        error->push_back(L"Redirection without a command");
					break;
				}
				
                wcstring target_str;
				const wchar_t *target=NULL;
				
				color.at(tok_get_pos( &tok )) = HIGHLIGHT_REDIRECTION;
				tok_next( &tok );
				
				/*
				 Check that we are redirecting into a file
				 */
				
				switch( tok_last_type( &tok ) )
				{
					case TOK_STRING:
					{
                        target_str = tok_last( &tok );
                        if (expand_one(target_str, EXPAND_SKIP_CMDSUBST)) {
                            target = target_str.c_str();
                        }
						/*
						 Redirect filename may contain a cmdsubst. 
						 If so, it will be ignored/not flagged.
						 */
					}
						break;
					default:
					{
                        size_t pos = tok_get_pos(&tok);
                        if (pos < color.size()) {
                            color.at(pos) = HIGHLIGHT_ERROR;
                        }
						if( error )
                            error->push_back(L"Invalid redirection");
					}
						
				}
				
				if( target != 0 )
				{
                    wcstring dir = target;
                    size_t slash_idx = dir.find_last_of(L'/');
					struct stat buff;
					/* 
					 If file is in directory other than '.', check
					 that the directory exists.
					 */
					if( slash_idx != wcstring::npos )
					{
						dir.resize(slash_idx);
						if( wstat( dir, &buff ) == -1 )
						{
							color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
							if( error )
                                error->push_back(format_string(L"Directory \'%ls\' does not exist", dir.c_str()));
							
						}
					}
					
					/*
					 If the file is read from or appended to, check
					 if it exists.
					 */
					if( last_type == TOK_REDIRECT_IN || 
					   last_type == TOK_REDIRECT_APPEND )
					{
						if( wstat( target, &buff ) == -1 )
						{
							color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
							if( error )
                                error->push_back(format_string(L"File \'%ls\' does not exist", target));
						}
					}
					if( last_type == TOK_REDIRECT_NOCLOB )
					{
						if( wstat( target, &buff ) != -1 )
						{
							color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
							if( error )
                                error->push_back(format_string(L"File \'%ls\' exists", target));
						}
					}
				}
				break;
			}
				
			case TOK_PIPE:
			case TOK_BACKGROUND:
			{
				if( had_cmd )
				{
					color.at(tok_get_pos( &tok )) = HIGHLIGHT_END;
					had_cmd = 0;
					use_command  = 1;
					use_function = 1;
					use_builtin  = 1;
					accept_switches = 1;
				}
				else
				{
					color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;					
					if( error )
                        error->push_back(L"No job to put in background" );
				}
				
				break;
			}
				
			case TOK_END:
			{
				color.at(tok_get_pos( &tok )) = HIGHLIGHT_END;
				had_cmd = 0;
				use_command  = 1;
				use_function = 1;
				use_builtin  = 1;
				accept_switches = 1;
				break;
			}
				
			case TOK_COMMENT:
			{
				color.at(tok_get_pos( &tok )) = HIGHLIGHT_COMMENT;
				break;
			}
				
			case TOK_ERROR:
			default:
			{
				/*
				 If the tokenizer reports an error, highlight it as such.
				 */
				if( error )
                    error->push_back(tok_last( &tok));
				color.at(tok_get_pos( &tok )) = HIGHLIGHT_ERROR;
				break;				
			}			
		}
	}
    tok_destroy( &tok );
}