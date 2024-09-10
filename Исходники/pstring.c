P_LIB_API pchar *
p_strtok (pchar *str, const pchar *delim, pchar **buf)
{
	if (P_UNLIKELY (delim == NULL))
		return str;

#ifdef P_OS_WIN
#  ifdef P_CC_MSVC
	if (P_UNLIKELY (buf == NULL))
		return str;
#    if _MSC_VER < 1400
	P_UNUSED (buf);
	return strtok (str, delim);
#    else
	return strtok_s (str, delim, buf);
#    endif
#  else
	P_UNUSED (buf);
	return strtok (str, delim);
#  endif
#else
	if (P_UNLIKELY (buf == NULL))
		return str;

	return strtok_r (str, delim, buf);
#endif
}