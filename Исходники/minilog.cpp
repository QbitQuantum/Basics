// line = "04:13:01.610|DEB| ogger\logger.c| 353| Log file created (05-09-2001)"
void VEMiniLog::Print(int level, const char *pszModule, int iLineNumber, const char *pszFormat, ...)
{
	// is tracing off?
	if(level > m_nTraceLevel) return;

	// error type
	const char *errType = 
		level==-1 ? "SYS" : 
		level==-2 ? "ERR" : 
		"DEB";

 	// store time, module name & line number
	_strtime(gszParam);
	const char *pmod=strrchr(pszModule,'\\'); 
	pmod=pmod!=0?pmod+1:pszModule;
	sprintf(&gszParam[strlen(gszParam)], ".000|%s|%-13s|%04d|",errType, pmod, iLineNumber);

	// get ... parameters
    va_list	arg_ptr;
    va_start( arg_ptr, pszFormat );
    _vsnprintf( &gszParam[strlen(gszParam)], sizeof(gszParam)-strlen(gszParam), pszFormat, arg_ptr );
    va_end( arg_ptr );

	// write line of log
	FILE *fp=fopen(GetLogFileName(),"ab");
	if(fp==0) return;
	fwrite(gszParam,strlen(gszParam),1,fp);
	fwrite(ENDOFLINE,strlen(ENDOFLINE),1,fp);
	fclose(fp);
}