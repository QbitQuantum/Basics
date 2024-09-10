/* 设置日志文件名 */
void SetLogFile( char *format , ... )
{
	va_list		valist ;
	
	va_start( valist , format );
	VSNPRINTF( g_log_pathfilename , sizeof(g_log_pathfilename)-1 , format , valist );
	va_end( valist );
	
	return;
}