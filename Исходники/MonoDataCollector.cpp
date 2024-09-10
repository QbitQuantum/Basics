DWORD WINAPI DataCollectorEntry(LPVOID lpThreadParameter)
{
	CPipeServer *pw;

#ifdef NDEBUG
	ZWSETINFORMATIONTHREAD ZwSetInformationThread=(ZWSETINFORMATIONTHREAD)GetProcAddress(GetModuleHandleA("ntdll.dll"), "ZwSetInformationThread");
	if (ZwSetInformationThread)
	{
		int r=ZwSetInformationThread(GetCurrentThread(), ThreadHideFromDebugger, NULL, 0);
		if (r!=0)
		{
			OutputDebugStringA("No debug safety");
		}
	}
#endif


	pw=new CPipeServer();
	pw->Start();

	DataCollectorThread=0;
	delete pw;	

	if (SuicideThread)
		TerminateThread(SuicideThread, 0);
	
	Sleep(1000);

	FreeLibraryAndExitThread(g_hInstance, 0);
	return 0;
}