static long
#else
static long long
#endif
get_inode(struct dirent *entry, const char *dirname)
{
#ifdef __MINGW32__
	char fname[PATH_MAX];
	HANDLE fh;
	BY_HANDLE_FILE_INFORMATION info;

	sprintf(fname, "%s\\%s", dirname, entry->d_name);
	fh = CreateFile(fname, 0, 0, NULL, OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS, NULL);
	if (fh == INVALID_HANDLE_VALUE)
		return 0;
	if (GetFileInformationByHandle(fh, &info)) {
		long long inode = info.nFileIndexHigh;

		inode <<= 32;
		inode += info.nFileIndexLow;
		return inode;
	}
	return 0;
#else
	(void) dirname;		/* silence warnings */
	return entry->d_ino;
#endif
}