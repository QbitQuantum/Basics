// this function creates a BSTR but it actually has an ANSI string inside
BSTR AFXAPI AfxBSTR2ABSTR(BSTR bstrW)
{
#pragma warning(push)
#pragma warning(disable:4068)
#pragma prefast(push)
#pragma prefast(disable:325, "We want to duplicate NULL semantics on the way out of this function")
	if (bstrW == NULL)
		return NULL;
#pragma prefast(pop)
#pragma warning(pop)

	int nLen = SysStringLen(bstrW); //not including NULL
	int nBytes = WideCharToMultiByte(CP_ACP, 0, bstrW, nLen,
		NULL, NULL, NULL, NULL); //number of bytes not including NULL
	BSTR bstrA = SysAllocStringByteLen(NULL, nBytes); // allocates nBytes
	if(!bstrA)
	{
		AfxThrowMemoryException();
	}
	VERIFY(WideCharToMultiByte(CP_ACP, 0, bstrW, nLen, (LPSTR)bstrA, nBytes, NULL,
		NULL) == nBytes);
	return bstrA;
}