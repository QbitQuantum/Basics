void CConsoleWindow::WriteFormat(LPCTSTR aFormat, ...)
	{
	va_list args;
	va_start(args, aFormat);
	TCHAR buf[KMaxFormatBuf];
	int length = _vsnwprintf(buf, KMaxFormatBuf, aFormat, args);
	Write(buf, length);
	}