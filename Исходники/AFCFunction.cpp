//下载函数
int InternetGetFile(TCHAR szUrl[], TCHAR szFileName[],CString &filename)
{
	CString title;
	CString name;//源文件名
	CString destname;//目标文件名
	CString Fullpath;//目标全路径
	CString path;	//目标全路径不包括文件名
	//	TCHAR szMsg[1000];
	//	DWORD err;
	//获取源文件名
	name=szUrl;
	int cur=name.ReverseFind('/');
	name=name.Mid(cur+1,name.GetLength()-1-cur);
	TCHAR g_CurDir[MAX_PATH+1];
	
    // PengJiLin, 2010-6-7, GetCurrentDirectory()函数全部替代
    //::GetCurrentDirectory(MAX_PATH,g_CurDir);
    lstrcpy(g_CurDir, CBcfFile::GetAppPath());

	if(szFileName)
	{//如果指定了目录文件名,则用目录文件名
		destname=szFileName;
		if(destname.GetAt(0)=='\\')
			destname=destname.Mid(1,destname.GetLength()-1);
		//组成全路径名
		Fullpath.Format(TEXT("%s\\%s"),g_CurDir,destname);
	}
	else
	{//没有指定则用源文件名
		TCHAR tempath[MAX_PATH+1];
		DWORD len=GetTempPath(MAX_PATH,tempath);
		if(len == 0 || len > MAX_PATH)
		{
			return -1;
		}
		if(len<=MAX_PATH)
		{
			tempath[len*sizeof(TCHAR)+1]='\0';
		}
		TCHAR tempname[MAX_PATH+1];
		if(!::GetTempFileName(tempath,TEXT("bzw"),0,tempname))
		{
			return -1;
		}
		Fullpath=tempname;
	}
	//获取目标全路径不包括文件名
	path=Fullpath;
	cur=path.ReverseFind('\\');
	destname=path;
	path=destname.Mid(cur+1,destname.GetLength()-1-cur);
	destname=Fullpath;
	if(filename)
		filename=destname;

	DWORD dwFlags;
	InternetGetConnectedState(&dwFlags, 0);
	TCHAR strAgent[64];
	memset(strAgent,0,sizeof(strAgent));
	wsprintf(strAgent, TEXT("Agent%ld"), timeGetTime());
	HINTERNET hOpen;
	if(!(dwFlags & INTERNET_CONNECTION_PROXY))
		hOpen = InternetOpen(strAgent, INTERNET_OPEN_TYPE_PRECONFIG_WITH_NO_AUTOPROXY, NULL, NULL, 0);
	else
		hOpen = InternetOpen(strAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(!hOpen)
	{//显示错误信息
		return -1;
	}

	DWORD dwSize;
	TCHAR   szHead[] = TEXT("Accept: */*\r\n\r\n");
	VOID* szTemp[16384];
	HINTERNET  hConnect;
	CFile file;

	if ( !(hConnect = InternetOpenUrl( hOpen, szUrl, szHead,
		lstrlen(szHead), INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0)))
	{//显示错误信息
		InternetCloseHandle(hOpen);
		return -1;
	}
	bool CreateDir=false;
retry:
	if(file.Open(destname.GetBuffer(),CFile::modeWrite|CFile::modeCreate)==FALSE)
	{//显示错误信息
		int err=GetLastError();
		if(!CreateDir)
		{//创建目录,然后重试
			::CreateDirectory(path.GetBuffer(),NULL);
			CreateDir = true;
			goto retry;
		}
		return -1;
	} 

	DWORD dwByteToRead = 0;
	DWORD dwSizeOfRq = 4;
	DWORD dwBytes = 0;

	if (!HttpQueryInfo(hConnect, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, 
		(LPVOID)&dwByteToRead, &dwSizeOfRq, NULL))
	{
		dwByteToRead = 0;
	}
	memset(szTemp,0,sizeof(szTemp));
	do
	{
		if(false)
		{
			file.Close();
			file.Remove(destname.GetBuffer());
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hOpen);
			return -1;
		}
		if (!InternetReadFile (hConnect, szTemp, 16384,  &dwSize))
		{//显示错误信息
			file.Close();
			file.Remove(destname.GetBuffer());
			InternetCloseHandle(hConnect);
			InternetCloseHandle(hOpen);
			return -1;
		}
		if (dwSize==0)
			break;
		else
		{
			file.Write(szTemp,dwSize);
		}
	}while (TRUE);
	file.Close();
	InternetCloseHandle(hConnect);
	InternetCloseHandle(hOpen);
	return 0;
}