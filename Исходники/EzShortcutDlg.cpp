void CEzShortcutDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szPathName[MAX_PATH];

	// 드롭된 파일의 갯수
	int nFiles=DragQueryFile(hDropInfo, 0xFFFFFFFF, szPathName, MAX_PATH);
	if( nFiles != 1)
	{
		AfxMessageBox(_T("This application is not support multi-file drag & drop"));
		return;
	}

	for(int index=0 ; index < nFiles ; index++)
	{
		DragQueryFile(hDropInfo, index, szPathName, MAX_PATH);     // 파일의 경로 얻어옴
		std::wstring strExt = light::get_file_ext(szPathName);

		if( strExt == _T("lnk" ))
		{
			IShellLink *link;
			IPersistFile *pfile;
			BSTR szLinkPath;
			CString szPrePath;
			TCHAR szBuffer[MAX_PATH];

			CString fname = szPathName;
			if(SUCCEEDED(CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&link))) 
			{
				link->QueryInterface(IID_IPersistFile, (void **)&pfile);
				szLinkPath = fname.AllocSysString();
				pfile->Load(szLinkPath, STGM_READ);
				SysFreeString(szLinkPath);
				link->Resolve(NULL, NULL);
				link->GetPath(szBuffer, MAX_PATH, NULL, 0);

				// 리스트 박스나 메세지 박스로 해당 경로 값을 불러온다. (szBuffer)
				_tcsncpy_s(szPathName , szBuffer, _TRUNCATE);
				pfile->Release();
				link->Release();
			}
		}
		
		SHORTCUT_INFO ShortcutInfo(GetSafeHwnd());
		ShortcutInfo.m_strShortcutName = light::get_file_name_without_ext(szPathName);
		ShortcutInfo.m_strProgramPath = szPathName;
		if( true == OnEditShortcutDlg(ShortcutInfo) )
		{
			AddShortCutInfo(ShortcutInfo);
			RebuildShortcutList();
			AutoSave();
		}
	}

	DragFinish(hDropInfo);

	CDialog::OnDropFiles(hDropInfo);
}