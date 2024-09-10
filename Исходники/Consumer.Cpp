BOOL CConsumer::ConsumerProcessTrace(TRACEHANDLE hTrace, DWORD processId, LPWSTR logFilePath)
{


// 	HRESULT hr = ConnectToETWNameSpace(_bstr_t(L"root\\wmi"));
// 	if(FAILED(hr))
// 	{
// 		wprintf(L"ConnectoETWNameSpace failed with 0x%x\r\n", hr);	
// 	}
	m_logFilePath = logFilePath;
	m_processId = processId;

	SymSetOptions(SYMOPT_DEBUG);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE, m_processId);
	if(hProcess == NULL)
	{
		wprintf(L"OpenProcess Failed with %lu\r\n", GetLastError());
	}
	else
	{

		HMODULE hMod[1024];
		DWORD	cbNeeded;
		TCHAR	szModName[MAX_PATH] = {0};
		std::string pdbSerchPath = "\\\\192.168.14.181\\public\\symbols\\";
		std::string finalSearchPath = "d:\\symbolslocal";
		if(EnumProcessModules(hProcess, hMod, sizeof(hMod), &cbNeeded))
		{
			for(int i = 0; i < cbNeeded / sizeof(HMODULE); ++i)
			{
				pdbSerchPath = "\\\\192.168.14.181\\public\\symbols\\";
				ZeroMemory(szModName, sizeof(szModName));
				if(GetModuleFileNameEx(hProcess, hMod[i], szModName, sizeof(szModName)))
				{
					CFileVersion fileVer;
					if(fileVer.Open(szModName))
					{
						CString strVer = fileVer.GetFixedProductVersion();
						std::wstring modName = szModName;
						DWORD index = modName.rfind(L'\\');
						DWORD suffixIndex = modName.rfind(L'.');
						if(index)
						{
							modName = modName.substr(index+1,suffixIndex - index -1);
						}
						modName += L"\\";
						modName += strVer.GetBuffer();
						strVer.ReleaseBuffer();

						char modPdbPath[MAX_PATH] = {0};
						WideCharToMultiByte(CP_ACP,0, modName.c_str(), -1, modPdbPath, MAX_PATH, NULL, FALSE);

						pdbSerchPath += modPdbPath;
						if(PathFileExistsA(pdbSerchPath.c_str()))
						{
							finalSearchPath = finalSearchPath + ";" + pdbSerchPath;
						}

					}
				}
			}
			finalSearchPath = finalSearchPath + ";" + "\\\\192.168.14.181\\public\\symbols\\Thunder\\7.9.19.4736";
			BOOL bRet = SymInitialize ( 
				hProcess, // Process handle
				finalSearchPath.c_str(),       // user-defined search path -> use default 
				TRUE                 // load symbols for modules in the current process 
				); 
			m_processHandle = hProcess;
		}

		//std::string pdbSerchPath = "\\\\192.168.14.181\\public\\symbols\\Thunder\\7.9.19.4736;D:\\develop\\thunder\\pdb\\Release";		
	}
	

	ULONG status = ProcessTrace(&hTrace, 1, 0, 0);
	if(ERROR_SUCCESS != status && ERROR_CANCELLED != status)
	{
		wprintf(L"ProcessTrace failed with %u\r\n", status);
	}
	else
	{
		OutputResult();
	}
	//CoUninitialize();
	return TRUE;
}