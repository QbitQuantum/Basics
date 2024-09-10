BOOL CXTPRegistryManager::GetProfilePoint(LPCTSTR lpszSection, LPCTSTR lpszEntry, CPoint* ptResult)
{
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);

	if (m_strINIFileName.IsEmpty())
	{
		CHKey hSecKey(GetSectionKey(lpszSection, KEY_READ));
		if (hSecKey == NULL)
			return FALSE;

		DWORD dwType, dwCount;
		m_lResult = ::RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
			NULL, &dwCount);

		if (m_lResult != ERROR_SUCCESS)
			return FALSE;

		ASSERT(dwType == REG_BINARY);
		m_lResult = ::RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
			(LPBYTE)ptResult, &dwCount);

		if (m_lResult != ERROR_SUCCESS)
			return FALSE;

		ASSERT(dwType == REG_BINARY);
		return TRUE;
	}
	else
	{
		ASSERT(m_strINIFileName.IsEmpty() == FALSE);

		CString str = GetProfileString(lpszSection, lpszEntry, NULL);
		if (str.IsEmpty())
			return FALSE;

		SCANF_S(str, _T("%ld,%ld"), &ptResult->x, &ptResult->y);
		return TRUE;
	}
}