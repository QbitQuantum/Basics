bool CHTTPParser::readString(CString& rString, HINTERNET hFile)
{
	const DWORD dwBufferSize = 1024;
	DWORD dwRead = 0;
	CHAR svBuffer[dwBufferSize];

	rString = _T("");

	ZeroMemory(svBuffer, dwBufferSize);
	
	while(InternetReadFile(hFile, svBuffer, dwBufferSize, &dwRead) && dwRead != 0)
	{
		CA2T pszBuffer((LPCSTR)svBuffer);
		
		rString.Append(pszBuffer);
	}

	return true;
}