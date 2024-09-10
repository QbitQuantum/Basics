bool CZipArchive::DirectoryExists(LPCTSTR lpszDir)
{
	TCHAR curPath[512];   /* Get the current working directory: */
	if (!_wgetcwd(curPath, 512))
		return false;
	if (_wchdir(lpszDir))	// retruns 0 if error
		return false;
	_wchdir(curPath);
	return true;
}