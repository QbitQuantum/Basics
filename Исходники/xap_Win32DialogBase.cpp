bool XAP_Win32DialogBase::getDlgItemText(HWND hWnd, int nIDDlgItem, UT_Win32LocaleString& str)
{	
	UT_return_val_if_fail(IsWindow(hWnd), false);
	
	wchar_t szBuff [1024];	
	bool rslt;
	
	rslt = (bool) GetDlgItemTextW(hWnd, nIDDlgItem, szBuff, 1024);
	
	if (rslt == true)
		str.fromLocale(szBuff);
	else
		str.clear();
	
	return rslt;
}