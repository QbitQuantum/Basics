//去掉绝对路径中的文件名与扩展名，szPath需要分配空间
BOOL	GetFilePathA(const char* szFullPath, char* szPath)
{
	char szDrive[_MAX_DRIVE];
	char szDir[_MAX_DIR];
	_splitpath_s(szFullPath, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, NULL, NULL, NULL, NULL);
	_makepath_s(szPath, MAX_PATH, szDrive, szDir, NULL, NULL);
	return TRUE;
}