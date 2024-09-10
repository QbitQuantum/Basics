int win32_find_system_file_using_path(git_buf *path, const char *filename)
{
	wchar_t * env = NULL;
	struct win32_path root;

	env = _wgetenv(L"PATH");
	if (!env)
		return -1;

	// search in all paths defined in PATH
	while ((env = win32_nextpath(env, root.path, MAX_PATH - 1)) != NULL && *root.path)
	{
		wchar_t * pfin = root.path + wcslen(root.path) - 1; // last char of the current path entry

		// ensure trailing slash
		if (*pfin != L'/' && *pfin != L'\\')
			wcscpy(++pfin, L"\\"); // we have enough space left, MAX_PATH - 1 is used in nextpath above

		root.len = (DWORD)wcslen(root.path) + 1;

		if (win32_find_file(path, &root, "git.cmd") == 0 || win32_find_file(path, &root, "git.exe") == 0) {
			// we found the cmd or bin directory of a git installaton
			if (root.len > 5) {
				wcscpy(root.path + wcslen(root.path) - 4, L"etc\\");
				if (win32_find_file(path, &root, filename) == 0)
					return 0;
			}
		}
	}
	
	return GIT_ENOTFOUND;
}