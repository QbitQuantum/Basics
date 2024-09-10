/* This appends timestamp from file (fn) last modified status time. Result is returned in same string fn.
 * Return SS_NORMAL for success */
uint4 append_time_stamp(char *fn, int fn_len, int *app_len, uint4 *ustatus)
{
	struct stat	stat_buf;
	struct tm	*tm_struct;
	int		status;
	size_t          tt;

	*ustatus = SS_NORMAL;
	STAT_FILE(fn, &stat_buf, status);
	if (-1 == status) /* if file fn does not exist */
		return errno;
	assert(0 <  MAX_FN_LEN - fn_len - 1);
	tm_struct = localtime(&(stat_buf.st_ctime));
	STRFTIME(&fn[fn_len], MAX_FN_LEN - fn_len - 1, TIME_EXT_FMT, tm_struct, tt);
	*app_len = (int)tt;
	return SS_NORMAL;
}