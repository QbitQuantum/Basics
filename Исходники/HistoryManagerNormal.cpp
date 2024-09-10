BOOL CHistoryManager::PrepareTempDirs()
{
	for (int i = 0; i < TEMP_KEY_COUNT; i++)
	{
		HKEY key;
		if (RegOpenKeyExA(HKEY_CURRENT_USER, REG_TEMP_FOLDER, 0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS)
			continue;

		g_TempPaths[i].strRegKey = g_TempKey[i];

		WCHAR szPath[1024];
		DWORD Size = 1024;
		if (RegQueryValueExW(key, g_TempPaths[i].strRegKey.c_str(), NULL, NULL, (LPBYTE)szPath, &Size) != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			continue;
		}

		CStringW strPath = szPath;
		strPath.Replace(L'/', L'\\');
		if (strPath[strPath.GetLength() - 1] != L'\\')
			strPath += L'\\';

		//////////////////////////////////////////////////////////////////////////
		// Create Redirect Directory

		CStringW strTemp = m_strRedirectPath + CStringW(g_TempPaths[i].strRegKey.c_str());
		if (!CreateDirectoryW(strTemp, NULL) && GetLastError() != ERROR_ALREADY_EXISTS)
			continue;
		SetFileAttributesW(strTemp, FILE_ATTRIBUTE_HIDDEN);
		
		//////////////////////////////////////////////////////////////////////////
		// 

 		WCHAR szDir[1024], szShort[1024], szLong[1024];
 		ExpandEnvironmentStringsW((LPWSTR)(LPCWSTR)strPath, (LPWSTR)szDir, _countof(szDir));
 		GetShortPathNameW(szDir, szShort, _countof(szShort));
		GetLongPathNameW(szDir, szLong, _countof(szLong));
		
		_wcslwr_s(szShort);
		_wcslwr_s(szLong);

		g_TempPaths[i].strShortTempDir = szShort;
		g_TempPaths[i].strLongTempDir = szLong;

		SplitPath(g_TempPaths[i].strShortTempDir, g_TempPaths[i].vecShortParts);
		SplitPath(g_TempPaths[i].strLongTempDir, g_TempPaths[i].vecLongParts);

		RegCloseKey(key);
	}

	return true;
}