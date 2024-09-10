void log_it(VMINT level, char* fmt, va_list ap) 
{
	vm_time_t tm;
	VM_P_HANDLE phandle;
	char text[MAX_APP_NAME_LEN], level_text[10] = {0};
	VMUINT written;

	memset(text, 0x00, sizeof(text));
	memset(level_text, 0x00, sizeof(level_text));
	
	switch(level)
	{
	case VM_DEBUG_LEVEL:
		strcpy(level_text, "DEBUG");
		break;
	case VM_INFO_LEVEL:
		strcpy(level_text, "INFO");
		break;
	case VM_WARN_LEVEL:
		strcpy(level_text, "WARN");
		break;
	case VM_ERROR_LEVEL:
		strcpy(level_text, "ERROR");
		break;
	default:
		strcpy(level_text, "FATAL");
		break;
	};
	
	vm_get_time(&tm);
	phandle = vm_pmng_get_current_handle_ignore_status();
	sprintf(text, "%d-%02.2d-%02.2d %02.2d:%02.2d:%02.2d [%s][PID:%d][%s:%d]- ", tm.year, tm.mon, tm.day, tm.hour,
		tm.min, tm.sec, level_text, phandle, _modFile, _lineNo);

	//vsprintf(text + strlen(text), fmt, ap);

#ifdef __MTK_TARGET__
		vsnprintf(text + strlen(text), 150, fmt, ap);
#else 
		_vsnprintf(text + strlen(text), 150, fmt, ap);
#endif 

	strcat(text, "\n\0");
	
    MMI_PRINT(MOD_MRE, TRACE_INFO,"%s", text);

	if(log_init && def_log_mtk == 1)
	{
		if (FS_Write(log_file, text, (VMUINT)strlen(text), &written) < 0)
		{
			FS_Close(log_file);
			log_init = 0;
			return;
		}
		if (FS_Commit(log_file) < 0)
		{
			FS_Close(log_file);
			log_init = 0;
			return;
		}
	}
	
}