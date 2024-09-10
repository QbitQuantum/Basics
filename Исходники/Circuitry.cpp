void CCircuitry::DoPrint(BYTE* pBuffer, DWORD nLength, LPCTSTR lpszHeader)
{
	CString strLine = lpszHeader;
	strLine += ToASCII( (BYTE*)pBuffer, nLength );
	
	theApp.Message( MSG_DEBUG, (LPCTSTR)strLine );
}