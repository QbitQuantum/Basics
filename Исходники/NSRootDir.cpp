bool DirectoryFileSource::GetModifiedTime( const PathStringArg& Path, int32_t& Time ){

	auto fullpath = Path.CreatePath(RealPath);

#ifdef UNICODE 
	struct _stat32 FileInfo;

	int result = _wstat32(fullpath.c_str(), &FileInfo);
#else
	struct stat FileInfo;

	int result = stat(fullpath.c_str(), &FileInfo);
#endif

	if(result == 0){
		return false;
	}

	Time = FileInfo.st_mtime;

	return true;
}