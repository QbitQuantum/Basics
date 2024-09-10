int WINAPI WinMain(HINSTANCE hThisInst, HINSTANCE /*hPrevInst*/, LPSTR lpszArgs, int nWndMode)
{
/**************************************
 *
 *      W i n M a i n
 *
 **************************************
 *
 * Functional description
 *      Run the server with NT named
 *      pipes and/or TCP/IP sockets.
 *
 **************************************/
	hInst = hThisInst;

	// We want server to crash without waiting for feedback from the user
	try
	{
		if (!Config::getBugcheckAbort())
			SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	}
	catch (Firebird::fatal_exception& e)
	{
		MessageBox(NULL, e.what(), "Firebird server failure",
			MB_OK | MB_ICONHAND | MB_SYSTEMMODAL  | MB_DEFAULT_DESKTOP_ONLY);
		return STARTUP_ERROR; // see /jrd/common.h
	}
	catch (Firebird::status_exception& e)
	{
		TEXT buffer[BUFFER_LARGE];
		const ISC_STATUS* vector = e.value();
		if (! (vector && fb_interpret(buffer, sizeof(buffer), &vector)))
		{
			strcpy(buffer, "Unknown internal failure");
		}

		MessageBox(NULL, buffer, "Firebird server failure",
			MB_OK | MB_ICONHAND | MB_SYSTEMMODAL  | MB_DEFAULT_DESKTOP_ONLY);
		return STARTUP_ERROR; // see /jrd/common.h
	}

#ifdef SUPERSERVER
	server_flag = SRVR_multi_client;
#else
	server_flag = 0;
#endif

#ifdef SUPERSERVER
	SetProcessAffinityMask(GetCurrentProcess(), static_cast<DWORD>(Config::getCpuAffinityMask()));
#endif

	protocol_inet[0] = 0;
	protocol_wnet[0] = 0;

	strcpy(instance, FB_DEFAULT_INSTANCE);

	const HANDLE connection_handle = parse_args(lpszArgs, &server_flag);

#ifdef SUPERSERVER
	// get priority class from the config file
	int priority = Config::getProcessPriorityLevel();

	// override it, if necessary
	if (server_flag & SRVR_high_priority) {
		priority = 1;
	}

	// set priority class
	if (priority > 0) {
		SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	}
	else if (priority < 0) {
		SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);
	}
#endif

	TEXT mutex_name[MAXPATHLEN];
	fb_utils::snprintf(mutex_name, sizeof(mutex_name), SERVER_MUTEX, instance);
	fb_utils::prefix_kernel_object_name(mutex_name, sizeof(mutex_name));
	CreateMutex(ISC_get_security_desc(), FALSE, mutex_name);

	// Initialize the service

	ISC_signal_init();
	Firebird::FpeControl::maskAll();

	int nReturnValue = 0;
	ISC_STATUS_ARRAY status_vector;
	fb_utils::init_status(status_vector);

	fb_shutdown_callback(0, wait_threads, fb_shut_finish, NULL);

	if (connection_handle != INVALID_HANDLE_VALUE)
	{
		rem_port* port = 0;

		if (server_flag & SRVR_inet)
		{
			port = INET_reconnect((SOCKET) connection_handle, status_vector);

			if (port)
			{
				SRVR_multi_thread(port, server_flag);
				port = NULL;
			}
		}
		else if (server_flag & SRVR_wnet)
			port = WNET_reconnect(connection_handle, status_vector);
		else if (server_flag & SRVR_xnet)
			port = XNET_reconnect((ULONG) connection_handle, status_vector);

		if (port) {
			service_connection(port);
		}
		else if (status_vector[1])
			gds__log_status(0, status_vector);

		fb_shutdown(5 * 1000 /*5 seconds*/, fb_shutrsn_no_connection);
	}
	else if (!(server_flag & SRVR_non_service))
	{
		Firebird::string service_name;
		service_name.printf(REMOTE_SERVICE, instance);

		CNTL_init(start_connections_thread, instance);

		const SERVICE_TABLE_ENTRY service_table[] =
		{
			{const_cast<char*>(service_name.c_str()), CNTL_main_thread},
			{NULL, NULL}
		};

		// BRS There is a error in MinGW (3.1.0) headers
		// the parameter of StartServiceCtrlDispatcher is declared const in msvc headers
#if defined(MINGW)
		if (!StartServiceCtrlDispatcher(const_cast<SERVICE_TABLE_ENTRY*>(service_table)))
		{
#else
		if (!StartServiceCtrlDispatcher(service_table))
		{
#endif
			if (GetLastError() != ERROR_CALL_NOT_IMPLEMENTED) {
				CNTL_shutdown_service("StartServiceCtrlDispatcher failed");
			}
			server_flag |= SRVR_non_service;
		}
	}
	else
	{
		start_connections_thread(0);
		nReturnValue = WINDOW_main(hThisInst, nWndMode, server_flag);
	}

#ifdef DEBUG_GDS_ALLOC
	// In Debug mode - this will report all server-side memory leaks
	// due to remote access

	//gds_alloc_report(0, __FILE__, __LINE__);
	Firebird::PathName name = fb_utils::getPrefix(fb_utils::FB_DIR_LOG, "memdebug.log");
	FILE* file = fopen(name.c_str(), "w+t");
	if (file)
	{
		fprintf(file, "Global memory pool allocated objects\n");
		getDefaultMemoryPool()->print_contents(file);
		fclose(file);
	}
#endif

	return nReturnValue;
}


THREAD_ENTRY_DECLARE process_connection_thread(THREAD_ENTRY_PARAM arg)
{
/**************************************
 *
 *      p r o c e s s _ c o n n e c t i o n _ t h r e a d
 *
 **************************************
 *
 * Functional description
 *
 **************************************/
	ThreadCounter counter;

	service_connection((rem_port*) arg);
	return 0;
}