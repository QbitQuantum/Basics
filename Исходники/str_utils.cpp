bool t2w(const TCHAR *ts, wchar_t *buff, int bufflen) 
{
	wcsncpy(buff, ts, bufflen);
	return true;
}