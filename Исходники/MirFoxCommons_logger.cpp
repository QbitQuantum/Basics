void MFLogger::log_p(const wchar_t* szText, ...){
	va_list args;
	va_start(args, szText);
	int len = (PREFIX_SIZE + _vscwprintf(szText, args ) + 1); // _vscprintf doesn't count terminating '\0'
	wchar_t* buffer = new wchar_t[len * sizeof(wchar_t)];
	vswprintf_s(buffer + PREFIX_SIZE, len, szText, args);
	va_end(args);
	memcpy(buffer, m_prefix, PREFIX_SIZE * sizeof(m_prefix[0]));
	log_int(buffer);
	delete[] buffer;
}