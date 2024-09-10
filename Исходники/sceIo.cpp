void __IoInit()
{
	INFO_LOG(HLE, "Starting up I/O...");

#ifdef _WIN32

	char path_buffer[_MAX_PATH], drive[_MAX_DRIVE] ,dir[_MAX_DIR], file[_MAX_FNAME], ext[_MAX_EXT];
	char mypath[_MAX_PATH];

	GetModuleFileName(NULL,path_buffer,sizeof(path_buffer));

	char *winpos = strstr(path_buffer, "Windows");
	if (winpos)
		*winpos = 0;
	strcat(path_buffer, "dummy.txt");

	_splitpath_s(path_buffer, drive, dir, file, ext );

	// Mount a couple of filesystems
	sprintf(mypath, "%s%sMemStick\\", drive, dir);
#else
	// TODO
	char mypath[256] = "/mount/sdcard/memstick";
#endif

	DirectoryFileSystem *memstick;
	memstick = new DirectoryFileSystem(&pspFileSystem, mypath);

	pspFileSystem.Mount("ms0:",	memstick);
	pspFileSystem.Mount("fatms0:", memstick);
	pspFileSystem.Mount("fatms:", memstick);
	pspFileSystem.Mount("flash0:", new EmptyFileSystem());
	pspFileSystem.Mount("flash1:", new EmptyFileSystem());
}