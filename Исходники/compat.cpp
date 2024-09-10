char* win32_cgets (char* buffer, int len)
{
	/* We use console ReadConsoleA / ReadConsoleW to be able to read
	   unicode from the win32 console and fallback if seomething fails. */

	HANDLE hIn=GetStdHandle (STD_INPUT_HANDLE);
	if(hIn
	  && (hIn!=INVALID_HANDLE_VALUE)
	    && p_WideCharToMultiByte && p_MultiByteToWideChar)
	{
		DWORD dwRead;
		wchar_t wszBuf[1024];
		char  szBuf[1024];

		// NT and unicode conversion.
		if(ReadConsoleW(hIn, wszBuf, 1024, &dwRead, NULL))
		{
			// Null terminate at end.
			if(wszBuf[dwRead-1]==L'\n')
			{
				wszBuf[dwRead-1]=L'\0';
				dwRead--;
			}

			if(wszBuf[dwRead-1]==L'\r')
			{
				wszBuf[dwRead-1]=L'\0';
				dwRead--;
			}

			wchar_2_UTF8(buffer, wszBuf, len);
			return buffer;
		}

		// Win 9x and unicode conversion.
		if(ReadConsoleA(hIn, szBuf, 1024, &dwRead, NULL))
		{
			// Null terminate at end.
			if(szBuf[dwRead-1]==L'\n')
			{
				szBuf[dwRead-1]=L'\0';
				dwRead--;
			}

			if(szBuf[dwRead-1]==L'\r')
			{
				szBuf[dwRead-1]=L'\0';
				dwRead--;
			}

			// Convert from ansii to wchar_t.
			p_MultiByteToWideChar(GetConsoleCP(),
				0, szBuf, -1, wszBuf, 1024);
			// Convert from wchar_t to UTF-8.
			if(wchar_2_UTF8(buffer, wszBuf, len))
				return buffer;
		}
	}

	// Fallback.
	if(fgets(buffer, len, stdin)) return buffer;
	return NULL;
}