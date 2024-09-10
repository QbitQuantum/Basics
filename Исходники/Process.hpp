	BOOL KillProcessByName(tstring& strProcessName)
	{
		PROCESSENTRY32  pe	= {sizeof(pe)};
		HANDLE			hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		Process32First(hSnapshot, &pe);

		do{
			if( _tcsicmp(pe.szExeFile,strProcessName.c_str())==0 )
			{
				HANDLE hProcess = OpenProcess( PROCESS_TERMINATE , FALSE , pe.th32ProcessID );
				if ( hProcess != NULL )
				{
					TerminateProcess(hProcess, EXIT_SUCCESS);
					CloseHandle( hProcess );
				}
					
				break;
			}
		}while(Process32Next(hSnapshot, &pe));

		return TRUE;
	}