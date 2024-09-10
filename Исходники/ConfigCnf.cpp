void CreateConfigPath()
{
	WCHAR appdata[MAX_PATH];

	pathconfigxml[0] = L'\0';

	if(SHGetFolderPathW(NULL, CSIDL_APPDATA | CSIDL_FLAG_DONT_VERIFY, NULL, SHGFP_TYPE_CURRENT, appdata) != S_OK)
	{
		appdata[0] = L'\0';
		return;
	}

	wcsncat_s(appdata, L"\\", _TRUNCATE);
	wcsncat_s(appdata, TextServiceDesc, _TRUNCATE);
	wcsncat_s(appdata, L"\\", _TRUNCATE);

	_wmkdir(appdata);
	SetCurrentDirectoryW(appdata);

	_snwprintf_s(pathconfigxml, _TRUNCATE, L"%s%s", appdata, fnconfigxml);

	LPWSTR pszUserSid;
	WCHAR szDigest[32+1];
	MD5_DIGEST digest;
	int i;

	ZeroMemory(cnfmutexname, sizeof(cnfmutexname));
	ZeroMemory(szDigest, sizeof(szDigest));

	if(GetUserSid(&pszUserSid))
	{
		if(GetMD5(&digest, (CONST BYTE *)pszUserSid, (DWORD)wcslen(pszUserSid)*sizeof(WCHAR)))
		{
			for(i=0; i<_countof(digest.digest); i++)
			{
				_snwprintf_s(&szDigest[i*2], _countof(szDigest)-i*2, _TRUNCATE, L"%02x", digest.digest[i]);
			}
		}

		LocalFree(pszUserSid);
	}

	_snwprintf_s(cnfmutexname, _TRUNCATE, L"%s%s", VIMCNFMUTEX, szDigest);
}