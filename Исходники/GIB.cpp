//
// Invoke()
//
// invoke the GIB program and return the recommended play
//
int CGIB::Invoke(CPlayer* pPlayer, CHandHoldings* pHand, CHandHoldings* pDummyHand, CPlayerStatusDialog* pStatusDlg)
{
	SECURITY_ATTRIBUTES saAttr; 
	
	//
	// create the GIB monitor dialog
	//
	CGIBDialog	gibDialog(pMAINFRAME);
	int nProcessingTime = theApp.GetValue(tnGIBAnalysisTime);
	gibDialog.m_nProcessTime = nProcessingTime;
//	gibDialog.m_hEventCancel = m_hEventCancel;

	
	// Set the bInheritHandle flag so pipe handles are inherited. 
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 
	
	//
	// create input and output pipes for the child process
	//

	// Create a pipe for the child process's STDOUT. 
	if (!CreatePipe(&m_hChildStdoutRd,	// returns the pipe's input handle
				    &m_hChildStdoutWr, 	// returns the pipe's output handle
					&saAttr, 
					0)) 
	{
		CString strError = "Stdout pipe creation failed\n"; 
		TRACE(strError); 
		pMAINFRAME->SetGIBMonitorText(strError);
		return ExitGracefully(-5);
	}
	// then create a pipe for the child process's STDIN. 
	if (!CreatePipe(&m_hChildStdinRd, 
					&m_hChildStdinWr, 
					&saAttr, 
					0)) 
	{
		CString strError = "Stdin pipe creation failed\n"; 
		TRACE(strError); 
		pMAINFRAME->SetGIBMonitorText(strError);
		return ExitGracefully(-5);
	}

	//
	// Now create the child process (GIB)
	//
	PROCESS_INFORMATION piProcInfo; 
	if (!LaunchProgram(piProcInfo)) 
	{
		TRACE("Create process failed"); 
		return ExitGracefully(-1);
	}
	HANDLE hGIBProcess = piProcInfo.hProcess;
	DWORD nGIBProcessID = piProcInfo.dwProcessId;

	// now close the readable handle to the child's stdin
	SafeCloseHandle(m_hChildStdinRd);
	// and the writable handle to the child's stdout
	SafeCloseHandle(m_hChildStdoutWr);

	//
	//------------------------------------------------------------------
	//
	// create the GIB input file
	//
	CFile file;
	CFileException fileException;
	CString strTempFile, strTempPath;
	GetTempPath(1024, strTempPath.GetBuffer(1024));
	strTempPath.ReleaseBuffer();
	GetTempFileName(strTempPath, "ezb", 0, strTempFile.GetBuffer(2048));
	strTempFile.ReleaseBuffer();
//	strTempFile.Format("%s\\%s", theApp.GetValueString(tszProgramDirectory), tszGIBTempFilename);
/*
	LPTSTR szBuffer = strTempFile.GetBuffer(MAX_PATH);
	GetTempFileName(theApp.GetValueString(tszProgramDirectory), "ezb", 0, szBuffer);
	strTempFile.ReleaseBuffer();
*/
//	CString strInput;
//	strInput.Format("-T %d %s\n",theApp.GetValue(tnGIBAnalysisTime),strTempFile);
	int nCode = file.Open(strTempFile, 
			  			  CFile::modeWrite | CFile::modeCreate | CFile::shareDenyWrite, 
						  &fileException);
	if (nCode == 0) 
	{
		CString strError = "Error opening temporary input file for GIB"; 
		TRACE(strError); 
		pMAINFRAME->SetGIBMonitorText(strError);
		return ExitGracefully(-2);
	}
	//
	CString strFileContents;
	CreateGIBInputFile(file, pPlayer, pHand, pDummyHand, strFileContents);
	file.Close();

	// then send the parameters line
	CString strParameters, strShortParameters;
	strParameters.Format("-T %d %s\n",nProcessingTime,strTempFile);
	strShortParameters.Format("-T %d",nProcessingTime);
	DWORD dwWritten;
	int nErrCode;
	if (!WriteFile(m_hChildStdinWr, (LPCTSTR)strParameters, strParameters.GetLength(), &dwWritten, NULL)) 
	{
		CString strError = "Error providing parameters to GIB"; 
		TRACE(strError); 
		pMAINFRAME->SetGIBMonitorText(strError);
		nErrCode = GetLastError();
		return ExitGracefully(-3);
	}

	//
	// update the GIB monitor window
	//
	CString strGIBText = "========================================\n";
	strGIBText += FormString("Launching %s %s\n",
							 theApp.GetValueString(tszGIBPath),
							 strShortParameters);
//	strGIBText += FormString("Input file contents:\n%s", strFileContents);
	strGIBText += "Awaiting Responses...\n";
	strGIBText += "----------------------------------------\n";
//	pMAINFRAME->SetGIBMonitorText(strGIBText);
	pMAINFRAME->AppendGIBMonitorText(strGIBText);
	

	//
	//------------------------------------------------------------
	//
	// now set up the wait loop and the cancel dialog,
	// then sit and wait for the process to run or for a cancel message
	//

/*
	//
	// create the "Cancel GIB" dialog thread
	// (this is a user interface thread)
	//
	CGIBMonitorThread* pMonitorThread = new CGIBMonitorThread(m_hEventFinished, m_hEventCancel, nProcessingTime);
	pMonitorThread->CreateThread(CREATE_SUSPENDED);
	pMonitorThread->SetThreadPriority(THREAD_PRIORITY_ABOVE_NORMAL);
	pMonitorThread->ResumeThread();

	// wait for the monitor thread to initialize
	DWORD nCode0 = WaitForSingleObject(m_hEventFinished,
									   INFINITE);		
*/

	//
	// create the wait thread
	// (this is a worker thread)
	//
	GIBStruct gibData;
	gibData.hReadHandle = m_hChildStdoutRd;
	gibData.pGIBDialog = &gibDialog;
	CWinThread* pWaitThread = AfxBeginThread(CGIB::ReadGIBOutput, &gibData, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);

	// copy its handle se that we can check its exit code later
  	HANDLE hWaitThread;
	BOOL bCode = ::DuplicateHandle(GetCurrentProcess(), pWaitThread->m_hThread, 
								   GetCurrentProcess(), &hWaitThread, 
								   0, FALSE, DUPLICATE_SAME_ACCESS);
	// and launch the threads
//	MonitorThread->ResumeThread();
	pWaitThread->ResumeThread();


	//
	// Show the Wait/Cancel dialog
	//
	m_bGIBPending = TRUE;		// mark dialog as active
	bCode = gibDialog.DoModal();

	// see if the user cancelled
	if (!bCode) 
	{
/*
		// lock out the wait thread and cancel operations
		if (ClearGIBPending())
		{
*/
		//
		pMAINFRAME->SetStatusText("GIB cancelled.");
		//
		TerminateProcess(hGIBProcess, 0);
		TerminateThread(hWaitThread, 0);
		// wait for the read thread to end
		WaitForSingleObject(hWaitThread, INFINITE);
		// close the wait thread handle
		CloseHandle(hWaitThread);
		CloseHandle(hGIBProcess);
		// and delete the thread object
		delete pWaitThread;
		// close pipe handles 
		SafeCloseHandle(m_hChildStdinWr);
		SafeCloseHandle(m_hChildStdoutRd);
		// and throw an exception
		throw CGIBException();
//		}
	}

/*
	// set up events
	HANDLE eventArray[2];
	eventArray[0] = m_hEventCancel;
	eventArray[1] = pWaitThread->m_hThread;

	//
	// then sit back and wait for the thread(s)
	//
	for(;;)
	{
		// wait for the cancelled or finished messages
		DWORD nCode = WaitForMultipleObjects(2,				// 2 events to wait for
											 eventArray,	// events array
											 FALSE,			// not all at once
											 INFINITE);		// wait 4-ever
		//
		if (nCode == WAIT_FAILED)
		{
			ASSERT(FALSE);
			break;
		}
		else if (nCode == WAIT_OBJECT_0) 
		{
			// got the cancel message, so kill GIB & the wait thread
			// the following is very dangersous --
			// so kids, don't try this at home
			TerminateThread(pWaitThread, 0);
			TerminateProcess(hGIBProcess, 0);
			return GIB_CANCEL;
		}
		else if (nCode == WAIT_OBJECT_0 + 1)
		{
			// GIB finished message
			// signal the GIB monitor that GIB has finished
			SetEvent(m_hEventFinished);
			break;
		}
	}

*/

	//
	//------------------------------------------------------------
	//
	// presumably, GIB has finished running
	//

	// wait for the GIB thread to exit, then get the card code
	DWORD nCardPlayed, nErrorCode;
	bCode = WaitForSingleObject(hWaitThread, INFINITE);
	bCode = GetExitCodeThread(hWaitThread, &nCardPlayed);
	if (!bCode)
		nErrorCode = GetLastError();

	// close the wait thread handle
	CloseHandle(hWaitThread);

	// delete the temporary file
	DeleteFile(strTempFile);
 
	// and kill the child process
	// first send a Ctrl-C to the app 
	// (this doesn't seem to do anything)
	CString strInput = "\03";	// Ctrl-C
	if (!WriteFile(m_hChildStdinWr, (LPCTSTR)strInput, strInput.GetLength(), &dwWritten, NULL)) 
	{
		CString strError = "Error stopping GIB"; 
		TRACE(strError); 
		pMAINFRAME->SetGIBMonitorText(strError);
		nErrCode = GetLastError();
		return ExitGracefully(-4);
	}

	// close the writable handle to the child's stdin
	SafeCloseHandle(m_hChildStdinWr);

	// then call terminateProcess
	TerminateProcess(hGIBProcess, 0);
	CloseHandle(hGIBProcess);

	// then close the readable handle to the child's stdout
	SafeCloseHandle(m_hChildStdoutRd);

	//
	// done
	//
	return nCardPlayed; 
} 