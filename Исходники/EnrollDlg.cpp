BOOL CEnrollDlg::OnInitDialog() // 每次DoModal之前都会执行
{
	CDialog::OnInitDialog();

	faceSz = g_faceMngr->m_faceSz;
	showSz = faceSz;

	if (showSz.height != 160) // (160*130)是预定显示大小，如果归一化大小不是则进行调整
		showSz *= (160.0/showSz.height);
	if (showSz.width > 130)
		showSz *= (130.0/showSz.width);

	EmbedCvWindow(GetDlgItem(IDC_FACE)->m_hWnd, "face", showSz.width, showSz.height);
	if (noface) cvShowImage("face", noface);
	RECT rc;
	GetWindowRect(&rc);
	SetWindowPos(NULL, rc.left + 15, rc.top + 300, 0,0, SWP_NOSIZE | SWP_NOZORDER);

	m_nShootNum = 0;

	m_strName = "";
	UpdateData(FALSE);
	CWnd *pBtn = GetDlgItem(IDC_SHOOT);
	RECT rc1;
	pBtn->GetClientRect(&rc1);
	pBtn->SetWindowText("拍摄");
	pBtn->SetWindowPos(NULL, 0,0, 35, rc1.bottom-rc1.top, SWP_NOMOVE | SWP_NOZORDER);
	GetDlgItem(IDC_DEL_SHOOT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ENROLL_PIC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_IMPORT_MODELS)->ShowWindow(SW_SHOW);
	if (g_bHasWebcam)
	{
		m_frame = cvCreateImage(g_webcam.GetFrameSize(), IPL_DEPTH_8U, 3);
		SetDlgItemText(IDC_SHOOT_GUIDE, 
			"若要从摄像头注册，请等画面较正时点“拍摄”。\n"
			"如果画面定住,说明人脸检测及对准未成功，请改善姿势、光照。\n"
			"为保证识别率，建议以正常表情拍摄3~4张。");
		m_bFaceStarted = true;
		m_thrdFace = ::AfxBeginThread(ShowFaceProc, this);
	}
	else
	{
		m_frame = NULL;
		SetDlgItemText(IDC_SHOOT_GUIDE, "");
		CWnd *pWnd = GetDlgItem(IDC_SHOOT);
		pWnd->EnableWindow(FALSE);
	}
	
	return TRUE;
}