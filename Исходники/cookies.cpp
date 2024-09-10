VOID NotifyNewCookie(LPSTR strDomain)
{
	WCHAR strDomainW[1024];
	_snwprintf_s(strDomainW, 1024, _TRUNCATE, L"%S", strDomain);

	for (DWORD i=0; i<SOCIAL_ENTRY_COUNT; i++)
		if (!wcscmp(strDomainW, pSocialEntry[i].strDomain))
			pSocialEntry[i].bNewCookie = TRUE;
}