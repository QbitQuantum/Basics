bool CMDIClient::killKernel(bool bKill)
{
	bool bReturn = false;
	wchar_t p[260] = {L"moneyhub.exe"};
	this->getPriviledge();

	HANDLE hand = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(hand != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32W pew = {sizeof(PROCESSENTRY32W)};
		bool bHaveOther=false;
		Process32FirstW(hand,&pew );	

		do{
			_wcslwr_s(pew.szExeFile, 260);

			if(!wcscmp(pew.szExeFile,p) && GetCurrentProcessId()!=pew.th32ProcessID)
			{
				HANDLE h = OpenProcess(PROCESS_TERMINATE, FALSE, pew.th32ProcessID);
				if( h )
				{
					if( TerminateProcess(h, 1) )
						bReturn = true;

					CloseHandle(h);
				}
			}

		}while(Process32NextW(hand,&pew));


		CloseHandle(hand);	
	}

	return bReturn ;
}