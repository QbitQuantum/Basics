/* Implementation of :u filename modifier. */
static int
apply_u_mod(const char *path, char *buf, size_t buf_len)
{
	if(!is_unc_path(path))
	{
		DWORD size = buf_len - 2;
		snprintf(buf, buf_len, "//");
		GetComputerNameA(buf + 2, &size);
		return 0;
	}
	snprintf(buf, buf_len, "%s", path);
	break_at(buf + 2, '/');
	return 0;
}