int dir_empty(const char *path)
{
#ifdef _WIN32
	return PathIsDirectoryEmptyA(path);
#else
	struct dirent *dp;
	int empty = 1;

	DIR *dir = opendir(path);
	if (dir == NULL) //Not a directory or doesn't exist
		return 1;

	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;    /* Skip . and .. */

		empty = 0;
		break;
	}
	closedir(dir);
	return empty;
#endif
}