	bool WinIO::is_file_exists(const char* p_name)
	{
		assert(p_name);
		if (p_name != NULL && strlen(p_name) > 0)
		{
			struct _stat32 stat_info;
			return _stat32(p_name, &stat_info) == 0;
		}
		else
			return false;
	}