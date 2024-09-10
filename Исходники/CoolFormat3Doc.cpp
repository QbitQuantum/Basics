BOOL CCoolFormat3Doc::DoSave( LPCTSTR lpszPathName, BOOL bReplace /*= TRUE*/ )
{
	if ( lpszPathName == NULL )  
	{ 
		TCHAR szPath[MAX_PATH]; 
		CString strDefault = GetTitle();
		strDefault.Remove('*');
		strDefault = strDefault.Trim();

		CString strFilter = _T("All Files(*.*)|*.*|")
			_T("C/C++ Files(*.c;*.cpp;*.h;*.hpp)|*.c;*.cpp;*.h;*.hpp|")
			_T("C# Files(*.cs)|*.cs|")
			_T("Java Files(*.java)|*.java||");
		g_GlobalUtils.m_sLanguageExt.GetAllLanguageFilter(strFilter);
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXTENSIONDIFFERENT;     
		CFileDialog dlg(FALSE, NULL, strDefault, dwFlags, strFilter, NULL);         
		if ( dlg.DoModal() == IDOK ) 
		{ 
			CString strTemp = dlg.GetPathName();
			if (dlg.m_ofn.nFilterIndex < MAX_SYN_LANG + 1 && dlg.m_ofn.nFilterIndex > 1)
			{
				CString strExt;
				g_GlobalUtils.m_sLanguageExt.GetLanguageOneFilter(dlg.m_ofn.nFilterIndex - 2, strExt);
				strTemp.Append(strExt);
			}		                                    
			lstrcpy(szPath, strTemp.GetBuffer(0)); 
			lpszPathName = szPath;                 
		} 
		else  
			return FALSE; 
	} 
	return  CDocument::DoSave(lpszPathName, bReplace); 
}