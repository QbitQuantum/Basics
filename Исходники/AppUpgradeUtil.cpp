BOOL AppUpgradeUtil::ObsoleteFile( LPCTSTR target, LPCTSTR log_file )
{
	TCHAR file_name[MAX_PATH + 1];
	StrCpy(file_name, target);
	::PathRemoveFileSpec(file_name);
	GetTempFileName(file_name, TEXT("~tmp"), 0, file_name);
	::DeleteFile(file_name);
	BOOL bRet = ::MoveFile(target, file_name);
	if(bRet)
	{
		WriteLog4ObsoleteFile(target, file_name, log_file);
	}
	return bRet;
}