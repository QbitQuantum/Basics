GIT_INLINE(int) path__cwd(wchar_t *path, int size)
{
	int len;

	if ((len = GetCurrentDirectoryW(size, path)) == 0) {
		errno = GetLastError() == ERROR_ACCESS_DENIED ? EACCES : ENOENT;
		return -1;
	} else if (len > size) {
		errno = ENAMETOOLONG;
		return -1;
	}

	/* The Win32 APIs may return "\\?\" once you've used it first.
	 * But it may not.  What a gloriously predictible API!
	 */
	if (wcsncmp(path, PATH__NT_NAMESPACE, PATH__NT_NAMESPACE_LEN))
		return len;

	len -= PATH__NT_NAMESPACE_LEN;

	memmove(path, path + PATH__NT_NAMESPACE_LEN, sizeof(wchar_t) * len);
	return len;
}