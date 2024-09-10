BOOL CUptOptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rcClient(0, 0, 356, 218);
	CRgn rgn;
	rgn.CreateRoundRectRgn(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, 5, 5);

	CRect rc = rcClient;
	rc.left = rc.right - 51;
	rc.right = rc.right - 10;
	rc.bottom = rc.top + 24;
	m_btnClose.MoveWindow(&rc);
	m_btnClose.SetImage(TEXT("Skin/Wnd/GongGao/x.png"), TEXT("Skin/Wnd/GongGao/x_a.png"));

	rc = CRect(60, 52, 260, 76);
	m_btnQuick.MoveWindow(&rc);
	m_btnQuick.SetCheck(BST_CHECKED);

	rc.OffsetRect(0, 40);
	m_btnForce.MoveWindow(&rc);

	rc.OffsetRect(-10, 60);
	rc.right = rc.left + 97; rc.bottom = rc.top + 25;
	m_btnOK.SetImage(TEXT("Skin/Wnd/GongGao/按钮_确定_默认状态.png"), 
		TEXT("Skin/Wnd/GongGao/按钮_确定_鼠标经过.png"));
	m_btnOK.MoveWindow(&rc);

	rc.OffsetRect(rc.Width() + 20, 0);
	m_btnCancel.SetImage(TEXT("Skin/Wnd/GongGao/button03.png"), 
		TEXT("Skin/Wnd/GongGao/按钮_取消_鼠标经过.png"));
	m_btnCancel.MoveWindow(&rc);

	MoveWindow(&rcClient, FALSE);
	CenterWindow();
	SetWindowRgn(rgn, TRUE);

	return TRUE;
}