int core_vfprintf(core_file *f, const char *fmt, va_list va)
{
	char buf[1024];
	vsnprintf(buf, sizeof(buf), fmt, va);
	return core_fputs(f, buf);
}