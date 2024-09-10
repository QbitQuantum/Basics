bool CODebugger::ReadTEB(HANDLE th) 
{	
	bool	rv = false;
	DWORD	dwLength = 0;

	DEBUGGER_THREAD* pDebuggerThread = NULL;
	pDebuggerThread = m_debuggerThread.Search(th);
	if(pDebuggerThread != NULL)
	{
		rv = ReadProcessMemory(
			m_hProcess,
			pDebuggerThread->m_tbiBasics.TebBaseAddress,
			&pDebuggerThread->m_ThreadEnvironmentBlock,
			sizeof(TEB),
			&dwLength);
	}

	return rv;
}