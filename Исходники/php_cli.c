int main(int argc, char *argv[])
#endif
{
#if defined(PHP_WIN32)
# ifdef PHP_CLI_WIN32_NO_CONSOLE
	int argc = __argc;
	char **argv = __argv;
# else
	int num_args;
	wchar_t **argv_wide;
	char **argv_save = argv;
	BOOL using_wide_argv = 0;
# endif
#endif

	int c;
	int exit_status = SUCCESS;
	int module_started = 0, sapi_started = 0;
	char *php_optarg = NULL;
	int php_optind = 1, use_extended_info = 0;
	char *ini_path_override = NULL;
	char *ini_entries = NULL;
	int ini_entries_len = 0;
	int ini_ignore = 0;
	sapi_module_struct *sapi_module = &cli_sapi_module;

	/*
	 * Do not move this initialization. It needs to happen before argv is used
	 * in any way.
	 */
	argv = save_ps_args(argc, argv);

	cli_sapi_module.additional_functions = additional_functions;

#if defined(PHP_WIN32) && defined(_DEBUG) && defined(PHP_WIN32_DEBUG_HEAP)
	{
		int tmp_flag;
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
		_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
		tmp_flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
		tmp_flag |= _CRTDBG_DELAY_FREE_MEM_DF;
		tmp_flag |= _CRTDBG_LEAK_CHECK_DF;

		_CrtSetDbgFlag(tmp_flag);
	}
#endif

#ifdef HAVE_SIGNAL_H
#if defined(SIGPIPE) && defined(SIG_IGN)
	signal(SIGPIPE, SIG_IGN); /* ignore SIGPIPE in standalone mode so
								that sockets created via fsockopen()
								don't kill PHP if the remote site
								closes it.  in apache|apxs mode apache
								does that for us!  [email protected]
								20000419 */
#endif
#endif


#ifdef ZTS
	tsrm_startup(1, 1, 0, NULL);
	(void)ts_resource(0);
	ZEND_TSRMLS_CACHE_UPDATE();
#endif

	zend_signal_startup();

#ifdef PHP_WIN32
	_fmode = _O_BINARY;			/*sets default for file streams to binary */
	setmode(_fileno(stdin), O_BINARY);		/* make the stdio mode be binary */
	setmode(_fileno(stdout), O_BINARY);		/* make the stdio mode be binary */
	setmode(_fileno(stderr), O_BINARY);		/* make the stdio mode be binary */
#endif

	while ((c = php_getopt(argc, argv, OPTIONS, &php_optarg, &php_optind, 0, 2))!=-1) {
		switch (c) {
			case 'c':
				if (ini_path_override) {
					free(ini_path_override);
				}
 				ini_path_override = strdup(php_optarg);
				break;
			case 'n':
				ini_ignore = 1;
				break;
			case 'd': {
				/* define ini entries on command line */
				int len = (int)strlen(php_optarg);
				char *val;

				if ((val = strchr(php_optarg, '='))) {
					val++;
					if (!isalnum(*val) && *val != '"' && *val != '\'' && *val != '\0') {
						ini_entries = realloc(ini_entries, ini_entries_len + len + sizeof("\"\"\n\0"));
						memcpy(ini_entries + ini_entries_len, php_optarg, (val - php_optarg));
						ini_entries_len += (int)(val - php_optarg);
						memcpy(ini_entries + ini_entries_len, "\"", 1);
						ini_entries_len++;
						memcpy(ini_entries + ini_entries_len, val, len - (val - php_optarg));
						ini_entries_len += len - (int)(val - php_optarg);
						memcpy(ini_entries + ini_entries_len, "\"\n\0", sizeof("\"\n\0"));
						ini_entries_len += sizeof("\n\0\"") - 2;
					} else {
						ini_entries = realloc(ini_entries, ini_entries_len + len + sizeof("\n\0"));
						memcpy(ini_entries + ini_entries_len, php_optarg, len);
						memcpy(ini_entries + ini_entries_len + len, "\n\0", sizeof("\n\0"));
						ini_entries_len += len + sizeof("\n\0") - 2;
					}
				} else {
					ini_entries = realloc(ini_entries, ini_entries_len + len + sizeof("=1\n\0"));
					memcpy(ini_entries + ini_entries_len, php_optarg, len);
					memcpy(ini_entries + ini_entries_len + len, "=1\n\0", sizeof("=1\n\0"));
					ini_entries_len += len + sizeof("=1\n\0") - 2;
				}
				break;
			}
#ifndef PHP_CLI_WIN32_NO_CONSOLE
			case 'S':
				sapi_module = &cli_server_sapi_module;
				cli_server_sapi_module.additional_functions = server_additional_functions;
				break;
#endif
			case 'h': /* help & quit */
			case '?':
				php_cli_usage(argv[0]);
				goto out;
			case 'i': case 'v': case 'm':
				sapi_module = &cli_sapi_module;
				goto exit_loop;
			case 'e': /* enable extended info output */
				use_extended_info = 1;
				break;
		}
	}
exit_loop:

	sapi_module->ini_defaults = sapi_cli_ini_defaults;
	sapi_module->php_ini_path_override = ini_path_override;
	sapi_module->phpinfo_as_text = 1;
	sapi_module->php_ini_ignore_cwd = 1;
	sapi_startup(sapi_module);
	sapi_started = 1;

	sapi_module->php_ini_ignore = ini_ignore;

	sapi_module->executable_location = argv[0];

	if (sapi_module == &cli_sapi_module) {
		if (ini_entries) {
			ini_entries = realloc(ini_entries, ini_entries_len + sizeof(HARDCODED_INI));
			memmove(ini_entries + sizeof(HARDCODED_INI) - 2, ini_entries, ini_entries_len + 1);
			memcpy(ini_entries, HARDCODED_INI, sizeof(HARDCODED_INI) - 2);
		} else {
			ini_entries = malloc(sizeof(HARDCODED_INI));
			memcpy(ini_entries, HARDCODED_INI, sizeof(HARDCODED_INI));
		}
		ini_entries_len += sizeof(HARDCODED_INI) - 2;
	}

	sapi_module->ini_entries = ini_entries;

	/* startup after we get the above ini override se we get things right */
	if (sapi_module->startup(sapi_module) == FAILURE) {
		/* there is no way to see if we must call zend_ini_deactivate()
		 * since we cannot check if EG(ini_directives) has been initialised
		 * because the executor's constructor does not set initialize it.
		 * Apart from that there seems no need for zend_ini_deactivate() yet.
		 * So we goto out_err.*/
		exit_status = 1;
		goto out;
	}
	module_started = 1;

#if defined(PHP_WIN32) && !defined(PHP_CLI_WIN32_NO_CONSOLE)
	php_win32_cp_cli_setup();
	orig_cp = (php_win32_cp_get_orig())->id;
	/* Ignore the delivered argv and argc, read from W API. This place
		might be too late though, but this is the earliest place ATW
		we can access the internal charset information from PHP. */
	argv_wide = CommandLineToArgvW(GetCommandLineW(), &num_args);
	PHP_WIN32_CP_W_TO_A_ARRAY(argv_wide, num_args, argv, argc)
	using_wide_argv = 1;

	SetConsoleCtrlHandler(php_cli_win32_ctrl_handler, TRUE);
#endif

	/* -e option */
	if (use_extended_info) {
		CG(compiler_options) |= ZEND_COMPILE_EXTENDED_INFO;
	}

	zend_first_try {
#ifndef PHP_CLI_WIN32_NO_CONSOLE
		if (sapi_module == &cli_sapi_module) {
#endif
			exit_status = do_cli(argc, argv);
#ifndef PHP_CLI_WIN32_NO_CONSOLE
		} else {
			exit_status = do_cli_server(argc, argv);
		}
#endif
	} zend_end_try();
out:
	if (ini_path_override) {
		free(ini_path_override);
	}
	if (ini_entries) {
		free(ini_entries);
	}
	if (module_started) {
		php_module_shutdown();
	}
	if (sapi_started) {
		sapi_shutdown();
	}
#ifdef ZTS
	tsrm_shutdown();
#endif

#if defined(PHP_WIN32) && !defined(PHP_CLI_WIN32_NO_CONSOLE)
	(void)php_win32_cp_cli_restore();

	if (using_wide_argv) {
		PHP_WIN32_FREE_ARRAY(argv, argc);
		LocalFree(argv_wide);
	}
	argv = argv_save;
#endif
	/*
	 * Do not move this de-initialization. It needs to happen right before
	 * exiting.
	 */
	cleanup_ps_args(argv);
	exit(exit_status);
}