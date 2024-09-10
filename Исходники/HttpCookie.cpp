BOOL CCookieMgr::LoadFromFile(LPCSTR lpszFile, BOOL bKeepExists)
{
	BOOL isOK	= FALSE;
	FILE* pFile = nullptr;

	if((pFile = fopen(lpszFile, "r")) == nullptr)
		goto _ERROR_END;

	{
		CStringA strDomain;
		CStringA strPath;
		CCookie cookie;

		char szBuffer[8192];
		int iBufferSize			= _countof(szBuffer);
		__time64_t tmCurrent	= _time64(nullptr);
		CCookieSet* pCookieSet	= nullptr;

		CWriteLock locallock(m_cs);

		if(!bKeepExists)
			ClearDomainCookiesNoLock();

		while(fgets(szBuffer, iBufferSize, pFile) != nullptr)
		{
			char c = szBuffer[0];

			if(c == '\n' || c == '\r')
				continue;
			else if(c != '\t')
			{
				if(!LoadDomainAndPath(szBuffer, strDomain, strPath))
					goto _ERROR_END;

				pCookieSet	= GetCookieSetNoLock(strDomain, strPath);
			}
			else
			{
				if(!LoadCookie(szBuffer, strDomain, strPath, cookie))
					goto _ERROR_END;

				if(cookie.expires <= tmCurrent)
					continue;

				if(pCookieSet)
				{
					if(bKeepExists)
					{
						CCookieSetCI it = pCookieSet->find(cookie);
						if(it != pCookieSet->end())
							continue;
					}

					pCookieSet->emplace(move(cookie));
				}
				else
				{
					SetCookieNoLock(cookie, FALSE);
					pCookieSet = GetCookieSetNoLock(strDomain, strPath);
				}
			}
		}

		if(!feof(pFile))
			goto _ERROR_END;
	}

	isOK = TRUE;

_ERROR_END:

	if(pFile) fclose(pFile);

	return isOK;
}