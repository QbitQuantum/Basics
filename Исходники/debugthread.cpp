	bool debugthread::stopdebug()
	{
	DebugActiveProcessStop(pars.pi.dwProcessId);
	return true;
	}