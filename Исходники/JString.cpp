	////////////////////// func. /////////////////////
	void JString::Format(const char* format, ...)
	{
		va_list vlist;

		char* pTempBuf = new char[JSTRING_BUFFER_MAX + 1];
		pTempBuf[0] = NULL;

		va_start(vlist, format);
		vsnprintf_s(pTempBuf, JSTRING_BUFFER_MAX + 1, JSTRING_BUFFER_MAX, format, vlist);
		va_end(vlist);

		Release();
		Init(strlen(pTempBuf));

		strncpy_s(pBuffer, nLength + 1, pTempBuf, nLength);
		delete[] pTempBuf;
	}