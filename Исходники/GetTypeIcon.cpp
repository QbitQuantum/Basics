void CFilePro::GetAllNewItemsIconFile(vector<NewType *> &vAllItems,CString strDestDir)
{
	string strIconFile;
	int iIndex = 0;
	bool bIsIconFile = false;
	for (size_t i = 0; i< vAllItems.size();i++)
	{
		bool bok1 = GetExeDefaultIconPath(vAllItems[i]->m_strExt.c_str(),strIconFile,iIndex,bIsIconFile);
		CString strDirOutIcoFile = strDestDir + "\\";
		CString strEx = vAllItems[i]->m_strExt.c_str() +1;
		CString strNameNoExt = strDirOutIcoFile + strEx + "\\" + strEx;
		strDirOutIcoFile = strNameNoExt + ".ico";
		MakeSureDirectoryPathExists(strDirOutIcoFile);
		if (!bIsIconFile && !strIconFile.empty()) // exe or dll
		{
			// 保存ICON文件
			CExtract Extract(strIconFile.c_str());
			BOOL BOK = Extract.ExtractIcon(iIndex,strDirOutIcoFile);
			if (Extract.m_bUseDefaultIcon)
			{
				char szPath[1024] ={0};
				ExpandEnvironmentStrings("%SystemRoot%\\system32\\shell32.dll",szPath,1024);
				bool bOK2 = ExtractIndifySizeIcon(szPath,strNameNoExt,32,16,0);
				bool bOK3 = ExtractIndifySizeIcon(szPath,strNameNoExt,64,32,0);
				continue;
			}
		}
		else
		{
			if (bIsIconFile && !strIconFile.empty())
			{
				::CopyFile(strIconFile.c_str(),strDirOutIcoFile,FALSE);
			}
			else
			{
				GetTypeIconToFile(vAllItems[i]->m_strExt.c_str(),strDestDir,true);
				strIconFile = strDirOutIcoFile;
			}
		}

		//保存PNG文件
		bool bOK2 = ExtractIndifySizeIcon(strIconFile.c_str(),strNameNoExt,64,32,iIndex);
		bool bOK3 = ExtractIndifySizeIcon(strIconFile.c_str(),strNameNoExt,128,88,iIndex);
	}
}