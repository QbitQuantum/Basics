static void on_logs(void *cbk, u32 ll, u32 lm, const char *fmt, va_list list)
{
	FILE *logs = cbk;
	vfprintf(logs, fmt, list);
	fflush(logs);
}