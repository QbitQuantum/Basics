/**
 * @brief
 *	Handles multiple incoming requests from mom_open_demux client processes, handles the
 *      output.
 *
 * @param[in]  pipename - pipe name for mom_open_demux clients to connect
 * @param[in]  jobid - job id for which demux is needed
 * @param[in]  num_nodes - job's number of nodes
 *
 * @return  int
 * @retval  0 - success
 * @retval  !0 - error
 *
 */
int
handle_np_conn(char *pipename, char *jobid, int num_nodes)
{
	HANDLE                  hPipe = NULL;
	DWORD                   dwRead=0;
	SECURITY_ATTRIBUTES     SecAttrib = {0};
	SECURITY_DESCRIPTOR     SecDesc;
	int                     i = 0;
	rshell_cmd              rs_cmd;
	HANDLE                  *pdemux_thread_handles = NULL;
	char                    hostname[PBS_MAXHOSTNAME + 1] = {'\0'};

	(void)memset(rs_cmd.hostname, '\0', sizeof(rs_cmd.hostname));
	(void)memset(rs_cmd.pipename_append, '\0', sizeof(rs_cmd.pipename_append));

	hPipe = CreateNamedPipe(
		pipename,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		0,
		0,
		(DWORD)-1,
		&SecAttrib);
	if (hPipe == INVALID_HANDLE_VALUE || hPipe == NULL) {
		fprintf(stderr, "pipe creation failed!\n");
		return (-1);
	}

	pdemux_thread_handles = (HANDLE *)malloc(num_nodes * sizeof(HANDLE));
	if (pdemux_thread_handles == NULL) {
		fprintf(stderr, "malloc failed!\n");
		close_valid_handle(&(hPipe));
		return (-1);
	}

	for (i = 0; i < num_nodes && hPipe != NULL; i++) {
		(void)InitializeSecurityDescriptor(&SecDesc, SECURITY_DESCRIPTOR_REVISION);
		(void)SetSecurityDescriptorDacl(&SecDesc, TRUE, NULL, TRUE);
		SecAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
		SecAttrib.lpSecurityDescriptor = &SecDesc;;
		SecAttrib.bInheritHandle = TRUE;

		(void)do_ConnectNamedPipe(hPipe, NULL);
		if (!ReadFile(hPipe, hostname, PBS_MAXHOSTNAME, &dwRead, NULL) ||
			dwRead == 0) {
			DWORD dwErr = GetLastError();
			/* break when client closes the pipe */
			if (dwErr == ERROR_NO_DATA) {
				(void)DisconnectNamedPipe(hPipe);
				pdemux_thread_handles[i] = INVALID_HANDLE_VALUE;
				continue;
			}
		}
		if (dwRead) {
			char pipename_append[PIPENAME_MAX_LENGTH] = {'\0'};
			hostname[ dwRead / sizeof(char) ] = '\0';
			(void)strncpy_s(pipename_append, _countof(pipename_append), jobid, _TRUNCATE);
			(void)strncat_s(pipename_append, _countof(pipename_append), "mom_demux", _TRUNCATE);
			(void)strncat_s(pipename_append, _countof(pipename_append), hostname, _TRUNCATE);
			/*
			 * run remote command
			 * do not redirect stdin
			 */
			(void)strncpy_s(rs_cmd.hostname, _countof(rs_cmd.hostname), hostname, _TRUNCATE);
			(void)strncpy_s(rs_cmd.pipename_append, _countof(rs_cmd.pipename_append), pipename_append, _TRUNCATE);
			rs_cmd.connect_stdin = 0;
			pdemux_thread_handles[i] = (HANDLE)_beginthread(remote_shell_command_thread, 0, &rs_cmd);
		}
		else {
			pdemux_thread_handles[i] = INVALID_HANDLE_VALUE;
		}
		(void)DisconnectNamedPipe(hPipe);
	}
	/* wait forever for demux threads to exit */
	(void)WaitForMultipleObjects(num_nodes, pdemux_thread_handles, TRUE, INFINITE);
	for (i = 0; i < num_nodes; i++)
		close_valid_handle(&(pdemux_thread_handles[i]));
	free(pdemux_thread_handles);
	close_valid_handle(&(hPipe));
	return 0;
}