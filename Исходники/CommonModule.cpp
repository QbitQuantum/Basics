// 函数功能：根据指定的错误代码，获取对应的错误描述信息
void GetErrorReason(__in const DWORD dwErrCode, __out CString & strErrMsg)
{
	// Retrieve the system error message for the last-error code
	LPVOID lpMsgBuf = NULL;
	LPVOID lpDisplayBuf = NULL;;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErrCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(_tcslen((LPCTSTR)lpMsgBuf) + 40)*sizeof(TCHAR));
	if (lpDisplayBuf)
	{
		StringCchPrintf((LPTSTR)lpDisplayBuf,
			LocalSize(lpDisplayBuf),
			_T("%s"),
			lpMsgBuf);
		strErrMsg.Format(_T("%s"), lpDisplayBuf);
	}

	lpMsgBuf ? LocalFree(lpMsgBuf) : 0;
	lpDisplayBuf ? LocalFree(lpDisplayBuf) : 0;
}