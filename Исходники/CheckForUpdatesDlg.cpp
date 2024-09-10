bool CCheckForUpdatesDlg::Download(CString filename)
{
	CString destFilename = GetDownloadsDirectory() + filename;
	if (PathFileExists(destFilename))
	{
		if (VerifySignature(destFilename))
			return true;
		else
			DeleteFile(destFilename);
	}

	CBSCallbackImpl bsc(this->GetSafeHwnd(), m_eventStop);

	CString url = m_sFilesURL + filename;

	m_progress.SetRange32(0, 1);
	m_progress.SetPos(0);
	m_progress.ShowWindow(SW_SHOW);

	CString tempfile = CTempFiles::Instance().GetTempFilePath(true).GetWinPathString();
	HRESULT res = URLDownloadToFile(NULL, url, tempfile, 0, &bsc);
	if (res == S_OK)
	{
		if (VerifySignature(tempfile))
		{
			if (PathFileExists(destFilename))
				DeleteFile(destFilename);
			MoveFile(tempfile, destFilename);
			return true;
		}
	}
	return false;
}