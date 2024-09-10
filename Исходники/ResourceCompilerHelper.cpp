bool CResourceCompilerHelper::InvokeResourceCompiler( const char *szSrcFile, const bool bWindow ) const
{
	bool bRet = true;

	// make command for execution

	wchar_t wMasterCDDir[512];
	GetCurrentDirectoryW(512,wMasterCDDir);

	SettingsManagerHelpers::CFixedString<wchar_t, 512> wRemoteCmdLine;
	SettingsManagerHelpers::CFixedString<wchar_t, 512> wDir;

	wRemoteCmdLine.appendAscii("Bin32/rc/");
	wRemoteCmdLine.appendAscii(RC_EXECUTABLE);
	wRemoteCmdLine.appendAscii(" \"");
	wRemoteCmdLine.append(wMasterCDDir);
	wRemoteCmdLine.appendAscii("\\");
	wRemoteCmdLine.appendAscii(szSrcFile);
	wRemoteCmdLine.appendAscii("\" /userdialog=0");

	wDir.append(wMasterCDDir);
	wDir.appendAscii("\\Bin32\\rc");

	STARTUPINFOW si;
	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	si.dwX = 100;
	si.dwY = 100;
	si.dwFlags = STARTF_USEPOSITION;

	PROCESS_INFORMATION pi;
	ZeroMemory( &pi, sizeof(pi) );

	if (!CreateProcessW( 
		NULL,     // No module name (use command line). 
		const_cast<wchar_t*>(wRemoteCmdLine.c_str()), // Command line. 
		NULL,     // Process handle not inheritable. 
		NULL,     // Thread handle not inheritable. 
		FALSE,    // Set handle inheritance to FALSE. 
		bWindow?0:CREATE_NO_WINDOW,	// creation flags. 
		NULL,     // Use parent's environment block. 
		wDir.c_str(),  // Set starting directory. 
		&si,      // Pointer to STARTUPINFO structure.
		&pi))     // Pointer to PROCESS_INFORMATION structure.
	{
		bRet = false;
	}

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );

	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return bRet;
}