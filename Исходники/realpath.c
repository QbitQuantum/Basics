char *realpathWin32(const char *path, char resolved[PATH_MAX])
{
	char realpath[PATH_MAX];

	strlcpy(resolved, path + 1, sizeof(realpath));
	backslashconvert(resolved);
	PathCanonicalizeA(realpath, resolved);
	slashconvert(realpath);

	/*
	* Store terminating slash in 'X:/' on Windows.
	*/

	if (realpath[1] == ':' && realpath[2] == 0)
	{
		realpath[2] = '/';
		realpath[3] = 0;
	}

	resolved[0] = *path; // will be our first slash in /x:/users/test1 format
	strncpy(resolved + 1, realpath, sizeof(realpath));
	return resolved;
}