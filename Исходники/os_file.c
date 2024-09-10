GF_Err gf_rmdir(const char *DirPathName)
{
#if defined (_WIN32_WCE)
	TCHAR swzName[MAX_PATH];
	BOOL res;
	CE_CharToWide(DirPathName, swzName);
	res = RemoveDirectory(swzName);
	if (! res) {
		int err = GetLastError();
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot delete directory %s: last error %d\n", DirPathName, err ));
	}
#elif defined (WIN32)
	int res;
	wchar_t* wcsDirPathName = utf8_to_wcs(DirPathName);
	if (!wcsDirPathName)
		return GF_IO_ERR;
	res = _wrmdir(wcsDirPathName);
	gf_free(wcsDirPathName);
	if (res == -1) {
		int err = GetLastError();
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot delete directory %s: last error %d\n", DirPathName, err ));
		return GF_IO_ERR;
	}
#else
	int res = rmdir(DirPathName);
	if (res==-1) {
		GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("Cannot delete directory %s: last error %d\n", DirPathName, errno  ));
		return GF_IO_ERR;
	}
#endif
	return GF_OK;
}