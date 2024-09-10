static int _outputvws_safe(wchar_t* buf, int cnt, const wchar_t* fmt, va_list ap)
{
	int ret;

#if defined(_MSC_VER)
	if (NULL == buf || 0 == cnt)
		return _vscwprintf(fmt, ap);
	#if _MSC_VER >= 1500
	ret = _vsnwprintf_s(buf, cnt, _TRUNCATE, fmt, ap);
	#else
	ret = _vsnwprintf(buf, cnt, fmt, ap);
	#endif
#else
	ret = vsnwprintf(buf, cnt, fmt, ap);
#endif
	
	if (NULL != buf && cnt > 0){
		if (ret < 0)
			buf[cnt-1] = 0;
		else if (ret >= cnt)
			ret = -1;
	}

	return ret;
}