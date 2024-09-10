int _tmain(int argc, _TCHAR* argv[])
{
	DWORD dwXmlRpcThreadID;
	PROCESS_INFORMATION pi;
	HANDLE hXMLRpcClientThread;
	bool ThreadCreated=false;

	LogLevel=1;
	Log(1,L"ITEScreenWatch V 0.1");

	MyGetIpAdress();	// read IP into g_pLocalIP

	InitScreenContent();

	CreateProcess(L"\\Program Files\\Intermec\\ITE\\intermte.exe", L"", NULL, NULL, FALSE, 0, NULL, NULL, NULL, &pi); 
	Sleep(10000);
	hWndITEWindow = FindWindow(_T("IntermTE"), _T("ITE"));
	if (hWndITEWindow==NULL)
	{
		Log(1,L"FindWindows ITE failes");
	}
	else
	{
		hXMLRpcClientThread=CreateThread(NULL, 0, XMLRpcClientThread, (VOID *)0, 0,&dwXmlRpcThreadID);
		if (hXMLRpcClientThread == NULL)
		{
			Log(1,L"CreateThread failed");
		}
		else
		{
			Log(1,L"CreateThread OK");
			ThreadCreated=true;
		}
	}
	
	Log(1,L"Waiting for TE exit");
	do{
		WaitForSingleObject(pi.hProcess,INFINITE);
	}while((FindWindow(_T("IntermTE"), _T("ITE")))!=NULL);

	Log(1,L"ITE Exit");

	if (ThreadCreated)
	{
		s.exit();
		s.shutdown();
	}
	//Sleep(2000);
	TerminateThread(hXMLRpcClientThread,1);
	//Log(L"Wait Thread end");
	//WaitForSingleObject(hXMLRpcClientThread,INFINITE);
	Sleep(1000);
	
	closeMsgQueue(g_hMsgQueue);

	Log(1,L"Program Exit");
	return 0;
}