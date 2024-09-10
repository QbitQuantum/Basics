int Log(LPCTSTR pszFormat, ...)
{
	va_list ptr;
	va_start(ptr, pszFormat);
	wchar_t pszBuffer[1024];
#pragma warning (push)
#pragma warning(disable : 4995)
#pragma warning(disable : 4996)
	vswprintf( pszBuffer, 1024, pszFormat, ptr );
#pragma warning (pop)
	va_end(ptr);

	theApp.PrintfToString(pszBuffer);

	CCodeTesterDlg* pDlg= (CCodeTesterDlg*)theApp.GetMainWnd();
	if(pDlg)
	{
		theApp.m_CritSection.Lock();
		pDlg->m_OutPutCtrl.OutPut(pszBuffer);
		theApp.m_CritSection.Unlock();
		return wcslen(pszBuffer);
	}

	return 0;
}