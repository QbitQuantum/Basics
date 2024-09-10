void LogMessage( const wchar_t *text, ... )
{
	if (!g_LogFile) return;

	wchar_t buf[2048];
	int len=Sprintf(buf,_countof(buf),L"%8d: ",GetTickCount()-g_LogTime);
	fwrite(buf,2,len,g_LogFile);

	va_list args;
	va_start(args,text);
	len=Vsprintf(buf,_countof(buf),text,args);
	va_end(args);
	fwrite(buf,2,len,g_LogFile);

	fwrite(L"\r\n",2,2,g_LogFile);

	fflush(g_LogFile);
}