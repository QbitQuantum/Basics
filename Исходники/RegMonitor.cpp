BOOL WINAPI DetourHttpSendRequestW(HINTERNET hRequest, LPCWSTR lpszHeaders, DWORD dwHeadersLength, LPVOID lpOptional, DWORD dwOptionalLength)
{	
	USES_CONVERSION;
	// 减少多次转换
	if(hwid == L"")
	{
		wstring thwid(A2W(GenHWID2().c_str()));
		hwid = thwid;
	}
	if(sn == L"")
	{
		wstring tsn(A2W(CSNManager::GetInstance()->GetSN().c_str()));
		sn = tsn;
	}

 	TCHAR szBuf[1024];
	memset(szBuf, 0, sizeof(szBuf));
	swprintf_s(szBuf, L"MoneyhubUID: %s\r\nSN:%s\r\n",hwid.c_str(),sn.c_str());
	HttpAddRequestHeadersW(hRequest, szBuf, -1, HTTP_ADDREQ_FLAG_ADD | HTTP_ADDREQ_FLAG_REPLACE); 

	return OldHttpSendRequestW(hRequest, lpszHeaders, dwHeadersLength, lpOptional, dwOptionalLength);
}