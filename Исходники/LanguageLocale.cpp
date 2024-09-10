bool CLanguageLocale::SetLanguage(int nID)
{
	bool bFound = false;
	if(m_nDataSource == LOADSTRING_FROM_RC)
	{
		switch (nID)
		{
		/*case LANGUAGE_CHS:
			bFound = SetThreadLocale(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_SIMPLIFIED))==TRUE;
			break;*/
		case LANGUAGE_PERSONAL:
			bFound = SetThreadLocale(MAKELANGID(LANG_CHINESE,SUBLANG_CHINESE_TRADITIONAL))==TRUE;
			break;
		case LANGUAGE_ENGLISH:
			bFound = SetThreadLocale(MAKELANGID(LANG_ENGLISH,SUBLANG_DEFAULT))==TRUE;
			break;
		}
	}
	else
	{
		CFileFind find;
		BOOL bRet = find.FindFile(m_strPath + "\\*.ini");
		bool bFound = false;
		int nLanguage = 0;
		gStrFileName.Empty();
		
		while(bRet)
		{
			bRet = find.FindNextFile();
			if(find.IsDots() || find.IsDirectory()) continue;
			
			CString szFilePath = find.GetFilePath();
			nLanguage = GetPrivateProfileInt(_T("Setting"),_T("Language"),-1,szFilePath);		
			if(nLanguage == nID)
			{
				gStrFileName = szFilePath;
				bFound = true;
				break;
			}		
		}
		find.Close();

	}
	return bFound;
}