extern "C" DIR *opendir(const char *dir)
{
	DIR *dp;
	char *filespec;
	long handle;
	int index;

	filespec = (char *)malloc(strlen(dir) + 2 + 1);
	strcpy(filespec, dir);
	index = strlen(filespec) - 1;
	if (index >= 0 && (filespec[index] == '/' || 
	   (filespec[index] == '\\' && !IsDBCSLeadByte(filespec[index-1]))))
		filespec[index] = '\0';
	strcat(filespec, "/*");

	dp = (DIR *) malloc(sizeof(DIR));
	dp->offset = 0;
	dp->finished = 0;

	if ((handle = _findfirst(filespec, &(dp->fileinfo))) < 0) {
		if (errno == ENOENT) {
			dp->finished = 1;
		} else {
			free(dp);
			free(filespec);
			return NULL;
		}
	}
	dp->dir = strdup(dir);
	dp->handle = handle;
	free(filespec);

	return dp;
}