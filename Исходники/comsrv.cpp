void CExeModule::MonitorShutdown() {
	WaitForSingleObject(hEventShutdown, INFINITE);
	#ifdef _ATL_FREE_THREADED
	CoSuspendClassObjects();
	#endif
	CloseHandle(hEventShutdown);
	CloseHandle(hMonitorThread);
	#ifdef _DEBUG
	PlaySound(_T("chimes.wav"),NULL,SND_FILENAME|SND_ASYNC);
	#endif
	PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
}