BOOL CCmd_Describe::HandledCmdSpecificError(LPCTSTR errBuf, LPCTSTR errMsg)
{
	BOOL handledError=TRUE;
#ifndef UNICODE
	if (!StrNCmp(errBuf, NOTRANS, sizeof(NOTRANS)-1))
	{
		CString utf8;
		TCHAR *p = (TCHAR *)errBuf + sizeof(NOTRANS)-1;
		while (*p && *p != '\'')
		{
			TCHAR c1 = *p++;
			TCHAR c2 = *p++;
			if (_istdigit(c1))
				c1 &= 0x0F;
			else
				c1 = (c1 & 0x0F) + 9;
			if (_istdigit(c2))
				c2 &= 0x0F;
			else
				c2 = (c2 & 0x0F) + 9;
			TCHAR c3 = (c1 << 4) + c2;
			utf8.Insert(0x7FFFFFFF, c3);
		}

		// allocate widechar buffer and convert into it
		int lenw = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, 0, 0);
		LPWSTR utf16 = (LPWSTR)::VirtualAlloc(NULL, lenw*sizeof(WCHAR), MEM_COMMIT, PAGE_READWRITE);
		MultiByteToWideChar(CP_UTF8, 0, utf8, -1, utf16, lenw);

		// allocate char buffer and convert back into it, using '?' for
		// unmappable characters
		int len = WideCharToMultiByte(CP_ACP, 0, utf16, -1, 0, 0, NULL, NULL);
		LPSTR buf = (LPSTR)::VirtualAlloc(NULL, len*sizeof(TCHAR), MEM_COMMIT, PAGE_READWRITE);
		WideCharToMultiByte(CP_ACP, 0, utf16, -1, buf, len, NULL, NULL);

		// append to description
		m_Description += buf;
		m_Description += g_CRLF;

		::VirtualFree(buf, 0, MEM_RELEASE);
		::VirtualFree(utf16, 0, MEM_RELEASE);
		handledError = FALSE;
	}
	else
#endif
	{
		m_FatalError = TRUE;
		TheApp()->StatusAdd( errMsg, SV_WARNING, true );	
	}
	return handledError;
}