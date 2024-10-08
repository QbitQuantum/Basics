	DWORD WaitWithMessageLoop(HANDLE* hEvent, DWORD nCount, DWORD dwMilliseconds)
	{
		DWORD dwRet = WAIT_FAILED;

		DWORD dwMaxTick = (dwMilliseconds == INFINITE) ? 0 : GetTickCount() + dwMilliseconds;

		while (1)
		{
			DWORD dwTimeOut = 0;
			if (dwMilliseconds == INFINITE)
			{
				dwTimeOut = INFINITE;
			}
			else{
				dwTimeOut = (dwMaxTick < GetTickCount()) ? 0 : dwMaxTick - GetTickCount(); //记算还要等待多秒微秒
			}
			// wait for event or message, if it's a message, process it and return to waiting state
			//dwRet = MsgWaitForMultipleObjectsEx(nCount, hEvent, dwTimeOut, QS_ALLINPUT, MWMO_ALERTABLE);
			dwRet = MsgWaitForMultipleObjectsEx(nCount, hEvent, dwTimeOut, QS_PAINT | QS_TIMER|QS_SENDMESSAGE , MWMO_ALERTABLE);
			if (dwRet < WAIT_OBJECT_0 + nCount)
			{
				//OutputDebugStringA("WaitWithMessageLoop() event triggered.\n");
				return dwRet;
			}
			else if (dwRet == WAIT_OBJECT_0 + nCount)
			{
				// process window messages
				//OutputDebugStringA("DoEvents.\n");
				DoEvents();
			}
			else if (dwRet == WAIT_TIMEOUT)
			{
				// timed out !
				//OutputDebugStringA("timed out!\n");
				return dwRet;
			}
			else if (dwRet == WAIT_FAILED)
			{
				//OutputDebugStringA("wait failed!\n");
				return dwRet;
			}
			else{
				return dwRet;
			}

		}
	}