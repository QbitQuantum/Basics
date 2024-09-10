BOOL CPipeServer::OpenOrAttachToProcess(void)
{
	ICLRMetaHost *pMetaHost;
	IEnumUnknown *RuntimeEnum;
	HANDLE ths;
	MODULEENTRY32 m;
	HRESULT r;
	BOOL result=FALSE;
	
	

	CLR_DEBUGGING_VERSION v;
	v.wStructVersion=0;
	v.wMajor=4;
	v.wMinor=0;
	v.wRevision=30319;
	v.wBuild=65535;


	CLRDebugging=NULL;
	CorDebugProcess=NULL;
	CorDebugProcess5=NULL;

	libprovider=NULL;
	datacallback=NULL;



	HMODULE hMscoree = LoadLibraryA("mscoree.dll");
	CLRCreateInstanceFnPtr CLRCreateInstance;

	if (hMscoree==NULL)
		return FALSE;

	CLRCreateInstance=(CLRCreateInstanceFnPtr)GetProcAddress(hMscoree, "CLRCreateInstance");
	if (CLRCreateInstance==NULL)
		return FALSE; //only 4.0 is supported for now

	processhandle=OpenProcess(PROCESS_ALL_ACCESS , FALSE, processid);
	if (processhandle==0)
		return FALSE;
	
	if (CLRCreateInstance(CLSID_CLRMetaHost, IID_ICLRMetaHost, (LPVOID*)&pMetaHost)!=S_OK)
		return FALSE;
		
	
	if (pMetaHost->EnumerateLoadedRuntimes(processhandle, &RuntimeEnum)==S_OK)
	{
		ICLRRuntimeInfo *info;
		ULONG count=0;

		RuntimeEnum->Next(1, (IUnknown **)&info, &count);
		if (count)
		{
			result=TRUE;
			libprovider=new CMyICLRDebuggingLibraryProvider(info);  //todo: scan for 4.0			
		}

		RuntimeEnum->Release();
	}
	pMetaHost->Release();

	if (!result)
		return FALSE; //no runtimes

	
	if (CLRCreateInstance(CLSID_CLRDebugging, IID_ICLRDebugging, (void **)&CLRDebugging)!=S_OK)
		return FALSE;

	

	
	ths=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processid);
	if (ths==INVALID_HANDLE_VALUE)
		return FALSE;

	

	ZeroMemory(&m, sizeof(m));
	m.dwSize=sizeof(m);
	if (Module32First(ths, &m))
	{
		datacallback=new CMyIcorDebugDataTarget(processhandle);

		do
		{
			CLR_DEBUGGING_PROCESS_FLAGS flags;
			r=CLRDebugging->OpenVirtualProcess((ULONG64)m.hModule, datacallback,  libprovider, &v, IID_ICorDebugProcess, (IUnknown **)&CorDebugProcess, &v, &flags);
				
			if (r==S_OK)
			{					
				CorDebugProcess->QueryInterface(IID_ICorDebugProcess5, (void **)&CorDebugProcess5);
				break;
			}
		}
		while (Module32Next(ths, &m));
	}


	CloseHandle(ths);

	if (r!=S_OK)
		return FALSE;

	

	//still here
	return TRUE;
}