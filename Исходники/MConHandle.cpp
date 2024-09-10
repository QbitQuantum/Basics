MConHandle::operator const HANDLE()
{
	if (mpp_OutBuffer && *mpp_OutBuffer && (*mpp_OutBuffer != INVALID_HANDLE_VALUE))
	{
		LogHandle(Event::e_GetHandlePtr, *mpp_OutBuffer);
		return *mpp_OutBuffer;
	}

	if (mh_Handle == INVALID_HANDLE_VALUE)
	{
		if (mn_StdMode)
		{
			mh_Handle = GetStdHandle(mn_StdMode);
			LogHandle(Event::e_CreateHandleStd, mh_Handle);
		}
		else
		{
			// Чтобы случайно не открыть хэндл несколько раз в разных потоках
			MSectionLock CS; CS.Lock(&mcs_Handle, TRUE);

			// Во время ожидания хэндл мог быт открыт в другом потоке
			if (mh_Handle == INVALID_HANDLE_VALUE)
			{
				mh_Handle = CreateFileW(ms_Name, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
										0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

				if (mh_Handle != INVALID_HANDLE_VALUE)
				{
					mb_OpenFailed = FALSE;
				}
				else
				{
					mn_LastError = GetLastError();

					if (!mb_OpenFailed)
					{
						mb_OpenFailed = TRUE; // чтобы ошибка вываливалась только один раз!
						char szErrMsg[512], szNameA[10], szSelfFull[MAX_PATH];
						const char *pszSelf;
						char *pszDot;

						if (!GetModuleFileNameA(0,szSelfFull,MAX_PATH))
						{
							pszSelf = "???";
						}
						else
						{
							pszSelf = strrchr(szSelfFull, '\\');
							if (pszSelf) pszSelf++; else pszSelf = szSelfFull;

							pszDot = strrchr((char*)pszSelf, '.');

							if (pszDot) *pszDot = 0;
						}

						WideCharToMultiByte(CP_OEMCP, 0, ms_Name, -1, szNameA, sizeof(szNameA), 0,0);
						_wsprintfA(szErrMsg, SKIPLEN(countof(szErrMsg)) "%s: CreateFile(%s) failed, ErrCode=0x%08X\n", pszSelf, szNameA, mn_LastError);
						HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

						if (h && h!=INVALID_HANDLE_VALUE)
						{
							DWORD dwWritten = 0;
							WriteFile(h, szErrMsg, lstrlenA(szErrMsg), &dwWritten, 0);
						}
					}
				}

				LogHandle(Event::e_CreateHandle, mh_Handle);
			}
		}
	}

	LogHandle(Event::e_GetHandle, mh_Handle);
	return mh_Handle;
};