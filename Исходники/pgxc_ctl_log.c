void
elog_start(const char *file, const char *func, int line)
{
	fname = Strdup(file);
	funcname = Strdup(func);
	lineno = line;
}