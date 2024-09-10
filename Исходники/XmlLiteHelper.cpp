//-----------------------------------------------------------------
//printf形式で文字列データを作る
std::vector<wchar_t> CXmlWriter::FormatV(LPCWSTR lpszFormat, va_list args)
{
	int len = _vscwprintf(lpszFormat, args);
	std::vector<wchar_t> buf(len+1);
	len = vswprintf_s( &buf[0], len+1, lpszFormat, args );
	return buf;
}