int DpPrintf(char* str,...)
{
	va_list args;
	va_start( args, str );
	char buf[4*1024];
	vsprintf_s(buf,4*1024,str,args);
	DWORD dwWritten;
	WriteFile( hWrite, buf, strlen(buf)+1, &dwWritten, NULL);  
	FlushFileBuffers(hWrite);
	return 0;
}