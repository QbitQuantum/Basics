void ManagerState::LogWrite(const char *format, ...)
{
	char LogString[1000];
	va_list arg_ptr;
	int len;

	if (log==0)
	{
		log = fopen("ErrorLog.txt", "wt");
		_strdate(LogString);
		len = strlen(LogString);
		LogString[len++]=' ';
		_strtime( LogString+len );
		len = strlen(LogString);
		LogString[len++]=' ';
		LogString[len]=0;
	}
		
	if(strlen(format) > sizeof(LogString)-256) return;
	va_start(arg_ptr, format);
	vsprintf(LogString, format, arg_ptr);
	va_end(arg_ptr);
	if (LogString[0]==0)
		return;

	strcat(LogString, "\n");	

	fwrite(LogString, 1, strlen(LogString), log);
}