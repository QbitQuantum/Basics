int
__statfsx64 (const char *file, struct statfsx64 *buf)
{
	char *RootDirectory = rootdir (file);
	int res = 0;
	
	if ((RootDirectory == NULL) ) {// || access (file, F_OK)) { // || (GetDriveType(RootDirectory) == DRIVE_REMOVABLE)) {
//   	fprintf(stderr, "__statfsx64: RootDirectory: %s\n", RootDirectory);
		buf = NULL;
		_set_errno(ENOENT);
		res = -1;
	}
	else
		res = __rstatfsx64 ((const char *) RootDirectory, buf);
	free (RootDirectory);
	return res;
}