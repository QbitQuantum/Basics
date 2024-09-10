CString CUserFile::GetModifyTime(CString appname)
{   
	WIN32_FIND_DATA ffd ;   
	HANDLE hFind = FindFirstFile(appname,&ffd);   
	SYSTEMTIME stUTC, stLocal;   
	FileTimeToSystemTime(&(ffd.ftLastWriteTime), &stUTC);   
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);   
	CString strTmp = "";   
	strTmp.Format("%d-%d-%d,%d:%d", stLocal.wYear,stLocal.wMonth,stLocal.wDay,stLocal.wHour,stLocal.wMinute);   
	return strTmp;   
}