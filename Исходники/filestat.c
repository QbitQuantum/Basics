static int php_disk_total_space(char *path, double *space) /* {{{ */
#if defined(WINDOWS) /* {{{ */
{
	ULARGE_INTEGER FreeBytesAvailableToCaller;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;
	PHP_WIN32_IOUTIL_INIT_W(path)

	if (GetDiskFreeSpaceExW(pathw, &FreeBytesAvailableToCaller, &TotalNumberOfBytes, &TotalNumberOfFreeBytes) == 0) {
		php_error_docref(NULL, E_WARNING, "%s", php_win_err());
		PHP_WIN32_IOUTIL_CLEANUP_W()
		return FAILURE;
	}