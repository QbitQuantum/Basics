void COSError::LogMessage(const TCHAR* msg)
{
	static CLock lock;
	TCHAR txt[512];
	size_t len = CTimeWrap::GetNow(txt, _countof(txt));
	_stprintf_s(txt + len, _countof(txt) - len, _T("  %s%s"), msg, _T("\r\n"));
	lock.Lock();
	try
	{
		if(m_proc!=NULL)
			m_proc(txt);
		 else if(m_show_out)
			 _tprintf_s(_T("%s"), txt);

		if(m_log != NULL)
			_fputts(txt, m_log);
	}
	catch(...)
	{
	}
	lock.UnLock();
}