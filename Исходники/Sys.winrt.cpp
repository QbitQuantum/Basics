/**
	sys_stat : string -> {
		gid => int,
		uid => int,
		atime => 'int32,
		mtime => 'int32,
		ctime => 'int32,
		dev => int,
		ino => int,
		nlink => int,
		rdev => int,
		mode => int,
		size => int
	}
	<doc>Run the [stat] command on the given file or directory.</doc>
**/
static value sys_stat( value path ) {
	#if defined(EPPC) || defined(KORE_CONSOLE)
	return alloc_null();
	#else
	value o;
	val_check(path,string);
	
	#if defined(NEKO_WINDOWS) && !defined(KORE_WINDOWSAPP) && !defined(KORE_XBOX_ONE)
	const wchar_t* _path = val_wstring(path);
	gc_enter_blocking();
	WIN32_FILE_ATTRIBUTE_DATA data;
	if( !GetFileAttributesExW(_path,GetFileExInfoStandard,&data) )
	{
		gc_exit_blocking();
		return alloc_null();
	}
	gc_exit_blocking();
	wchar_t fullPath[MAX_PATH+1];
	GetFullPathNameW(_path,MAX_PATH+1,fullPath,NULL);
	int dev = PathGetDriveNumberW(fullPath);
	#define EPOCH_DIFF	(134774*24*60*60.0)
	ULARGE_INTEGER ui;
	o = alloc_empty_object( );
	alloc_field(o,val_id("gid"),alloc_int(0));
	alloc_field(o,val_id("uid"),alloc_int(0));
	ui.LowPart = data.ftLastAccessTime.dwLowDateTime;
	ui.HighPart = data.ftLastAccessTime.dwHighDateTime;
	alloc_field(o,val_id("atime"),alloc_int32((int)(((double)ui.QuadPart) / 10000000.0 - EPOCH_DIFF)));
	ui.LowPart = data.ftLastWriteTime.dwLowDateTime;
	ui.HighPart = data.ftLastWriteTime.dwHighDateTime;
	alloc_field(o,val_id("mtime"),alloc_int32((int)(((double)ui.QuadPart) / 10000000.0 - EPOCH_DIFF)));
	ui.LowPart = data.ftCreationTime.dwLowDateTime;
	ui.HighPart = data.ftCreationTime.dwHighDateTime;
	alloc_field(o,val_id("ctime"),alloc_int32((int)(((double)ui.QuadPart) / 10000000.0 - EPOCH_DIFF)));
	alloc_field(o,val_id("dev"),alloc_int(dev));
	alloc_field(o,val_id("ino"),alloc_int(0));
	int mode = 0;
	if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) mode |= _S_IFDIR;
	if ((data.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE) == 0) mode |= _S_IFREG;
	mode |= _S_IREAD;
	if ((data.dwFileAttributes & FILE_ATTRIBUTE_READONLY) == 0) mode |= _S_IWRITE;
	if ((data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) mode |= _S_IEXEC;
	alloc_field(o,val_id("mode"),alloc_int(mode));
	alloc_field(o,val_id("nlink"),alloc_int(1));
	alloc_field(o,val_id("rdev"),alloc_int(dev));
	alloc_field(o,val_id("size"),alloc_int32(data.nFileSizeLow));
	#else
	gc_enter_blocking();
	struct stat s;
	if( stat(val_string(path),&s) != 0 )
	{
		gc_exit_blocking();
		return alloc_null();
	}
	gc_exit_blocking();
	o = alloc_empty_object( );
	STATF(gid);
	STATF(uid);
	STATF32(atime);
	STATF32(mtime);
	STATF32(ctime);
	STATF(dev);
	STATF(ino);
	STATF(mode);
	STATF(nlink);
	STATF(rdev);
	STATF(size);
	#endif
	return o;
	#endif
}