BOOL CAddCopyrightInfoDlg::MyFindFile(TCHAR* path, char* copyright)
{
	WIN32_FIND_DATA findFileData;
	TCHAR szFind[MAX_PATH] = {0};
	TCHAR szFindTemp[MAX_PATH] = {0};

	wcsncpy_s(szFind,path,wcslen(path));
    wcsncat_s(szFind,L"\\*.*",4);
	HANDLE h = FindFirstFile(szFind, &findFileData);
	if(INVALID_HANDLE_VALUE==h)
	{
		MessageBox(_T("请检查路径是否正确"));
		return FALSE;
	}
	while(true)
	{
		if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(findFileData.cFileName[0]!='.')
			{
				wcsncpy_s(szFindTemp,path,wcslen(path));
				wcsncat_s(szFindTemp,L"\\",1);
				wcsncat_s(szFindTemp,findFileData.cFileName,sizeof(findFileData.cFileName));
				MyFindFile(szFindTemp, copyright);
			}
		}
		else
		{
			TCHAR exName[_MAX_EXT];
			_wsplitpath(findFileData.cFileName, NULL, NULL, NULL, exName); 
			if(wcscmp(exName,_T(".cs"))==0)//只有是.cs文件的才写
			{	
				TCHAR filePath[MAX_PATH];
				wcsncpy_s(filePath,path,wcslen(path));
				wcsncat_s(filePath,L"\\",1);
				wcsncat_s(filePath,findFileData.cFileName,sizeof(findFileData.cFileName));

				TCHAR fileName[MAX_PATH];
				wcsncpy_s(fileName, filePath, wcslen(filePath)-3);//去除.cs
				wcsncat_s(fileName,L".bak",4);
				CopyFile(filePath,fileName,TRUE);//备份文件
				
				WriteCopyright(filePath, fileName, copyright);//写版权信息
			}
		}
		if(!FindNextFile(h,&findFileData))    
			break;
	}
	FindClose(h);
	return TRUE;
}