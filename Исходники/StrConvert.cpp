std::string W2Ansi( const wstring& wszIn )
{
	string szRet;
	if (wszIn.length() <= 0) 
	{
		return szRet;
	}
	LPCWSTR pwszSrc = wszIn.c_str();
	int nWLen = wszIn.length();
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
	
	char* pszDst = new char[nLen+1];
	assert(NULL != pszDst);
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen] = '\0';
	szRet =pszDst;
	delete [] pszDst;
	return szRet;
}