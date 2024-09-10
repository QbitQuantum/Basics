void CLogFile::Printf(const char * szFormat, ...)
{
	// Lock the mutex
	m_mutex.TryLock(1);

	// Collect the arguments
	va_list vaArgs;
	char szBuffer[2048];
	va_start(vaArgs, szFormat);
	vsnprintf_s(szBuffer, sizeof(szBuffer), szFormat, vaArgs);
	va_end(vaArgs);

	// Print the message
	Print(szBuffer);

	// Unlock the mutex
	m_mutex.Unlock();
}