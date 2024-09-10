void COXString::Format(LPCTSTR pszFormat, LPCTSTR* rgpsz, int nString)
{
	// NOTE: will not work for strings > 255 characters

	int nTotalLen = PtrToInt(_tcslen(pszFormat));
	int i = 0;
	for (i = 0; i < nString; i++)
	{
		if (rgpsz[i] != NULL)
			nTotalLen += PtrToInt(_tcslen(rgpsz[i]));
	}

	LPCTSTR pchSrc = pszFormat;
	LPTSTR pchDestBegin  =  GetBuffer(nTotalLen+1);
	LPTSTR pchDest = pchDestBegin;
	while (*pchSrc != '\0')
	{
		if (pchSrc[0] == _T('%') && (pchSrc[1] >= _T('1') && pchSrc[1] <= _T('9')))
		{
			i = pchSrc[1] - _T('1');
			pchSrc += 2;
			if (i >= nString)
			{
				TRACE1("COXString::Format : Illegal string index requested %d\n", i);
				*pchDest++ = _T('?');
			}   	
			else if (rgpsz[i] != NULL)
			{
				UTBStr::tcscpy(pchDest, nTotalLen, rgpsz[i]);
				pchDest += _tcslen(pchDest);
			}
		}
		else
		{
			*pchDest++ = *pchSrc++;
		}
	}


	ReleaseBuffer((int)((LPCTSTR)pchDest - (LPCTSTR)pchDestBegin));
	// Release will assert if we went too far
}