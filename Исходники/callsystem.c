/*
 int
 callsystem(const char * cmd,
 const char * argv[],
 const char * env[],
 callsystem_fd_t in[2],
 callsystem_fd_t out)[2],
 callsystem_fd_t err[2],
 const char * wd,
 int pri,
 callsystem_pid_t * child)

 parameters:
 cmd          command to execute
 argv         zero terminated array of options(only options,
 without the usual argv[0] == cmd, callsystem handles that internally)
 envp         zero terminated array of environment vars
(*in)[2]     fds to be connected to the childs stdin
(*out)[2]    fds to be connected to the childs stdout
(*err)[2]    fds to be connected to the childs stderr
 wd           working directory for the child process
 pri          priority advise 0=normal, 1=higher, -1=lower
 *child       where to store the childs pid, must be initialized to CALLSYSTEM_ILG_PID

 returns -1 when forking the child failed

 the fd's, argv, env and wd might be NULL
 envp will use defaults if NULL(see callsystem_exportdefaults() below)
 fd's will be bound to the standard streams when NULL
 working dir wont be changed if NULL
 */
int
callsystem(const char * cmd,
			char * argv[],
			char * env[],
			callsystem_fd_t in[2],
			callsystem_fd_t out[2],
			callsystem_fd_t err[2],
			const char * wd,
			const int pri,
			callsystem_pid_t * const child)
{
#ifdef unix
	int ppri = getpriority(PRIO_PROCESS, 0);
	callsystem_pid_t cpid;

	if(*child != CALLSYSTEM_ILG_PID)
	{
		errno = EBUSY;
		return -1;
	}

    /*
    pid_t parentPid = getpid();
    pid_t parentGroup = GetGroup();
    */
    
	cpid = fork();
	if(cpid == -1)
		return -1;
/*
    if (parentPid == getpid())
    {
        SetGroup(cpid, parentGroup);
    }
    else
    {
        printf("in child");
    }
 */
    // ---------------
    
	if(cpid == 0){
        
        
		/* child goes here */
		const char* bin;

		if( setup_fd(in, STDIN_FILENO, 0) == -1)
			CALLSYSTEM_CHILD_ERROR("illegal stdin");

		if( setup_fd(out, STDOUT_FILENO, 1) == -1)
			CALLSYSTEM_CHILD_ERROR("illegal stdout");

		if( setup_fd(err, STDERR_FILENO, 1) == -1)
			CALLSYSTEM_CHILD_ERROR("illegal stderr");

		if(wd && chdir(wd))
			CALLSYSTEM_CHILD_ERROR("illegal working directory");

		if(!env && callsystem_exportdefaults(&env))
			CALLSYSTEM_CHILD_ERROR("callsystem_exportdefaults failed");

		bin = alloc_executable_name(&env, &argv, cmd);

		/* put command name into argv[0]*/
		callsystem_argv_pushfront(&argv, strrchr(cmd, '/')?(strrchr(cmd, '/') + 1):cmd);

		if(pri != 0){
			setpriority(PRIO_PROCESS, 0, ppri +(pri>0?-5:5));
			errno = 0;
		}


		execve(bin,argv,env);
		CALLSYSTEM_CHILD_ERROR("execve failed");
	}
    

	/* parent */
	/* close fd's */
	if(in)
	{
		close(in[0]);
		in[0] = CALLSYSTEM_ILG_FD;
	}
	if(out)
	{
		close(out[1]);
		out[1] = CALLSYSTEM_ILG_FD;
	}
	if(err)
	{
		close(err[1]);
		err[1] = CALLSYSTEM_ILG_FD;
	}

	*child = cpid;

	return 0;
#elif defined(WIN32)

	char * bin;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	LPVOID argvblock;
	LPVOID envblock;

	/* we need to copy argv as we're not going to fork on windows. */
	char **argv_child;

	callsystem_argv_dup(argv, &argv_child);

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	si.dwFlags = STARTF_USESTDHANDLES;

	if(!in)
		si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	else
	{
		si.hStdInput = in[0];
		/* make sure the child process doesn't get the other
		 end of the pipe. */
		SetHandleInformation( in[1], HANDLE_FLAG_INHERIT, 0);
	}

	if(!out)
		si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	else
	{
		si.hStdOutput = out[1];
		SetHandleInformation( out[0], HANDLE_FLAG_INHERIT, 0);
	}

	if(!err)
		si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	else
	{
		si.hStdError = err[1];
		SetHandleInformation( err[0], HANDLE_FLAG_INHERIT, 0);
	}

	/*environment*/
	if(!env && callsystem_exportdefaults(&env))
	{
		CALLSYSTEM_CHILD_ERROR("callsystem_exportdefaults failed");
		return -1;
	}

	bin = alloc_executable_name(&env, &argv_child, cmd);
	if(!bin)
	{
		CALLSYSTEM_CHILD_ERROR("command not found");
		return -1;
	}

	/*appname
	 */
	callsystem_argv_pushfront(&argv_child, cmd);

	/*commandline*/
	argvblock = alloc_commandline(argv_child);

	/* don't need this anymore. */
	callsystem_argv_clear(&argv_child);

	if(!argvblock)
		return -1;

	envblock = alloc_envblock(env);
	if(!envblock)
		return -1;

	/*
	 * You must have "inherit==TRUE" or the stdin/out/err handles
	 * won't be available to the sub-process.
	 */
	if(!CreateProcess(bin, argvblock, NULL, NULL, TRUE, 0, envblock, wd, &si, &pi ))
	{
		free(bin);
		return -1;
	}

	free(bin);

	/*
	 * You must close the "other" end of pipes.
	 * reading will just block if you don't
	 */
	if(out)
	{
		if(!CloseHandle(out[1]))
		{
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			return -1;
		}
		out[1] = CALLSYSTEM_ILG_FD;
	}

	if(err)
	{
		if(!CloseHandle(err[1]))
		{
			CloseHandle(pi.hThread);
			CloseHandle(pi.hProcess);
			return -1;
		}
		err[1] = CALLSYSTEM_ILG_FD;
	}


	(void) SetPriorityClass(pi.hProcess,
							pri<0?IDLE_PRIORITY_CLASS:
							pri>0?HIGH_PRIORITY_CLASS:NORMAL_PRIORITY_CLASS);

	CloseHandle(pi.hThread);
	*child = pi.hProcess;

	return 0;

#endif
}