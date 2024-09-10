void CDiagRec::setNTError(DWORD errorMsgLang, const char *FuncName)
{
	LPVOID	lpMsgBuf;
	DWORD	error;
	char	buffer[10];

	error = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				error,
				errorMsgLang,
				(LPTSTR) &lpMsgBuf,
				0,
				NULL);
	setDiagRec(DRIVER_ERROR, IDS_NT_ERROR, error, (char *)lpMsgBuf, NULL, 
		SQL_ROW_NUMBER_UNKNOWN, SQL_COLUMN_NUMBER_UNKNOWN, 2, FuncName, _itoa(error,buffer,10));
	LocalFree(lpMsgBuf);
}