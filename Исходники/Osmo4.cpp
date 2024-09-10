static void osmo4_do_log(void *cbk, u32 level, u32 tool, const char *fmt, va_list list)
{
	FILE *logs = (FILE *) cbk;
    vfprintf(logs, fmt, list);
	fflush(logs);
}