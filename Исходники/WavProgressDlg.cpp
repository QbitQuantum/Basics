BOOL CWavProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	static_cast<CProgressCtrl*>(GetDlgItem(IDC_PROGRESS_BAR))->SetRange(0, 100);
	CView *pView = static_cast<CFrameWnd*>(AfxGetMainWnd())->GetActiveView();		// // //
	CSoundGen *pSoundGen = theApp.GetSoundGenerator();

	pView->Invalidate();
	pView->RedrawWindow();

	// Start rendering
	CString FileStr;
	AfxFormatString1(FileStr, IDS_WAVE_PROGRESS_FILE_FORMAT, m_sFile);
	SetDlgItemText(IDC_PROGRESS_FILE, FileStr);

	if (!pSoundGen->RenderToFile(m_sFile.GetBuffer(), m_iSongEndType, m_iSongEndParam, m_iTrack))
		EndDialog(0);

	m_dwStartTime = GetTickCount();
	SetTimer(0, 200, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}