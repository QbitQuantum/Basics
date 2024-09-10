void CFilesHashDlg::OnDropFiles(HDROP hDropInfo)
{
	if(!m_thrdData.threadWorking)
	{
		unsigned int i;
		TCHAR szDragFilename[MAX_PATH];
		DragAcceptFiles(FALSE);

		m_thrdData.nFiles = DragQueryFile(hDropInfo, -1, NULL, 0);
		ClearFilePaths();

		for(i=0; i < m_thrdData.nFiles; i++)
		{
			DragQueryFile(hDropInfo, i, szDragFilename, sizeof(szDragFilename));
			CString tmp;
			tmp.Format(_T("%s"), szDragFilename);
			m_thrdData.fullPaths.push_back(tmp);
		}

		DragFinish(hDropInfo);
		DragAcceptFiles(TRUE);

		DoMD5();
	}
}