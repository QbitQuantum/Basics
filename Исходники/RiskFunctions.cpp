bool CloseNTApplication( TCHAR* strApplName, bool bForce /* = false */ )
{
	USES_CONVERSION;

	// Check if application is running
	if (!NTApplicationRunning(strApplName))
		return true;

	// Application is closed
	CInternalData::Instance()->SetApplicationClosed(true);

	// Get the list of process identifiers.
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;
	std::string strAppName = _strlwr(W2A(strApplName));
	if ( !lpEnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
		return false;

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.
	for ( i = 0; i < cProcesses; i++ )
	{
		std::string strProcess = GetProcessNameAndID( aProcesses[i] );

		if( strstr( strProcess.c_str(), strAppName.c_str() ) != NULL )
		{
			// Should we force the application to close?
			if (bForce)
			{
				// Get handle to process
				HANDLE hProcess = OpenProcess
					(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);

				// Terminate process
				DWORD exCode;
				GetExitCodeProcess(hProcess, &exCode);
				TerminateProcess(hProcess, exCode);
			}
			else
			{
				// Send message to the right window
				EnumWindows(EnumWinHandle, aProcesses[i]);
			}
		}
	}
	return true;
}