void odPrintfW(const WCHAR * format,...)
{
	WCHAR wbuff[MAX_DBG_MSG_LEN] = {'[','W','Y','X',']',' '};
	va_list body;
	va_start(body,format);
	vswprintf_s(wbuff + 6,MAX_DBG_MSG_LEN - 6,format,body);
	va_end(body);
	OutputDebugStringW(wbuff);
}