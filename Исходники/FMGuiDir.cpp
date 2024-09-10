FMGUI_Dir *
FMGUI_OpenDir(const char *path)
{
	FMGUI_Dir *dir;

	dir = (FMGUI_Dir *) Malloc(sizeof(FMGUI_Dir));
	dir->ents = NULL;
	dir->nents = 0;

#ifdef _WIN32
	{
		char dpath[FMGUI_PATHNAME_MAX];
		HANDLE h;
		WIN32_FIND_DATA fdata;
		DWORD rv;

		Strlcpy(dpath, path, sizeof(dpath));
		Strlcat(dpath, "\\*", sizeof(dpath));
		if ((h = FindFirstFile(dpath, &fdata))==INVALID_HANDLE_VALUE) {
			ReportError1("Invalid file handle (%d)",
			    (int)GetLastError());
			goto fail;
		}
		while (FindNextFile(h, &fdata) != 0) {
			dir->ents = Realloc(dir->ents,
			    (dir->nents+1)*sizeof(char *));
			dir->ents[dir->nents++] = Strdup(fdata.cFileName);
		}
		rv = GetLastError();
		FindClose(h);
		if (rv != ERROR_NO_MORE_FILES) {
			ReportError1("FindNextFileError (%lu)", rv);
			goto fail;
		}
	}
#else /* !_WIN32 */
	{
		DIR *dp;
		struct dirent *dent;
		
		if ((dp = opendir(path)) == NULL) {
			ReportError2("%s: Failed to open directory (%s)",
			    path, strerror(errno));
			goto fail;
		}
		while ((dent = readdir(dp)) != NULL) {
			dir->ents = (char **) Realloc(dir->ents,
			    (dir->nents+1)*sizeof(char *));
			dir->ents[dir->nents++] = strdup(dent->d_name);
		}
		closedir(dp);
	}
#endif /* _WIN32 */

	return (dir);
fail:
	Free(dir);
	return (NULL);
}