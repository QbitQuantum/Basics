static int wfio_realpathw(wchar_t *relpath, size_t relpath_len TSRMLS_DC) {
	char *p;
	char workdir[MAXPATHLEN] = {0};
	wchar_t workdirw[MAX_PATH] = {0};
	wchar_t newpathw[MAX_PATH] = {0};

	if (relpath[0] == L'\\' || relpath[0] == L'/')
		return 0;

	p = VCWD_GETCWD(workdir, MAXPATHLEN);

	if (p != NULL) {
		MultiByteToWideChar(CP_ACP, 0, workdir, MAXPATHLEN, workdirw, MAX_PATH);
		PathCombineW(newpathw, workdirw, relpath);
		wcsncpy(relpath, newpathw, relpath_len);
		return 0;
	} else {
		return -1;
	}
}