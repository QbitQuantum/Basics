///////////////////////////////////////////////////////////////////////////////
//
// _AssocQueryString() - private function
//
// Purpose:     Calls AssocQueryStringW() to get associated application.
//
// Parameters:  See AssocQueryString() in MSDN.
//
// Returns:     HRESULT - S_OK = AssocQueryStringW() succeeded
//
// Notes:       This code is necessary because AssocQueryStringA() doesn't 
//              work (confirmed by MS Tech Support), so for ANSI version
//              we convert parameters to Unicode and call wide version.
//
static HRESULT _AssocQueryString(ASSOCF flags, 
								 ASSOCSTR str, 
								 LPCTSTR pszAssoc, 
								 LPCTSTR pszExtra,	// may be NULL
								 LPTSTR pszOut, 
								 DWORD *pcchOut)	// size of pszOut in TCHARs
{
	HRESULT hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_FILE_NOT_FOUND);

	if (!pszOut || !pcchOut || (*pcchOut == 0) || 
		!pszAssoc || (pszAssoc[0] == _T('\0')))
	{
		TRACE(_T("ERROR: _AssocQueryString: bad parameters\n"));
		return hr;
	}

	*pszOut = 0;

#ifdef _UNICODE

	hr = AssocQueryStringW(flags, str, pszAssoc, pszExtra, pszOut, pcchOut);

#else

	// get size of buffer for pszAssoc
	int wlen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszAssoc, -1, NULL, 0);
	TRACE(_T("wlen=%d\n"), wlen);
	WCHAR *pszAssocW = new WCHAR [wlen+16];
	pszAssocW[0] = 0;

	// convert pszAssoc to unicode
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszAssoc, -1, pszAssocW, wlen+2);

	// get size of buffer for pszExtra
	WCHAR *pszExtraW = NULL;
	if (pszExtra  && (pszExtra[0] != _T('\0')))
	{
		wlen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszExtra, -1, NULL, 0);
		TRACE(_T("wlen=%d\n"), wlen);
		pszExtraW = new WCHAR [wlen+16];
		pszExtraW[0] = 0;

		// convert pszExtra to unicode
		MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszExtra, -1, pszExtraW, wlen+2);
	}

	// create buffer for wide-character output
	WCHAR *pszOutW = new WCHAR [MAX_PATH*3];
	pszOutW[0] = 0;
	DWORD dwOut = MAX_PATH*3 - 4;

	// get exe filepath
	hr = AssocQueryStringW(flags, str, pszAssocW, pszExtraW, pszOutW, &dwOut);

	// convert exe filepath to ansi
	WideCharToMultiByte(CP_ACP, 0, pszOutW, -1, pszOut, *pcchOut, NULL, NULL);
	*pcchOut = _tcslen(pszOut);

	delete [] pszAssocW;
	delete [] pszExtraW;
	delete [] pszOutW;

#endif

	return hr;
}