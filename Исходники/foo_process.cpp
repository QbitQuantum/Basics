bool RunProcessing(LPCWSTR fname, int mode, HWND hWnd, int curtrack)
{
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO si;
	PROCESS_INFORMATION pi; 
	HANDLE hReadError, hReadOut, hWriteError, hWriteOut;
	char xxx[1000],tempbuf[1000]; DWORD dd; int i,pos=0;

	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&hReadOut, &hWriteOut, &sa, 0)) return 1;
	if (!CreatePipe(&hReadError, &hWriteError, &sa, 0)) return 1;

	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));

	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = NULL;
	si.hStdOutput = hWriteOut;
	si.hStdError = hWriteError;

	//////////////////////////////////////////////////////////////////////////
	// запуск процесса
	wchar_t cmdline[1000];
	StringCchPrintf(cmdline, 1000, L"aucdtect.exe -m%d -v \"%s\"", mode, fname);
	
	if (!CreateProcess(NULL,cmdline, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, L".", &si, &pi))
	{
		MessageBox(0, L"can not launch aucdtect.exe", NULL, MB_OK);
		return false;
	}
	CloseHandle(hWriteOut);
	CloseHandle(hWriteError);
	int oldpers = -1;

	SendMessage(hWnd, MES_SENDPROCID1, curtrack, GetProcessId(GetCurrentProcess()));
	SendMessage(hWnd, MES_SENDPROCID2, curtrack, pi.dwProcessId);

	while(ReadFile(hReadError,xxx,80,&dd,0))
	{
		for(i=0;i<(int)dd;i++){
			if(xxx[i]==13 || xxx[i]==10){
				if(xxx[i]==13)i++;
				tempbuf[pos] = 0;
				int pers = ParsePercentString(tempbuf);
				// сообщение
				if( pers != oldpers){
					if( !MySendMessage(hWnd, MES_PROGRESS, curtrack, pers) )
						return false;
					oldpers = pers;
				}
				pos=0;
			}else{
				if(xxx[i]==10)continue;
				tempbuf[pos++] = xxx[i]; 
			}
		}
	}
	pos=0;
	while(ReadFile(hReadOut,xxx,80,&dd,0))
	{
		for(int i=0;i<(int)dd;i++){
			if(xxx[i]==13 || xxx[i]==10){
				if(xxx[i]==13)i++;
				tempbuf[pos] = 0;
				StringCchCatA(tempbuf, 1000, "\r\n");
				pos+=2;
			}else{
				if(xxx[i]==10)continue;
				tempbuf[pos++] = xxx[i]; 
			}
		}
	}
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	if( !SendStdOut(hWnd, tempbuf, curtrack) )
		return false;

	return true;
}