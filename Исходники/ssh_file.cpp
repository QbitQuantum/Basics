	void File::get_time(Time* create, Time* access, Time* write) const
	{
		struct _stat64 stat;
		if(_wstat64(path, &stat)) SSH_THROW(L"Не удалось получить время файла %s!", path);
		if(access) *access = stat.st_atime;
		if(create) *create = stat.st_ctime;
		if(write) *write = stat.st_mtime;
	}