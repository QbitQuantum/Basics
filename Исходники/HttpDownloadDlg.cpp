BOOL CHttpDownloadDlg::OnInitDialog() 
{
	CString cap;
	cap = GetResString(IDS_CANCEL);
	GetDlgItem(IDCANCEL)->SetWindowText(cap);

	if (!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle);

	//Let the parent class do its thing
	CDialog::OnInitDialog();
	InitWindowStyles(this);

	//Setup the animation control
	m_ctrlAnimate.Open(IDR_HTTPDOWNLOAD_ANI);

	//Validate the URL
	ASSERT(m_sURLToDownload.GetLength()); //Did you forget to specify the file to download
	if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort))
	{
		//Try sticking "http://" before it
		m_sURLToDownload = _T("http://") + m_sURLToDownload;
		if (!AfxParseURL(m_sURLToDownload, m_dwServiceType, m_sServer, m_sObject, m_nPort))
		{
			TRACE(_T("Failed to parse the URL: %s\n"), m_sURLToDownload);
			EndDialog(IDCANCEL);
			return TRUE;
		}
	}

	//Check to see if the file we are downloading to exists and if
	//it does, then ask the user if they were it overwritten
	// edited: we always want to overwrite old language dlls and server.mets
	/*CFileStatus fs;
	ASSERT(m_sFileToDownloadInto.GetLength());
	if (CFile::GetStatus(m_sFileToDownloadInto, fs))
	{
		CString sMsg;
		sMsg.Format(GetResString(IDS_HTTPDOWNLOAD_OK_TO_OVERWRITE), m_sFileToDownloadInto);
		if (AfxMessageBox(sMsg, MB_YESNO) != IDYES)
		{
			TRACE(_T("Failed to confirm file overwrite, download aborted\n"));
			EndDialog(IDCANCEL);
			return TRUE;
		}
	}*/

	//Try and open the file we will download into
	if (!m_FileToWrite.Open(m_sFileToDownloadInto, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite))
	{
		TRACE(_T("Failed to open the file to download into, Error:%d\n"), GetLastError());
		CString sError;
		sError.Format(_T("%d"), ::GetLastError());
		CString sMsg;
		sMsg.Format(GetResString(IDS_HTTPDOWNLOAD_FAIL_FILE_OPEN), sError);
		AfxMessageBox(sMsg);
		EndDialog(IDCANCEL);
		return TRUE;
	}

	//Pull out just the filename component
	int nSlash = m_sObject.ReverseFind(_T('/'));
	if (nSlash == -1)
		nSlash = m_sObject.ReverseFind(_T('\\'));
	if (nSlash != -1 && m_sObject.GetLength() > 1)
		m_sFilename = m_sObject.Right(m_sObject.GetLength() - nSlash - 1);
	else
		m_sFilename = m_sObject;

	//Set the file status text
	CString sFileStatus;
	ASSERT(m_sObject.GetLength());
	ASSERT(m_sServer.GetLength());
	sFileStatus.Format(GetResString(IDS_HTTPDOWNLOAD_FILESTATUS), m_sFilename, m_sServer);
	m_ctrlFileStatus.SetWindowText(sFileStatus);

	// set labels
	SetDlgItemText(IDC_TIMELEFTTEXT,GetResString(IDS_ESTTIMELEFT));
	SetDlgItemText(IDC_TRANSFER_RATE_LABEL,GetResString(IDS_TRANSFER_RATE_LABEL));

	//Spin off the background thread which will do the actual downloading
	m_pThread = AfxBeginThread(_DownloadThread, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if (m_pThread == NULL)
	{
		TRACE(_T("Failed to create download thread, dialog is aborting\n"));
		EndDialog(IDCANCEL);
		return TRUE;
	}
	m_pThread->m_bAutoDelete = FALSE;
	m_pThread->ResumeThread();

	return TRUE;
}