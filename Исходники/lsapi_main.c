static int cli_main( int argc, char * argv[] )
{

    static const char * ini_defaults[] = {
        "report_zend_debug",    "0",
        "display_errors",       "1",
        "register_argc_argv",   "1",
        "html_errors",          "0",
        "implicit_flush",       "1",
        "output_buffering",     "0",
        "max_execution_time",   "0",
        "max_input_time",       "-1",
        NULL
    };

    const char ** ini;
    char ** p = &argv[1];
    char ** argend= &argv[argc];
    int ret = -1;
    int c;
#if PHP_MAJOR_VERSION >= 7
	zend_string * psKey;
#endif
    lsapi_mode = 0;        /* enter CLI mode */

#ifdef PHP_WIN32
    _fmode = _O_BINARY;            /*sets default for file streams to binary */
    setmode(_fileno(stdin), O_BINARY);    /* make the stdio mode be binary */
    setmode(_fileno(stdout), O_BINARY);   /* make the stdio mode be binary */
    setmode(_fileno(stderr), O_BINARY);   /* make the stdio mode be binary */
#endif

    zend_first_try     {
        SG(server_context) = (void *) 1;

        zend_uv.html_errors = 0; /* tell the engine we're in non-html mode */
        CG(in_compilation) = 0; /* not initialized but needed for several options */
        SG(options) |= SAPI_OPTION_NO_CHDIR;
        
#if PHP_MAJOR_VERSION < 7
        EG(uninitialized_zval_ptr) = NULL;
#endif
        for( ini = ini_defaults; *ini; ini+=2 ) {
#if PHP_MAJOR_VERSION >= 7
			psKey = zend_string_init(*ini, strlen( *ini ), 1);
            zend_alter_ini_entry_chars(psKey,
                                (char *)*(ini+1), strlen( *(ini+1) ),
                                PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
			zend_string_release(psKey);
#else
            zend_alter_ini_entry( (char *)*ini, strlen( *ini )+1,
                                (char *)*(ini+1), strlen( *(ini+1) ),
                                PHP_INI_SYSTEM, PHP_INI_STAGE_ACTIVATE);
#endif
        }

        while (( p < argend )&&(**p == '-' )) {
            c = *((*p)+1);
            ++p;
            switch( c ) {
            case 'q':
                break;
            case 'i':
                if (php_request_startup() != FAILURE) {
                    php_print_info(0xFFFFFFFF);
#ifdef PHP_OUTPUT_NEWAPI
                    php_output_end_all();
#else
                    php_end_ob_buffers(1);
#endif
                    php_request_shutdown( NULL );
                    ret = 0;
                }
                break;
            case 'v':
                if (php_request_startup() != FAILURE) {
#if ZEND_DEBUG
                    php_printf("PHP %s (%s) (built: %s %s) (DEBUG)\nCopyright (c) 1997-2017 The PHP Group\n%s", PHP_VERSION, sapi_module.name, __DATE__, __TIME__, get_zend_version());
#else
                    php_printf("PHP %s (%s) (built: %s %s)\nCopyright (c) 1997-2017 The PHP Group\n%s", PHP_VERSION, sapi_module.name, __DATE__, __TIME__, get_zend_version());
#endif
#ifdef PHP_OUTPUT_NEWAPI
                    php_output_end_all();
#else
                    php_end_ob_buffers(1);
#endif
                    php_request_shutdown( NULL );
                    ret = 0;
                }
                break;
            case 'c':
                ++p;
            /* fall through */
            case 's':
                break;
            case 'l':
                source_highlight = 2;
                break;
            case 'h':
            case '?':
            default:
                cli_usage();
                ret = 0;
                break;

            }
        }
        if ( ret == -1 ) {
            if ( *p ) {
                zend_file_handle file_handle;
                memset(&file_handle, 0, sizeof(file_handle));
                file_handle.type = ZEND_HANDLE_FP;
                file_handle.handle.fp = VCWD_FOPEN(*p, "rb");

                if ( file_handle.handle.fp ) {
                    script_filename = *p;
                    php_self = *p;

                    SG(request_info).path_translated = estrdup(*p);
                    SG(request_info).argc = argc - (p - argv);
                    SG(request_info).argv = p;

                    if (php_request_startup() == FAILURE ) {
                        fclose( file_handle.handle.fp );
                        ret = 2;
                    } else {
                        if (source_highlight == 1) {
                            zend_syntax_highlighter_ini syntax_highlighter_ini;

                            php_get_highlight_struct(&syntax_highlighter_ini);
                            highlight_file(SG(request_info).path_translated, &syntax_highlighter_ini);
                        } else if (source_highlight == 2) {
                            file_handle.filename = *p;
                            file_handle.free_filename = 0;
                            file_handle.opened_path = NULL;
                            ret = php_lint_script(&file_handle);
                            if (ret==SUCCESS) {
                                zend_printf("No syntax errors detected in %s\n", file_handle.filename);
                            } else {
                                zend_printf("Errors parsing %s\n", file_handle.filename);
                            }

                        } else {
                            file_handle.filename = *p;
                            file_handle.free_filename = 0;
                            file_handle.opened_path = NULL;

                            php_execute_script(&file_handle);
                            ret = EG(exit_status);
                       }

                        php_request_shutdown( NULL );
                    }
                } else {
                    php_printf("Could not open input file: %s.\n", *p);
                }
            } else {
                cli_usage();
            }
        }

    }zend_end_try();

    php_module_shutdown();

#ifdef ZTS
    tsrm_shutdown();
#endif
    return ret;
}