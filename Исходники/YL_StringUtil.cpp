bool YL_StringUtil::Format(string& str, const char* szFmt, ...)
{
	va_list argList;
	int len;
	char* buf;

	va_start( argList, szFmt );
	len = _vscprintf(szFmt, argList) + 1;

	buf = new char[len];

	if(vsprintf(buf, szFmt, argList) < 0)
	{
		return false;
	}

	str = string(buf, len - 1);
	delete[] buf;
	va_end( argList );
	return true;
}