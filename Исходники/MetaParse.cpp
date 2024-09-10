void Parse_Print(LPCSTR   lpFmt,...)
{	
	CHAR  szBuf[1024];
	va_list  argList;
	memset(szBuf,0,1024);
	va_start(argList,  lpFmt); 
	wvsprintfA(szBuf,lpFmt,  argList);
	va_end(argList); 
	
	printf(szBuf);
}