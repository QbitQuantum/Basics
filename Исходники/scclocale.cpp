double ScCLocale::strtod ( const char * str, char ** endptr )
{
	if(NULL == that()->cLocale)
	{
		// a sade workaround
		double result(0.0);
		setlocale(LC_NUMERIC, "C");
		result = std::strtod(str, endptr);
		setlocale(LC_NUMERIC, "");
		return result;
	}
	else
	{
#if defined(Q_WS_WIN)
		return _strtod_l(str, endptr, that()->cLocale);
#else
  #if defined(Q_OS_SOLARIS) or defined (Q_OS_OPENBSD) or defined (Q_OS_FREEBSD)
		char *oldlocale=setlocale(LC_NUMERIC, NULL);
		double result(0.0);
		setlocale(LC_NUMERIC, "C");
		result = std::strtod(str, endptr);
		setlocale(LC_NUMERIC, oldlocale);
		return result;
  #else
		return strtod_l(str, endptr, that()->cLocale);
  #endif
#endif
	}
}