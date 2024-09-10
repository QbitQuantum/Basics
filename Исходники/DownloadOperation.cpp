/**
*           bIndex == 1     遍历指定文件夹并解压缩
*           数据升级Config因为包括黑白名单缓存，需特殊处理
*/
void CDownloadOperation::uncompressTraverse(IN LPWSTR path ,IN BYTE bIndex, IN OUT LPWSTR parentDirectory )
{
	USES_CONVERSION;
	WIN32_FIND_DATAW  fw;
	HANDLE hFind= FindFirstFileW(path,&fw);

	if(hFind == INVALID_HANDLE_VALUE)
		return ;

	WBRETURN bIsWBCab = NONE;

	do
	{
		if(wcscmp(fw.cFileName,L".") == 0 || wcscmp(fw.cFileName,L"..") == 0 || wcscmp(fw.cFileName,L".svn") == 0)
			continue;

		if(fw.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(bIndex == 1)
			{	

			}
		}
		else
		{
			if(bIndex == 1 && strstr(W2A(fw.cFileName),"cab") != NULL)
			{
				std::wstring newFile ;
				bool bIsSC = isSpecialCab(fw.cFileName);

				newFile = this->getAppDataPath();

				if( !bIsSC )
					newFile += BANKINFOPATHNOFIND;

				WBRETURN bWBCab = IsNewTBCacheFile(fw.cFileName);
				if( bWBCab != NONE)
					if( bWBCab != bIsWBCab && bIsWBCab != ALL )
					{
						if( bIsWBCab == NONE)
							bIsWBCab = bWBCab;
						else
							bIsWBCab = ALL;
					}
				

				std::wstring existingFile ;
				existingFile = getBankCachePath();
				existingFile += fw.cFileName;

				//没有通过验证的升级包不允许升级
				if( _UpdateMgr.isSafeFile((wchar_t *)existingFile.c_str() ) )
				{				
					moveFiles(fw.cFileName, true);	

					CCabExtract tt;
					if(tt.ExtractFile(existingFile.c_str(), newFile.c_str() ) )
						OutputDebugStringW(L"extractFile is OK!");
					else
					{
						moveFiles(fw.cFileName, false);
					}
				}
			}
		}
	}
	while( FindNextFile(hFind,&fw) );  

	this->UpdateWBFile(bIsWBCab);
	FindClose(hFind);
}