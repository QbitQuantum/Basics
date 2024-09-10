// 删除目录及文件
BOOL CHistoryManagerXP::DeleteDir(CStringW dir)
{
	SHFILEOPSTRUCTW FileOp; 
	FileOp.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR; 
	FileOp.hNameMappings = NULL; 
	FileOp.hwnd = NULL; 
	FileOp.lpszProgressTitle = NULL; 
	FileOp.pFrom = dir; 
	FileOp.pTo = NULL; 
	FileOp.wFunc = FO_DELETE; 
	return SHFileOperationW(&FileOp) == 0;
}