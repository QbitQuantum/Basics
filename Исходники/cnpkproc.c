int cnprocCreateProcess( int *pPId, CnpkPipeFds *pFds, int format, int fdOut )
{


	int command_pipe[2];
	int response_pipe[2];
	int data_pipe[2];
	int pid;


	if( pipe(command_pipe) == -1 ){
		DebugPrint( "Pipe Create Error1 \n");
		goto pipe_error;
	}
	if( pipe(response_pipe) == -1 ){
		DebugPrint( "Pipe Create Error2 \n");
		goto pipe_error;
	}
	if( pipe(data_pipe) == -1 ){
		DebugPrint( "Pipe Create Error3 \n");
		goto pipe_error;
	}

	if( (pid=fork()) == -1 ){
		DebugPrint( "Fork Error: \n");
		goto fork_error;
	}
	else if( pid == 0 ){
		char cmdpipe_opt[32];
		char respipe_opt[32];
		char datpipe_opt[32];
		char format_opt[32];
		char output_opt[32];
		char *module_arg[7];
		char *module_buf = NULL;
		int ret;

		close( command_pipe[1] );
		close( response_pipe[0] );
		close( data_pipe[1] );

		snprintf( format_opt, 31, FORMAT_STR, format );
		snprintf( output_opt, 31, OUTPUT_STR, fdOut );
		snprintf( cmdpipe_opt,31, CMD_PIPE_STR, command_pipe[0] );
		snprintf( respipe_opt,31, RES_PIPE_STR, response_pipe[1] );
		snprintf( datpipe_opt,31, DAT_PIPE_STR, data_pipe[0] );

		module_buf = malloc(strlen(MODULE_PATH)+strlen(MODULE_NAME)+2);
		if( module_buf == NULL ){
			goto malloc_error;
		}

		memset(module_buf, 0, sizeof(module_buf));
		strncpy(module_buf, MODULE_PATH, strlen(MODULE_PATH)+1);
		strcat(module_buf, "/");
		strncat(module_buf, MODULE_NAME, strlen(MODULE_NAME)+1);

		module_arg[0] = module_buf;
		module_arg[1] = format_opt;
		module_arg[2] = output_opt;
		module_arg[3] = cmdpipe_opt;
		module_arg[4] = respipe_opt;
		module_arg[5] = datpipe_opt;
		module_arg[6] = NULL;

		ret = execv(module_buf, module_arg);
		if( ret == -1 ){
			DebugPrint( "exec Error \n");
			exit(-1);

		}
	}
	else{
		close( command_pipe[0] );
		close( response_pipe[1] );
		close( data_pipe[0] );
	}

	*pPId = pid;
	pFds->cmd_fd = command_pipe[1];
	pFds->res_fd = response_pipe[0];
	pFds->dat_fd = data_pipe[1];

	return 0;

 malloc_error:
 fork_error:
 pipe_error:
	return -1;

}