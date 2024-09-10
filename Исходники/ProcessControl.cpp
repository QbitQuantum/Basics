BOOL
CProcessControl::Get(
					 __in	BOOL	bCurrentProc,
					 __in	ULONG	ulPid,
					 __out	LPSTR	lpOutBuf,
					 __in	ULONG	ulOutBufSizeCh
					 )
{
	BOOL	bRet					= FALSE;

	HANDLE	hProc					= NULL;
	DWORD	dwProcPathLenCh			= 0;
	CHAR	chProcPathDev[MAX_PATH]	= {0};
	CHAR	chVolNameDev[MAX_PATH]	= {0};
	CHAR	chVolName[MAX_PATH]		= {0};


	__try
	{
		if (!lpOutBuf || !ulOutBufSizeCh || (!bCurrentProc && !ulPid))
		{
			printfPublic("input arguments error. %d %d 0x%p %d", bCurrentProc, ulPid, lpOutBuf, ulOutBufSizeCh);
			__leave;
		}

		ZeroMemory(lpOutBuf, ulOutBufSizeCh * sizeof(CHAR));

		if (bCurrentProc)
		{
			if (!CModulePath::Get(NULL, lpOutBuf, ulOutBufSizeCh))
			{
				printfPublic("Get failed");
				__leave;
			}

			bRet = TRUE;
			__leave;
		}

		hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, ulPid);
		if (!hProc)
		{
			printfPublic("OpenProcess failed. (%d)", GetLastError());
			__leave;
		}

		if (m_QueryFullProcessImageNameA)
		{
			dwProcPathLenCh = ulOutBufSizeCh;
			if (!m_QueryFullProcessImageNameA(hProc, 0, lpOutBuf, &dwProcPathLenCh))
			{
				printfPublic("QueryFullProcessImageName failed. (%d)", GetLastError());
				__leave;
			}

			bRet = TRUE;
			__leave;
		}

		if (!GetProcessImageFileNameA(hProc, chProcPathDev, _countof(chProcPathDev)))
		{
			printfPublic("GetProcessImageFileName failed. (%d)", GetLastError());
			__leave;
		}

		strcat_s(chVolName, _countof(chVolName), "A:");
		for (; _T('Z') >= *chVolName; (*chVolName)++)
		{
			ZeroMemory(chVolNameDev, sizeof(chVolNameDev));
			if (!QueryDosDeviceA(chVolName, chVolNameDev, _countof(chVolNameDev)))
			{
				if (2 == GetLastError())
					continue;
				else
				{
					printfPublic("QueryDosDevice failed. (%d)", GetLastError());
					__leave;
				}
			}

			if (0 == _strnicmp(chProcPathDev, chVolNameDev, strlen(chVolNameDev)))
			{
				bRet = TRUE;
				break;
			}
		}

		if (bRet)
		{
			strcat_s(lpOutBuf, ulOutBufSizeCh, chVolName);
			strcat_s(lpOutBuf, ulOutBufSizeCh, chProcPathDev + strlen(chVolNameDev));
		}
	}
	__finally
	{
		if (hProc)
		{
			CloseHandle(hProc);
			hProc = NULL;
		}
	}

	return bRet;
}