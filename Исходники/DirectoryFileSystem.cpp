PSPFileInfo DirectoryFileSystem::GetFileInfo(std::string filename) {
	PSPFileInfo x;
	x.name = filename;

	std::string fullName = GetLocalPath(filename);
	if (! File::Exists(fullName)) {
#if HOST_IS_CASE_SENSITIVE
		if (! FixPathCase(basePath,filename, FPC_FILE_MUST_EXIST))
			return x;
		fullName = GetLocalPath(filename);

		if (! File::Exists(fullName))
			return x;
#else
		return x;
#endif
	}
	x.type = File::IsDirectory(fullName) ? FILETYPE_DIRECTORY : FILETYPE_NORMAL;
	x.exists = true;

	if (x.type != FILETYPE_DIRECTORY)
	{
#ifdef _WIN32_NO_MINGW
		struct _stat64i32 s;
		_wstat64i32(ConvertUTF8ToWString(fullName).c_str(), &s);
#else
		struct stat s;
		stat(fullName.c_str(), &s);
#endif

		x.size = File::GetSize(fullName);
		x.access = s.st_mode & 0x1FF;
		localtime_r((time_t*)&s.st_atime,&x.atime);
		localtime_r((time_t*)&s.st_ctime,&x.ctime);
		localtime_r((time_t*)&s.st_mtime,&x.mtime);
	}

	return x;
}