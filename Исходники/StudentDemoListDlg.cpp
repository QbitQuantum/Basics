BOOL CStudentDemoListDlg::OnInitDialog()
{
	CElcSkinDialog::OnInitDialog();

	AdjustImagePanePos(IDC_IMAGE_PANE);
	BindButton(IDC_BTN_HELP);
	BindButton(ID_BTN_OK);
	BindButton(ID_BTN_CANCEL);
	BindPictureCtrl(IDC_STUDENT_DEMO_ICON, IDR_RT_STUDENT_DEMO);

	if (!GetParent()) {
		SetParent(m_pWndParent);
		SetOwner(m_pWndParent);
	}

	CString strText;
	strText.LoadString(IDS_DEMO_TO_ALL);
	m_wndListType.InsertString(0, strText);
	strText.LoadString(IDS_DEMO_TO_STUDENT);
	m_wndListType.InsertString(1, strText);
	strText.LoadString(IDS_DEMO_TO_GROUP);
	m_wndListType.InsertString(2, strText);
	m_wndListType.SetCurSel(0);

	m_wndAvailableList.EnableCheck(IDB_STATE_IMAGE_LIST16);
	m_wndAvailableList.EnableSelect(TRUE);

	m_nSelectType = DEMO_TO_ALL;
	GetDlgItem(IDC_CHK_SELECT_ALL)->EnableWindow(m_nSelectType != DEMO_TO_ALL);
	InitAvailableList(m_nSelectType);
	UpdateButtonState();

	if (m_pTeacherFrame) {
		DWORD dwCallbackMask;
		dwCallbackMask =  ITeacherFrame::ELC_MEMBER_CONNECTED
						| ITeacherFrame::ELC_MEMBER_DISCONNECTED
						| ITeacherFrame::ELC_MEMBER_NAMECHANGED
						| ITeacherFrame::ELC_EXIT;
		m_pTeacherFrame->RegisterCallback(dwCallbackMask, this, NULL);
	}

	if (m_pDemoMemberInfo) {
		GetWindowText(strText);
		strText += (CString)_T(" [") + m_pDemoMemberInfo->szDefaultName + (CString)_T("] ");
		SetWindowText(strText);
	}

	return TRUE;
}