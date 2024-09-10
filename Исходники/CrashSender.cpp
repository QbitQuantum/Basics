int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int /*nCmdShow*/ = SW_SHOWDEFAULT)
{ 
  LPCWSTR szCommandLine = GetCommandLineW();
  
  int argc = 0;
  LPWSTR* argv = CommandLineToArgvW(szCommandLine, &argc);
 
  // Read the crash info passed by CrashRpt.dll to CrashSender.exe 
  if(argc!=2)
    return 1; // No arguments passed

  // Read crash info
  CString sFileName = CString(argv[1]);
  int nInit = g_CrashInfo.Init(sFileName);
  if(nInit!=0)
  {
    MessageBox(NULL, _T("Couldn't initialize!"), _T("CrashSender.exe"), MB_ICONERROR);
    return 1;
  }
  
  if(!g_CrashInfo.m_bSendRecentReports)
  {
    // Do the crash info collection work assynchronously
    g_ErrorReportSender.DoWork(COLLECT_CRASH_INFO);
  }
  
  // Check window mirroring settings 
  CString sRTL = Utility::GetINIString(g_CrashInfo.m_sLangFileName, _T("Settings"), _T("RTLReading"));
  if(sRTL.CompareNoCase(_T("1"))==0)
  {
  	SetProcessDefaultLayout(LAYOUT_RTL);  
  }  

  CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);
    
  if(!g_CrashInfo.m_bSendRecentReports)
  {
    if(dlgErrorReport.Create(NULL) == NULL)
	  {
		  ATLTRACE(_T("Main dialog creation failed!\n"));
		  return 0;
	  }
  }
  else
  {
    // check if another instance of CrashSender.exe is running
	  ::CreateMutex( NULL, FALSE,_T("Local\\43773530-129a-4298-88f2-20eea3e4a59b"));
    if (::GetLastError() == ERROR_ALREADY_EXISTS)
	  {		
      // Another CrashSender.exe already tries to resend recent reports; exit.
		  return 0;
	  }

    if(g_CrashInfo.GetReportCount()==0)
      return 0; // There are no reports for us to send

    // Check if it is ok to remind user now
    if(!g_CrashInfo.IsRemindNowOK())
      return 0;

    if(dlgResend.Create(NULL) == NULL)
	  {
		  ATLTRACE(_T("Resend dialog creation failed!\n"));
		  return 0;
	  }
  }
  
	int nRet = theLoop.Run();

  // Wait until the worker thread is exited  
  g_ErrorReportSender.WaitForCompletion();
  nRet = g_ErrorReportSender.GetGlobalStatus();

	_Module.RemoveMessageLoop();

	return nRet;
}