BOOL REPluginList::GetSIDName(LPCWSTR asComputer, PSID pSID, TCHAR* pszOwner, DWORD cchOwnerMax)
{
	BOOL lbExist = FALSE;
	_ASSERTE(pszOwner!=0);
	*pszOwner = 0;

	// Кеш
	if (mp_SidCache && nSidCount)
	{
		for (DWORD i = 0; i < nSidCount; i++)
		{
			if (EqualSid(pSID, mp_SidCache[i].pSID))
			{
				lstrcpyn(pszOwner, mp_SidCache[i].pszOwner, cchOwnerMax);
				return TRUE;
			}
		}
	}
	
	// Если в кеше нет - читаем из системы
	DWORD nAccountLength = 0, nDomainLength = 0;
	SID_NAME_USE snu;
	DWORD nLastErr = 0;
	if (!asComputer)
		asComputer = L"";
	BOOL lbRc = LookupAccountSidW(asComputer, pSID, NULL, &nAccountLength, NULL, &nDomainLength, &snu);
	if (!lbRc) nLastErr = GetLastError();
	if (nAccountLength && nDomainLength)
	{
		LPWSTR pszAccount = (wchar_t*)calloc(nAccountLength+1,2);
		LPWSTR pszDomain = (wchar_t*)calloc(nDomainLength+1,2);
		if (pszAccount && pszDomain)
		{
			if (!LookupAccountSidW(asComputer, pSID, pszAccount, &nAccountLength, pszDomain, &nDomainLength, &snu))
			{
				nLastErr = GetLastError();
			}
			else
			{
				//if (*pszDomain && (nDomainLength+nAccountLength+1) <= cchOwnerMax)
				//{
				//	lstrcpy_t(pszOwner, cchOwnerMax, pszDomain);
				//	lstrcat(pszOwner, _T("\\"));
				//	lstrcpy_t(pszOwner+lstrlen(pszOwner), cchOwnerMax-nDomainLength, pszAccount);
				//} else {
				lstrcpy_t(pszOwner, cchOwnerMax, pszAccount);
				//}
				lbExist = TRUE;
			}
		}
		SafeFree(pszAccount);
		SafeFree(pszDomain);
	}

	// Кеш
	if (!mp_SidCache || (nSidCount+1) > nMaxSidCount)
	{
		nMaxSidCount = nSidCount + 128;
		SidCache *pSidCache = (SidCache*)calloc(nMaxSidCount, sizeof(SidCache));
		if (nSidCount) {
			memmove(pSidCache, mp_SidCache, sizeof(SidCache)*nSidCount);
			SafeFree(mp_SidCache);
		}
		mp_SidCache = pSidCache;
	}

	DWORD nSidLen = GetLengthSid(pSID);
	mp_SidCache[nSidCount].pSID = (PSID)calloc(nSidLen,1);
	CopySid(nSidLen, mp_SidCache[nSidCount].pSID, pSID);
	mp_SidCache[nSidCount].pszOwner = lstrdup(lbExist ? pszOwner : _T(""));
	nSidCount++;

	return lbExist;
}