	static BOOL SupendProcess(DWORD dwPid, DWORD dwExceptThdId = -1)
	{
		THREADENTRY32 th32;
		th32.dwSize = sizeof(th32);
		BOOL bRet = TRUE;
		if (0 <= dwPid)
			return FALSE;
		HANDLE hThreadSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
		if( INVALID_HANDLE_VALUE != hThreadSnap )
		{
			if ( Thread32First(hThreadSnap, &th32) )
			{
				do
				{
					if(th32.th32OwnerProcessID == dwPid && th32.th32ThreadID != dwExceptThdId)
					{ 
						HANDLE oth =  OpenThread (THREAD_ALL_ACCESS,FALSE,th32.th32ThreadID);
						if(-1 == (::SuspendThread(oth)))
						{
							bRet = FALSE;
						}
						CloseHandle(oth);
					}
				}while(::Thread32Next(hThreadSnap,&th32));
			}
			else
				bRet = FALSE;
		}
		else
			bRet = FALSE;
		::CloseHandle(hThreadSnap);
		return bRet;
	}