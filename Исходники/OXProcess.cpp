BOOL COXProcess::GetImageFileName(CString& sFileName) const
{
	if(GetCurrentProcessID()==m_dwProcessID)
	{
		LPTSTR pszBuffer=sFileName.GetBuffer(MAX_PATH);
		ASSERT(pszBuffer!=NULL);
		BOOL bResult=(::GetModuleFileName(NULL,pszBuffer,MAX_PATH)>0);
		sFileName.ReleaseBuffer();

		return bResult;
	}

	VERIFY(InitializeProcessFunctions());

	if(m_bIsRunningNT)
	{
		// Using the process ID, open up a handle to the process
		HANDLE hProcess=::OpenProcess(
			PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,m_dwProcessID);
		if(hProcess==NULL)
		{
			if(m_dwProcessID==0)
			{
				VERIFY(sFileName.LoadString(IDS_OX_PROCESSIDLE));//"System Idle Process"
				return TRUE;
			}
			if(m_dwProcessID==2 || m_dwProcessID==8)
			{
				VERIFY(sFileName.LoadString(IDS_OX_PROCESSSYSTEM));//"System"
				return TRUE;
			}
			return FALSE;
		}
            
		HMODULE moduleArray[1024];
		DWORD cbNeeded;
		// EnumProcessModules returns an array of HMODULEs for the process
		if(!pfnEnumProcessModules(hProcess,moduleArray,sizeof(moduleArray),&cbNeeded))
		{
			::CloseHandle(hProcess);
			if(m_dwProcessID==0)
			{
				VERIFY(sFileName.LoadString(IDS_OX_PROCESSIDLE));//"System Idle Process"
				return TRUE;
			}
			if(m_dwProcessID==2 || m_dwProcessID==8)
			{
				VERIFY(sFileName.LoadString(IDS_OX_PROCESSSYSTEM));//"System"
				return TRUE;
			}
			return FALSE;
		}

		// First module is the EXE
		char szModuleName[MAX_PATH];
		// GetModuleFileNameEx is like GetModuleFileName, but works
		// in other process address spaces
		pfnGetModuleFileNameExA(
			hProcess,moduleArray[0],szModuleName,sizeof(szModuleName));
		sFileName=szModuleName;

		::CloseHandle(hProcess);    // We're done with this process handle
	}
	else
	{
	    // Create a ToolHelp32 snapshot containing the process list
	    //  
	    HANDLE hSnapshotProcess;
	    hSnapshotProcess=pfnCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	    if(hSnapshotProcess==NULL)
		{
			return FALSE;
		}

		// Iterate through each of the processes in the snapshot
		PROCESSENTRY32 procEntry={ sizeof(PROCESSENTRY32) };
		BOOL bProcessContinue;
		BOOL bSuccess=FALSE;
		for(bProcessContinue=pfnProcess32First(hSnapshotProcess,&procEntry);
			bProcessContinue;
			bProcessContinue=pfnProcess32Next(hSnapshotProcess,&procEntry))
		{
			if(m_dwProcessID==procEntry.th32ProcessID)
			{
				sFileName=procEntry.szExeFile;
				bSuccess=TRUE;
				break;
			}
		}
    
		::CloseHandle(hSnapshotProcess);    // Done with process list snapshot

		if(!bSuccess)
		{
			return FALSE;
		}
	}

	return TRUE;
}