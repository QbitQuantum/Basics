BOOL CGravador::RodaConsole(DWORD * pdwExitCode, CString strRun)
{
	HANDLE hOutputReadTmp;
	HANDLE hOutputWrite;
	SECURITY_ATTRIBUTES sa;

	strReturn.Empty();

	// Set up the security attributes struct.
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;


	// Create the child output pipe.
	if (!CreatePipe(&hOutputReadTmp, &hOutputWrite, &sa, 0))
		DisplayError(_T("CreatePipe"));


	// Create new output read handle and the input write handles. Set
	// the Properties to FALSE. Otherwise, the child inherits the
	// properties and, as a result, non-closeable handles to the pipes
	// are created.
	if (!DuplicateHandle(	GetCurrentProcess(),
							hOutputReadTmp,
							GetCurrentProcess(),
							&hOutputRead, // Address of new handle.
							0,
							FALSE, // Make it uninheritable.
							DUPLICATE_SAME_ACCESS))
		DisplayError(_T("DuplicateHandle"));


	// Close inheritable copies of the handles you do not want to be
	// inherited.
	if (!CloseHandle(hOutputReadTmp))
		DisplayError(_T("CloseHandle"));

	pWDlg->BeginWaitCursor();

	CHandleThread * pHandleThread;
	pHandleThread = new CHandleThread();
	pHandleThread->IniciaThread((void *) this, ReadAndHandleOutput);

	PrepAndLaunchRedirectedChild(hOutputWrite, NULL, NULL, strRun); // o child neste caso será o osql.exe


	// Close pipe handles (do not continue to modify the parent).
	// You need to make sure that no handles to the write end of the
	// output pipe are maintained in this process or else the pipe will
	// not close when the child process exits and the ReadFile will hang.
	if (!CloseHandle(hOutputWrite))
		DisplayError(_T("CloseHandle"));


	// Read the child's output.
	// ReadAndHandleOutput(hOutputRead);

	// Redirection is complete

	// espera finalização do osql.exe
	DWORD dwRet;
	dwRet = WaitForSingleObject(hChildProcess, INFINITE);

	pHandleThread->FinalizaThread(10000);
	delete pHandleThread;

	if (dwRet == WAIT_FAILED)
		DisplayError(_T("WaitForSingleObject"));

	pWDlg->EndWaitCursor();

	if (!CloseHandle(hOutputRead))
		DisplayError(_T("CloseHandle"));

	BOOL bResult;
	bResult = GetExitCodeProcess(hChildProcess, pdwExitCode);
	if (!CloseHandle(hChildProcess))
		DisplayError(_T("CloseHandle"));

	return bResult;
}