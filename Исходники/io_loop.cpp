int
stdin_pipe_handler(Service*, int) {

	std::string* line;
	while ((line = stdin_buffer.GetNextLine()) != NULL) {

		const char * command = line->c_str();

		// CREATE_CONDOR_SECURITY_SESSION contains sensitive data that
		// normally shouldn't be written to a publically-readable log.
		// We should conceal it unless GAHP_DEBUG_HIDE_SENSITIVE_DATA
		// says not to.
		if ( param_boolean( "GAHP_DEBUG_HIDE_SENSITIVE_DATA", true ) &&
			 strncmp( command, GAHP_COMMAND_CREATE_CONDOR_SECURITY_SESSION,
					  strlen( GAHP_COMMAND_CREATE_CONDOR_SECURITY_SESSION ) ) == 0 ) {
			dprintf( D_ALWAYS, "got stdin: %s XXXXXXXX\n",
					 GAHP_COMMAND_CREATE_CONDOR_SECURITY_SESSION );
		} else {
			dprintf (D_ALWAYS, "got stdin: %s\n", command);
		}

		Gahp_Args args;

		if (parse_gahp_command (command, &args) &&
			verify_gahp_command (args.argv, args.argc)) {

				// Catch "special commands first
			if (strcasecmp (args.argv[0], GAHP_COMMAND_RESULTS) == 0) {
					// Print number of results
				std::string rn_buff;
				formatstr( rn_buff, "%d", result_list.number() );
				const char * commands [] = {
					GAHP_RESULT_SUCCESS,
					rn_buff.c_str() };
				gahp_output_return (commands, 2);

					// Print each result line
				char * next;
				result_list.rewind();
				while ((next = result_list.next()) != NULL) {
					printf ("%s\n", next);
					fflush(stdout);
					dprintf(D_FULLDEBUG,"put stdout: %s\n",next);
					result_list.deleteCurrent();
				}

				new_results_signaled = FALSE;
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_VERSION) == 0) {
				printf ("S %s\n", version);
				fflush (stdout);
				dprintf(D_FULLDEBUG,"put stdout: S %s\n",version);
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_QUIT) == 0) {
				gahp_output_return_success();
				DC_Exit(0);
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_ASYNC_MODE_ON) == 0) {
				async_mode = TRUE;
				new_results_signaled = FALSE;
				gahp_output_return_success();
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_ASYNC_MODE_OFF) == 0) {
				async_mode = FALSE;
				gahp_output_return_success();
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_QUIT) == 0) {
				gahp_output_return_success();
				return 0; // exit
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_COMMANDS) == 0) {
				const char * commands [] = {
					GAHP_RESULT_SUCCESS,
					GAHP_COMMAND_DOWNLOAD_SANDBOX,
					GAHP_COMMAND_UPLOAD_SANDBOX,
					GAHP_COMMAND_DESTROY_SANDBOX,
					GAHP_COMMAND_CREATE_CONDOR_SECURITY_SESSION,
					GAHP_COMMAND_CONDOR_VERSION,
					GAHP_COMMAND_ASYNC_MODE_ON,
					GAHP_COMMAND_ASYNC_MODE_OFF,
					GAHP_COMMAND_RESULTS,
					GAHP_COMMAND_QUIT,
					GAHP_COMMAND_VERSION,
					GAHP_COMMAND_COMMANDS};
				gahp_output_return (commands, 12);
			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_CREATE_CONDOR_SECURITY_SESSION) == 0) {
				ClaimIdParser claimid( args.argv[1] );
				if ( !daemonCore->getSecMan()->CreateNonNegotiatedSecuritySession(
										DAEMON,
										claimid.secSessionId(),
										claimid.secSessionKey(),
										claimid.secSessionInfo(),
										CONDOR_PARENT_FQU,
										NULL,
										0 ) ) {
					gahp_output_return_error();
				} else {
					sec_session_id = claimid.secSessionId();
					gahp_output_return_success();
				}

			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_CONDOR_VERSION) == 0) {
				peer_condor_version = args.argv[1];

				const char *reply [] = { GAHP_RESULT_SUCCESS,
										 escapeGahpString( CondorVersion() ) };
				gahp_output_return( reply, 2 );

			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_DOWNLOAD_SANDBOX) == 0) {

				int fds[2];
				if ( pipe( fds ) < 0 ) {
					EXCEPT( "Failed to create pipe!" );
				}
				ChildErrorPipe = fds[1];
				int tid = daemonCore->Create_Thread(do_command_download_sandbox, (void*)strdup(command), NULL, download_sandbox_reaper_id);

				close( fds[1] );
				if( tid ) {
					dprintf (D_ALWAYS, "BOSCO: created download_sandbox thread, id: %i\n", tid);

					// this is a "success" in the sense that the gahp command was
					// well-formatted.  whether or not the file transfer works or
					// not is not what we are reporting here.
					gahp_output_return_success();

					SandboxEnt e;
					e.pid = tid;
					e.request_id = args.argv[1];
					e.sandbox_id = args.argv[2];
					e.error_pipe = fds[0];
					// transfer started, record the entry in the map
					std::pair<int, struct SandboxEnt> p(tid, e);
					sandbox_map.insert(p);
				} else {
					dprintf (D_ALWAYS, "BOSCO: Create_Thread FAILED!\n");
					gahp_output_return_success();
					const char * res[2] = {
						"Worker thread failed",
						"NULL"
					};
					enqueue_result(args.argv[1], res, 2);
					close( fds[0] );
				}

			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_UPLOAD_SANDBOX) == 0) {

				int fds[2];
				if ( pipe( fds ) < 0 ) {
					EXCEPT( "Failed to create pipe!" );
				}
				ChildErrorPipe = fds[1];
				int tid = daemonCore->Create_Thread(do_command_upload_sandbox, (void*)strdup(command), NULL, upload_sandbox_reaper_id);

				close( fds[1] );
				if( tid ) {
					dprintf (D_ALWAYS, "BOSCO: created upload_sandbox thread, id: %i\n", tid);

					// this is a "success" in the sense that the gahp command was
					// well-formatted.  whether or not the file transfer works or
					// not is not what we are reporting here.
					gahp_output_return_success();

					SandboxEnt e;
					e.pid = tid;
					e.request_id = args.argv[1];
					e.sandbox_id = args.argv[2];
					e.error_pipe = fds[0];
					// transfer started, record the entry in the map
					std::pair<int, struct SandboxEnt> p(tid, e);
					sandbox_map.insert(p);
				} else {
					dprintf (D_ALWAYS, "BOSCO: Create_Thread FAILED!\n");
					gahp_output_return_success();
					const char * res[1] = {
						"Worker thread failed"
					};
					enqueue_result(args.argv[1], res, 1);
					close( fds[0] );
				}

			} else if (strcasecmp (args.argv[0], GAHP_COMMAND_DESTROY_SANDBOX) == 0) {

				int fds[2];
				if ( pipe( fds ) < 0 ) {
					EXCEPT( "Failed to create pipe!" );
				}
				ChildErrorPipe = fds[1];
				int tid = daemonCore->Create_Thread(do_command_destroy_sandbox, (void*)strdup(command), NULL, destroy_sandbox_reaper_id);

				close( fds[1] );
				if( tid ) {
					dprintf (D_ALWAYS, "BOSCO: created destroy_sandbox thread, id: %i\n", tid);

					// this is a "success" in the sense that the gahp command was
					// well-formatted.  whether or not the file transfer works or
					// not is not what we are reporting here.
					gahp_output_return_success();

					SandboxEnt e;
					e.pid = tid;
					e.request_id = args.argv[1];
					e.sandbox_id = args.argv[2];
					e.error_pipe = fds[0];
					// transfer started, record the entry in the map
					std::pair<int, struct SandboxEnt> p(tid, e);
					sandbox_map.insert(p);
				} else {
					dprintf (D_ALWAYS, "BOSCO: Create_Thread FAILED!\n");
					gahp_output_return_success();
					const char * res[1] = {
						"Worker thread failed"
					};
					enqueue_result(args.argv[1], res, 1);
					close( fds[0] );
				}

			} else {
				// should never get here if verify does its job
				dprintf(D_ALWAYS, "FTGAHP: got bad command: %s\n", args.argv[0]);
				gahp_output_return_error();
			}
			
		} else {
			gahp_output_return_error();
		}

		delete line;
	}

	// check if GetNextLine() returned NULL because of an error or EOF
	if (stdin_buffer.IsError() || stdin_buffer.IsEOF()) {
		dprintf (D_ALWAYS, "stdin buffer closed, exiting\n");
		DC_Exit (1);
	}

	return TRUE;
}