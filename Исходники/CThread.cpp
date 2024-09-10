	void ExitThread(unsigned long dwExitCode)
	{
#ifndef _WIN32
		pthread_exit(&dwExitCode);
#else
		_endthreadex(dwExitCode);
#endif
	}