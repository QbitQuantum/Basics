bool InsertDateW(wchar_t* def, wchar_t* pBuf, size_t& index, size_t& filelength, size_t maxlength, __time64_t ttime)
{
	// Search for first occurrence of def in the buffer, starting at index.
	if (!FindPlaceholderW(def, pBuf, index, filelength))
	{
		// No more matches found.
		return false;
	}
	// Format the text to insert at the placeholder
	if (ttime == USE_TIME_NOW)
		_time64(&ttime);

	struct tm newtime;
	if (wcsstr(def, L"UTC"))
	{
		if (_gmtime64_s(&newtime, &ttime))
			return false;
	}
	else
	{
		if (_localtime64_s(&newtime, &ttime))
			return false;
	}
	wchar_t destbuf[1024];
	wchar_t* pBuild = pBuf + index;
	ptrdiff_t Expansion;
	if ((wcscmp(def,TEXT(DATEWFMTDEF)) == 0) || (wcscmp(def,TEXT(NOWWFMTDEF)) == 0) ||
		(wcscmp(def,TEXT(DATEWFMTDEFUTC)) == 0) || (wcscmp(def,TEXT(NOWWFMTDEFUTC)) == 0))
	{
		// Format the date/time according to the supplied strftime format string
		wchar_t format[1024] = { 0 };
		wchar_t* pStart = pBuf + index + wcslen(def);
		wchar_t* pEnd = pStart;

		while (*pEnd != '$')
		{
			++pEnd;
			if (((__int64)(pEnd - pBuf))*((__int64)sizeof(wchar_t)) >= (__int64)filelength)
				return false; // No terminator - malformed so give up.
		}
		if ((pEnd - pStart) > 1024)
			return false; // Format specifier too big
		memcpy(format, pStart, (pEnd - pStart) * sizeof(wchar_t));

		// to avoid wcsftime aborting if the user specified an invalid time format,
		// we set a custom invalid parameter handler that does nothing at all:
		// that makes wcsftime do nothing and set errno to EINVAL.
		// we restore the invalid parameter handler right after
		_invalid_parameter_handler oldHandler = _set_invalid_parameter_handler(_invalid_parameter_donothing);

		if (wcsftime(destbuf,1024,format,&newtime) == 0)
		{
			if (errno == EINVAL)
				wcscpy_s(destbuf, L"Invalid Time Format Specified");
		}
		_set_invalid_parameter_handler(oldHandler);

		Expansion = wcslen(destbuf) - (wcslen(def) + pEnd - pStart + 1);
	}
	else
	{
		// Format the date/time in international format as yyyy/mm/dd hh:mm:ss
		swprintf_s(destbuf, L"%04d/%02d/%02d %02d:%02d:%02d", newtime.tm_year + 1900, newtime.tm_mon + 1, newtime.tm_mday, newtime.tm_hour, newtime.tm_min, newtime.tm_sec);
		Expansion = wcslen(destbuf) - wcslen(def);
	}
	// Replace the def string with the actual commit date
	if (Expansion < 0)
		memmove(pBuild, pBuild - Expansion, (filelength - ((pBuild - Expansion) - pBuf) * sizeof(wchar_t)));
	else if (Expansion > 0)
	{
		// Check for buffer overflow
		if (maxlength < Expansion * sizeof(wchar_t) + filelength)
			return false;
		memmove(pBuild + Expansion, pBuild, (filelength - (pBuild - pBuf) * sizeof(wchar_t)));
	}
	memmove(pBuild, destbuf, wcslen(destbuf) * sizeof(wchar_t));
	filelength += Expansion * sizeof(wchar_t);
	return true;
}