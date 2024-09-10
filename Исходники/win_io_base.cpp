bool win_io_base::is_file_exists(const TCHAR* p_name)
{
	assert(p_name);
	if (p_name != NULL && wcslen(p_name) > 0)
	{
		struct _stat32 stat_info;
		return _wstat32(p_name, &stat_info) == 0;
	}
	else
		return false;
}