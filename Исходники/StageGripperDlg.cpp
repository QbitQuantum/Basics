BOOL CStageGripperDlg::YoInitDialog() 
{
	CFrameWnd *pMainFrame = GetTopLevelFrame(); 
	CView *pView = pMainFrame->GetActiveView();
	CStageDoc *pDoc = ((CStageView *)pView)->GetDocument();
	int dWidth;
	int dHeight;
	RECT rect;
	RECT mfRect;
	CREATESTRUCT cs;
	char s[128];
	CWnd *pCBox;

	m_init = TRUE;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

    cs.cy = ::GetSystemMetrics(SM_CYSCREEN); 
    cs.cx = ::GetSystemMetrics(SM_CXSCREEN); 

	this->GetWindowRect(&rect);
	dWidth = (rect.right - rect.left);
	dHeight = rect.bottom - rect.top;
	((CMainFrame *)pMainFrame)->m_viewPart->GetWindowRect(&mfRect);
	//rect.right = YO_MIN(mfRect.right + dWidth, cs.cx);
	//rect.left = rect.right - dWidth;
	rect.top = YO_MIN(mfRect.bottom, cs.cy - dHeight);
	rect.bottom = rect.top + dHeight;
	rect.left = mfRect.left;
	rect.right = rect.left + dWidth;
	//rect.right -= 3;
	//rect.left -= 3;
	//rect.top -= 8;
	//rect.bottom -= 8;
	this->MoveWindow(&rect, TRUE);

	sprintf(s, "%.3f", ((CStageGripper *)pDoc->m_currentDevice)->m_displacementOpen);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_DISPLACEMENT_OPEN);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();
	
	sprintf(s, "%.3f", ((CStageGripper *)pDoc->m_currentDevice)->m_displacementClose);
	pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_DISPLACEMENT_CLOSE);
	pCBox->SetWindowText(s);
	pCBox->UpdateWindow();

	if (((CStageGripper *)pDoc->m_currentDevice)->m_typeTranslating == TRUE)
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_TRANSLATING);
		((CButton *)pCBox)->SetCheck(1);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_ROTATING);
		((CButton *)pCBox)->SetCheck(0);
	}
	else
	{
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_TRANSLATING);
		((CButton *)pCBox)->SetCheck(0);
		pCBox = (CComboBox*)this->GetDlgItem(IDC_GRIPPER_TYPE_ROTATING);
		((CButton *)pCBox)->SetCheck(1);
	}
	
	UpdateData(FALSE);	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}