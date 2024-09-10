/**
 * @brief Get canonical application name (all non-alphanumeric characters are stripped).
 * @param pszAppName - buffer for resulting application name.
 * @param nBufferSize - size of file name buffer.
 * @param bAllowSpaces - true if spaces are allowed.
 * @return length of the name.
 */
size_t GetCanonicalAppName(PTSTR pszAppName, size_t nBufferSize, BOOL bAllowSpaces)
{
	if (nBufferSize == 0)
		return 0;
	if (*g_szAppName != _T('\0'))
	{
		--nBufferSize;
		size_t nStrLength = _tcslen(g_szAppName);
		if (nStrLength > nBufferSize)
			nStrLength = nBufferSize;
		size_t nSrcPos = 0, nDstPos = 0;
		WORD wCharMask = C1_ALPHA | C1_DIGIT;
		if (bAllowSpaces)
			wCharMask |= C1_SPACE;
		while (nSrcPos < nStrLength)
		{
			WORD arrCharType[2];
#ifdef _UNICODE
			size_t nCharSize = GetUnicodeCharSize((const BYTE*)(g_szAppName + nSrcPos)) / sizeof(WCHAR);
			GetStringTypeW(CT_CTYPE1, g_szAppName + nSrcPos, (int)nCharSize, arrCharType);
#else
			size_t nCharSize = IsDBCSLeadByte(g_szAppName[nSrcPos]) ? 2 : 1;
			GetStringTypeA(LOCALE_USER_DEFAULT, CT_CTYPE1, g_szAppName + nSrcPos, (int)nCharSize, arrCharType);
#endif
			if (*arrCharType & wCharMask)
			{
				pszAppName[nDstPos++] = g_szAppName[nSrcPos++];
				if (nCharSize > 1)
					pszAppName[nDstPos++] = g_szAppName[nSrcPos++];
			}
			else
			{
				/*if (*arrCharType & C1_SPACE)
					pszAppName[nDstPos++] = _T('_');*/
				nSrcPos += (DWORD)nCharSize;
			}
		}
		pszAppName[nDstPos] = _T('\0');
		return nDstPos;
	}
	else
	{
		TCHAR szAppFileName[MAX_PATH];
		if (! GetModuleFileName(NULL, szAppFileName, countof(szAppFileName)))
			return FALSE;
		PTSTR pszFileName = PathFindFileName(szAppFileName);
		PathRemoveExtension(pszFileName);
		_tcscpy_s(pszAppName, nBufferSize, pszFileName);
		return _tcslen(pszAppName);
	}
}