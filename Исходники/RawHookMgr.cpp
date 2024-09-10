//////////////////////////////////////////////////////////////////////////
//
// ¸ðµç ¾²·¹µå¸¦ °¡µ¿½ÃÅ²´Ù
//
//////////////////////////////////////////////////////////////////////////
void CRawHookMgr::ResumeAllThread()
{
	// ¸ðµç ¾²·¹µåµéÀÇ ½º³À¼¦À» ¸¸µì´Ï´Ù.
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
	hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, GetCurrentProcessId());

	if(hThreadSnap == INVALID_HANDLE_VALUE) return;


	THREADENTRY32 te32;
	memset(&te32, 0,sizeof(THREADENTRY32));
	te32.dwSize = sizeof(THREADENTRY32);

	// ÇöÀç ÇÁ·Î¼¼½ºID¿Í ¾²·¹µåID
	DWORD dwCurPID = GetCurrentProcessId();
	DWORD dwCurTID = GetCurrentThreadId();

	// ¾²·¹µå ¼øÈ¸
	BOOL bNext = Thread32First(hThreadSnap, &te32);
	while(bNext)
	{
		if( te32.th32OwnerProcessID == dwCurPID && te32.th32ThreadID != dwCurTID )
		{
			// ¾²·¹µå Á¤Áö
			HANDLE hThread = OpenThread(THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
			if(hThread)
			{
				ResumeThread(hThread);
				//CloseHandle(hThread);
			}
		}

		bNext = Thread32Next(hThreadSnap, &te32);
	}
	CloseHandle (hThreadSnap);

	m_bIsAllThreadSuspended = FALSE;
}