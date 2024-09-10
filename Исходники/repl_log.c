int repl_log(FILE *fp, boolean_t stamptime, boolean_t flush, char *fmt, ...)
{
	va_list printargs;
	char	time_str[CTIME_BEFORE_NL + 2]; /* for GET_CUR_TIME macro */
	char	fmt_str[BUFSIZ];
	int	rc;

	assert(NULL != fp);
	if (stamptime)
	{
		GET_CUR_TIME(time_str);
		strcpy(fmt_str, time_str);
		fmt_str[CTIME_BEFORE_NL] = ' '; /* Overwrite \n */
		fmt_str[CTIME_BEFORE_NL + 1] = ':';
		fmt_str[CTIME_BEFORE_NL + 2] = ' ';
		strcpy(fmt_str + CTIME_BEFORE_NL + 3, fmt);
		fmt = &fmt_str[0];
	}

	va_start(printargs, fmt);
	VFPRINTF(fp, fmt, printargs, rc);
	assert(0 <= rc);
	va_end(printargs);

	if (flush)
		FFLUSH(fp);

	return(SS_NORMAL);
}