/**------------------------------------------------------**/
void print_R(char* out, const char *format, ...)
{
	
	LOG_FILETYPE stderr_f;
	char buffer[64];
	
	va_list argptr;
	va_start(argptr, format);
	VSNPRINTF(buffer, format, argptr);
	va_end(argptr);

	if(out == NULL)
	{
		printf_terminal(buffer);
	}else
	{
		if(!monitor_openappend(out,&stderr_f))
		{
			if(!monitor_openwrite(out,&stderr_f))
			{
				return;
			}
		}
		/* print to file */
		(void)monitor_seek_end(&stderr_f);
		(void)monitor_write(buffer,&stderr_f);
		(void)monitor_close(&stderr_f);
	}
	
}