int
hssystemfileio_copy_permissions(const wchar_t *old_path, const wchar_t *new_path)
{
	struct __stat64 st;
	int rc = _wstat64(old_path, &st);
	if (rc == -1)
	{ return rc; }
	
	return _wchmod(new_path, st.st_mode);
}