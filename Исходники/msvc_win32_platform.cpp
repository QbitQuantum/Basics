// ------------------------------------------------------------------
bool win32_platform::get_backtrace_frame_info(void* frame, char* function,
	char* filename, int* line_number)
{
	IMAGEHLP_SYMBOL64* symbol = (IMAGEHLP_SYMBOL64*)malloc(
		sizeof(IMAGEHLP_SYMBOL64) + DEREFEREE_MAX_FUNCTION_LEN);

	symbol->SizeOfStruct = sizeof(IMAGEHLP_SYMBOL64);
	symbol->MaxNameLength = DEREFEREE_MAX_FUNCTION_LEN;
	memset((char*)symbol + sizeof(IMAGEHLP_SYMBOL64), 0,
		DEREFEREE_MAX_FUNCTION_LEN);

	DWORD64 displacement = 0;
	BOOL res = SymGetSymFromAddr64(GetCurrentProcess(), (DWORD64)frame,
		&displacement, symbol);

	if(res)
	{
		strncpy(function, (char*)symbol->Name,
			DEREFEREE_MAX_FUNCTION_LEN - 1);

		IMAGEHLP_LINE64 line_info = { 0 };
		line_info.SizeOfStruct = sizeof(line_info);
		DWORD displacement2 = 0;
		
		res = SymGetLineFromAddr64(GetCurrentProcess(), (DWORD64)frame,
			&displacement2, &line_info);

		if(res)
		{
			strncpy(filename, (char*)line_info.FileName,
				DEREFEREE_MAX_FILENAME_LEN - 1);
			*line_number = (int)line_info.LineNumber;
		}
		else
		{
			filename[0] = '\0';
			*line_number = 0;
		}

		free(symbol);
		return true;
	}
	else
	{
		free(symbol);
		return false;
	}
}