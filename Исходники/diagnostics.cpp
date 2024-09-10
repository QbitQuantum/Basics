// initialize the diagnostics environment.
//
int diagnostics_init(
    int _flags, const char* stdout_prefix, const char* stderr_prefix
) {
    // Check to see if we have already been called
    if (diagnostics_initialized) {
        return ERR_INVALID_PARAM;
    }
    diagnostics_initialized = true;

    // Setup initial values
    flags = _flags;
    snprintf(stdout_log, sizeof(stdout_log), "%s.txt", stdout_prefix);
    snprintf(stdout_archive, sizeof(stdout_archive), "%s.old", stdout_prefix);
    snprintf(stderr_log, sizeof(stderr_log), "%s.txt", stderr_prefix);
    snprintf(stderr_archive, sizeof(stderr_archive), "%s.old", stderr_prefix);
    strcpy(boinc_dir, "");
    strcpy(boinc_install_dir, "");
    boinc_proxy_enabled = 0;
    strcpy(boinc_proxy, "");
    strcpy(symstore, "");

    // Check for invalid parameter combinations
    if ((flags & BOINC_DIAG_REDIRECTSTDERR) && (flags & BOINC_DIAG_REDIRECTSTDERROVERWRITE)) {
        return ERR_INVALID_PARAM;
    }

    if ((flags & BOINC_DIAG_REDIRECTSTDOUT) && (flags & BOINC_DIAG_REDIRECTSTDOUTOVERWRITE)) {
        return ERR_INVALID_PARAM;
    }


    // Archive any old stderr.txt and stdout.txt files, if requested
    if (flags & BOINC_DIAG_ARCHIVESTDERR) {
        boinc_copy(stderr_log, stderr_archive);
    }

    if (flags & BOINC_DIAG_ARCHIVESTDOUT) {
        boinc_copy(stdout_log, stdout_archive);
    }


    // Redirect stderr and/or stdout, if requested
    //
    if (flags & BOINC_DIAG_REDIRECTSTDERR) {
        file_size(stderr_log, stderr_file_size);
        stderr_file = freopen(stderr_log, "a", stderr);
        if (!stderr_file) {
            return ERR_FOPEN;
        }
        setbuf(stderr_file, 0);
    }

    if (flags & BOINC_DIAG_REDIRECTSTDERROVERWRITE) {
        stderr_file = freopen(stderr_log, "w", stderr);
        if (!stderr_file) {
            return ERR_FOPEN;
        }
        setbuf(stderr_file, 0);
    }

    if (flags & BOINC_DIAG_REDIRECTSTDOUT) {
        file_size(stdout_log, stdout_file_size);
        stdout_file = freopen(stdout_log, "a", stdout);
        if (!stdout_file) {
            return ERR_FOPEN;
        }
    }

    if (flags & BOINC_DIAG_REDIRECTSTDOUTOVERWRITE) {
        stdout_file = freopen(stdout_log, "w", stdout);
        if (!stdout_file) {
            return ERR_FOPEN;
        }
    }


#if defined(_WIN32)

#if defined(_DEBUG)

    _CrtSetReportHook(boinc_message_reporting);

    if (flags & BOINC_DIAG_MEMORYLEAKCHECKENABLED) {
        SET_CRT_DEBUG_FIELD(_CRTDBG_LEAK_CHECK_DF);
    }

    if (flags & BOINC_DIAG_HEAPCHECKENABLED) {
        if (flags & BOINC_DIAG_HEAPCHECKEVERYALLOC) {
            SET_CRT_DEBUG_FIELD(_CRTDBG_CHECK_ALWAYS_DF);
        } else {
            SET_CRT_DEBUG_FIELD(_CRTDBG_CHECK_EVERY_1024_DF);
        }
    }

    if (flags & BOINC_DIAG_BOINCAPPLICATION) {
        if (flags & BOINC_DIAG_MEMORYLEAKCHECKENABLED) {
            _CrtMemCheckpoint(&start_snapshot); 
        }
    }

#endif // defined(_DEBUG)

    // Initialize the thread list structure
    //   The data for this structure should be set by
    //   boinc_init or boinc_init_graphics.
    diagnostics_init_thread_list();

    diagnostics_init_unhandled_exception_monitor();

    diagnostics_init_message_monitor();

#endif // defined(_WIN32)


    // Install unhandled exception filters and signal traps.
    if (BOINC_SUCCESS != boinc_install_signal_handlers()) {
        return ERR_SIGNAL_OP;
    }


    // Store various pieces of inforation for future use.
    if (flags & BOINC_DIAG_BOINCAPPLICATION) {
        char    buf[256];
        char    proxy_address[256];
        int     proxy_port;
        MIOFILE mf;
        FILE*   p;
#ifdef _WIN32
        LONG    lReturnValue;
        HKEY    hkSetupHive;
        DWORD   dwSize = 0;
#endif

        strcpy(buf, "");
        strcpy(proxy_address, "");
        proxy_port = 0;

#ifndef _USING_FCGI_
        p = fopen(INIT_DATA_FILE, "r");
#else
        p = FCGI::fopen(INIT_DATA_FILE, "r");
#endif
 
		if (p) {
			mf.init_file(p);
			while(mf.fgets(buf, sizeof(buf))) {
				if (match_tag(buf, "</app_init_data>")) break;
				else if (parse_str(buf, "<boinc_dir>", boinc_dir, 256)) continue;
				else if (parse_str(buf, "<symstore>", symstore, 256)) continue;
				else if (match_tag(buf, "<use_http_proxy/>")) {
					boinc_proxy_enabled = true;
					continue;
				}
				else if (parse_str(buf, "<http_server_name>", proxy_address, 256)) continue;
				else if (parse_int(buf, "<http_server_port>", proxy_port)) continue;
			}
			fclose(p);
		}

        if (boinc_proxy_enabled) {
            int buffer_used = snprintf(boinc_proxy, sizeof(boinc_proxy), "%s:%d", proxy_address, proxy_port);
            if ((sizeof(boinc_proxy) == buffer_used) || (-1 == buffer_used)) { 
                boinc_proxy[sizeof(boinc_proxy)-1] = '\0';
            }
        }

#ifdef _WIN32
        // Lookup the location of where BOINC was installed to and store
        //   that for future use.
        lReturnValue = RegOpenKeyEx(
            HKEY_LOCAL_MACHINE, 
            _T("SOFTWARE\\Space Sciences Laboratory, U.C. Berkeley\\BOINC Setup"),  
	        0, 
            KEY_READ,
            &hkSetupHive
        );
        if (lReturnValue == ERROR_SUCCESS) {
            // How large does our buffer need to be?
            dwSize = sizeof(boinc_install_dir);

            lReturnValue = RegQueryValueEx(
                hkSetupHive,
                _T("INSTALLDIR"),
                NULL,
                NULL,
                (LPBYTE)&boinc_install_dir,
                &dwSize
            );
        }

        if (hkSetupHive) RegCloseKey(hkSetupHive);
#endif
    }

    return BOINC_SUCCESS;
}