	static DWORD WINAPI StdErrReaderThread(LPVOID lpParameter)
	{
		CDownloader* pObj = ((PipeThreadParm*)lpParameter)->pObj;
		char Line[4096+1]; // When output is redirected, RAW ASCII is used
		const DWORD dwToRead = countof(Line)-1;
		DWORD dwRead, nValue, nErrCode;
		BOOL bSuccess;

		CEStr szLine;
		const wchar_t *ptr;
		const wchar_t sProgressMark[]    = L" " CEDLOG_MARK_PROGR;
		const wchar_t sInformationMark[] = L" " CEDLOG_MARK_INFO;
		const wchar_t sErrorMark[]       = L" " CEDLOG_MARK_ERROR;

		LineBuffer buffer = {};
		bool bExit = false;

		while (!bExit)
		{
			bSuccess = ReadFile(pObj->mh_PipeErrRead, Line, dwToRead, &dwRead, NULL);
			if (!bSuccess || dwRead == 0)
			{
				nErrCode = GetLastError();
				break;
			}
			_ASSERTE(dwRead < countof(Line));
			Line[dwRead] = 0; // Ensure it is ASCIIZ
			// Append to the line-buffer
			buffer.AddBlock(Line, dwRead);

			// Parse read line
			while (buffer.GetLine(szLine))
			{
				bool bProgress = false;
				if ((ptr = wcsstr(szLine, sProgressMark)) != NULL)
				{
					bProgress = true;
					if (pObj->mfn_Callback[dc_ProgressCallback])
					{
						// 09:01:20.811{1234} Progr: Bytes downloaded 1656
						wchar_t* ptrEnd = NULL;
						LPCWSTR pszFrom = wcspbrk(ptr+wcslen(sProgressMark), L"0123456789");
						nValue = pszFrom ? wcstoul(pszFrom, &ptrEnd, 10) : 0;

						if (nValue)
						{
							CEDownloadInfo progrInfo = {
								sizeof(progrInfo),
								pObj->m_CallbackLParam[dc_ProgressCallback]
							};
							progrInfo.argCount = 1;
							progrInfo.Args[0].argType = at_Uint;
							progrInfo.Args[0].uintArg = nValue;

							pObj->mfn_Callback[dc_ProgressCallback](&progrInfo);
						}
					}
				}

				// For logging purposes
				if (!bProgress && ((ptr = wcsstr(szLine, sErrorMark)) != NULL))
				{
					if (pObj->mfn_Callback[dc_ErrCallback])
					{
						CEDownloadInfo Error = {
							sizeof(Error),
							pObj->m_CallbackLParam[dc_ErrCallback],
							szLine.ms_Val
						};
						pObj->mfn_Callback[dc_ErrCallback](&Error);
					}
				}
				else //if (bProgress || ((ptr = wcsstr(szLine, sInformationMark)) != NULL))
				{
					if (pObj->mfn_Callback[dc_LogCallback])
					{
						CEDownloadInfo Info = {
							sizeof(Info),
							pObj->m_CallbackLParam[dc_LogCallback],
							szLine.ms_Val
						};
						pObj->mfn_Callback[dc_LogCallback](&Info);
					}
					// Exit?
					ptr = wcsstr(szLine, sInformationMark);
					if (ptr)
					{
						ptr += wcslen(sInformationMark);
						if (wcsncmp(ptr, L"Exit", 4) == 0)
						{
							bExit = true;
							break;
						}
					}
				}
			}
		}

		return 0;
	};