void RichEditEventLogger::AddToLog(LogLevel level, uint8_t * data, int32_t length, const TCHAR * msg, ...)
{
	if (level < m_LogLevel)
	{
		return;
	}

	TCHAR * pLogMsg = logMsgBuffer;
	time_t rawtime;
	struct tm timeinfo;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	_tcsftime(pLogMsg, MAX_LOG_MSG_LENGTH, _T("%d-%m-%Y %I:%M:%S: "), &timeinfo);
	pLogMsg += _tcslen(logMsgBuffer);

	va_list argptr;
	va_start(argptr, msg);
	_vstprintf_s(pLogMsg, MAX_LOG_MSG_LENGTH - _tcslen(logMsgBuffer), msg, argptr);
	va_end(argptr);

	int32_t logMsgLength = sizeof(logMsgBuffer) / sizeof(TCHAR);
	int32_t currentLength = _tcslen(logMsgBuffer);

	TCHAR hexStr[16];
	for (int32_t i = 0; i < length; i++)
	{
		if ((i % 16) == 0)
		{
			_tcscat_s(logMsgBuffer, logMsgLength - currentLength, _T("\n"));
			currentLength = _tcslen(logMsgBuffer);
			pLogMsg = logMsgBuffer + currentLength;
		}
		_stprintf_s(hexStr, sizeof(hexStr) / sizeof(TCHAR), _T(" %02X"), data[i]);
		_tcscat_s(pLogMsg, logMsgLength - currentLength, hexStr);
		currentLength += _tcslen(hexStr);
		pLogMsg = logMsgBuffer + currentLength;
	}
	_tcscat_s(pLogMsg, logMsgLength - currentLength, _T("\n"));

	m_Logger->SetSel(-1, -1);
	m_Logger->ReplaceSel(logMsgBuffer);
	m_Logger->PostMessage(WM_VSCROLL, SB_BOTTOM, NULL);
}