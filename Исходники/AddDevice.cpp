void CAddDevice::GetONVIFStreamPort(const CString& str, WORD& nPort)
{
	CString cs_rtsp = str;
	wchar_t *wstr = NULL;
	wchar_t str_rtsp[128];
	wcscpy(str_rtsp, cs_rtsp.GetBuffer());
	wstr = wcstok(str_rtsp,_T(":"));
	wstr = wcstok(NULL,_T(":"));
	if(wstr)
	{
		wstr = wcstok(NULL,_T("/"));
	}

	if (wstr)
		nPort = _ttoi(wstr);
	else
		nPort = 554;
	cs_rtsp.ReleaseBuffer();
}