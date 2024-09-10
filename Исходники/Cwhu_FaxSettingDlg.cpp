bool Cwhu_FaxSettingDlg::whu_findfile(CString m_file,CString folder)
{
	folder = folder + _T("\\*.*");
	CFileFind filefind;
	bool bworking = filefind.FindFile(folder);
	bool find = false;
	while(bworking)
	{
		bworking = filefind.FindNextFileA();
		CString m_curfile = filefind.GetFilePath();
		if (m_curfile == m_file)
		{
			find =true;
		}
	}
	return find;
}