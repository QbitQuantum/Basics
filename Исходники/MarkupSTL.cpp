CStdString CMarkupSTL::x_TextToDoc( const char * szText, bool bAttrib ) const
{
	// Convert text as seen outside XML document to XML friendly
	// replacing special characters with ampersand escape codes
	// E.g. convert "6>7" to "6&gt;7"
	//
	// &lt;   less than
	// &amp;  ampersand
	// &gt;   greater than
	//
	// and for attributes:
	//
	// &apos; apostrophe or single quote
	// &quot; double quote
	//
	static _TCHAR* szaReplace[] = { _T("&lt;"),_T("&amp;"),_T("&gt;"),_T("&apos;"),_T("&quot;") };
	const _TCHAR* pFind = bAttrib?_T("<&>\'\""):_T("<&>");
	CStdString csText;
	const _TCHAR* pSource = szText;
	int nDestSize = _tcslen(pSource);
	nDestSize += nDestSize / 10 + 7;
	_TCHAR* pDest = csText.GetBuffer(nDestSize);
	int nLen = 0;
	_TCHAR cSource = *pSource;
	_TCHAR* pFound;
	while ( cSource )
	{
		if ( nLen > nDestSize - 6 )
		{
			csText.ReleaseBuffer(nLen);
			nDestSize *= 2;
			pDest = csText.GetBuffer(nDestSize);
		}
		if ( (pFound=_tcschr(pFind,cSource)) != NULL )
		{
			pFound = szaReplace[pFound-pFind];
			_tcscpy(&pDest[nLen],pFound);
			nLen += _tcslen(pFound);
		}
		else
		{
			_tccpy( &pDest[nLen], pSource );
			++nLen;
		}
		pSource += _tclen( pSource );
		cSource = *pSource;
	}
	csText.ReleaseBuffer(nLen);
	return csText;
}