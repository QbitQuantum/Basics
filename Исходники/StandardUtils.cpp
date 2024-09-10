	std::string FormatStr(const char *pszFormat, ...)
	{
		std::string   strRet;
		va_list       arg;
		int           cch;

		va_start(arg, pszFormat);

		// Check the required size
		cch = _vscprintf(pszFormat, arg);
		strRet.resize(cch);

		va_start(arg, pszFormat);
		_vsnprintf_s(&strRet[0], cch+1, cch, pszFormat, arg);

		va_end(arg);

		return strRet;
	}