static int doldd(const char* filename)
{
	STARTUPINFO		si;
	HANDLE			ph; 
	DEBUG_EVENT		event;
	struct spawndata	sdata;
	char*			av[2];
	pid_t			pid;
	int			status;
	int			r = 0;
	char			dllname[PATH_MAX+1];
	char			dllpath[PATH_MAX+1];

	memset(&sdata, 0, sizeof(sdata));
	memset(&si, 0, sizeof(si));
	sdata.start = &si;
	sdata.flags = DEBUG_PROCESS;
	si.cb		= sizeof(si);
	si.dwFlags	= STARTF_FORCEONFEEDBACK|STARTF_USESHOWWINDOW;
	si.wShowWindow	= SW_SHOWNORMAL;
	av[0] = (char*)filename;
	av[1] = 0;
	if ((pid = uwin_spawn(filename, av, NULL, &sdata)) < 0)
	{
		error(ERROR_system(0), "%s cannot create process", filename);
		return -1;
	}
	ph = sdata.handle;
	for (;;)
	{
		if (!WaitForDebugEvent(&event, 1500))
			break;
		if (event.dwProcessId != uwin_ntpid(pid))
			continue;
		switch(event.dwDebugEventCode)
		{
		case EXIT_PROCESS_DEBUG_EVENT:
			CloseHandle(ph);
			ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE);
			wait(&status);
			return 0;
		case LOAD_DLL_DEBUG_EVENT:
			if (event.u.LoadDll.hFile)
			{
				if (modulenamepath(ph, &event.u.LoadDll, dllname, sizeof(dllname), dllpath, sizeof(dllpath)) < 0)
					r = -1;
				else
					sfprintf(sfstdout, "\t%s => %s\n", dllname, dllpath);
			}
			ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE);
			break;
		case CREATE_PROCESS_DEBUG_EVENT:
			ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE);
			break;
		case CREATE_THREAD_DEBUG_EVENT:
		case EXCEPTION_DEBUG_EVENT:
			kill(pid, SIGTERM);
			ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_TERMINATE_PROCESS);
			break;
		default:
			ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE);
			break;
		}
	}
	return 0;
}