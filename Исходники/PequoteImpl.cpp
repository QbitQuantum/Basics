DWORD CPequote::Start()
{	
	//CEgRegKey key;
	CModuleVersion ver;
	TCHAR pModName [1024] = { 0 };
	TCHAR pVer[100] = { 0 };
    
    //detecting the module version
	::GetModuleFileName( NULL, pModName, sizeof(pModName)/sizeof(TCHAR));
	ver.GetModuleVersionInfo(pModName);		
	ver.GetValue(_T("ProductVersion"), pVer);

	DWORD dwFlags;
	if(GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwFlags))
	{
		dwFlags &= ~(ENABLE_QUICK_EDIT | ENABLE_INSERT_MODE);
		SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), dwFlags);
	}

	m_hStopApplication = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!m_hStopApplication)
	{
		return TraceError();
	}
	
	if (!::SetConsoleCtrlHandler(HandlerRoutine, TRUE))
		return TraceError();

	CTracer::TraceMessage(CTracer::enMtInformation, NULL, _T("Starting Pequote connector..."));

	DWORD dwRes = m_PequoteConnector.Start(NULL);	
	if (dwRes)
	{
		CTracer::TraceMessage(CTracer::enMtError, NULL, _T("Failed to start Pequote connector."));
		return dwRes;
	}

	CTracer::TraceMessage(CTracer::enMtInformation, NULL, _T("Pequote connector started."));
	CTracer::TraceMessage(CTracer::enMtInformation, NULL, _T("Server started."));
    
	return 0;
}