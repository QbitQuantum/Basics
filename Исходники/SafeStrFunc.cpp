	int shared_snprintf(wchar_t* pszwDst, uint32 uDstLength, const wchar_t* pszwFormat, ...)
	{
		va_list args;
		va_start(args, pszwFormat);
		int nRet = _vsnwprintf_s(pszwDst, _TRUNCATE, uDstLength-1, pszwFormat, args);
		va_end(args);

		return nRet;
	}