void UnicodeCString2Ansi(CString &str, char* pDst, int nDstLen)
{
	USES_CONVERSION;

#if _UNICODE
	char* pTmp = W2A(str);
#else
	char* pTmp = (char*)(LPCTSTR)str;
#endif

	int nLen = strnlen_s(pTmp, nDstLen-1);

	ZeroMemory(pDst, nDstLen);
	strcpy_s(pDst, nLen+1, pTmp);
}