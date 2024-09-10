BOOL COptLgnDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rcClient(0, 0, 469, 179);
	MoveWindow(&rcClient, FALSE);
	CRgn rgn;
	rgn.CreateRoundRectRgn(0, 0, rcClient.Width(), rcClient.Height(), 10, 10);

	CRect rc = CRect(10, 5, 10 + 100, 30);
	m_btnCaption.MoveWindow(&rc);

	rc = CRect(rcClient.right-56, 3, rcClient.right-15, 24+3);
	m_btnClose.MoveWindow(&rc);
	m_btnClose.SetImage(TEXT("Skin/Wnd/SysSet/按钮_关闭_默认状态.png"), 
		TEXT("Skin/Wnd/SysSet/按钮_关闭_鼠标经过.png"), TEXT("Skin/Wnd/SysSet/按钮_关闭_鼠标按下.png"));

	rc = CRect(188, 60, 400, 85);
	m_btnTip.MoveWindow(&rc);

	rc.OffsetRect(5, 32);
	rc.right = rc.left + 245; rc.bottom = rc.top + 16;
	m_edtPassword.MoveWindow(&rc);

	rc = CRect(200, 130, 200+97, 130+25);
	m_btnOK.SetImage(TEXT("Skin/Wnd/optlogin/按钮_登陆_默认状态.png"),
		TEXT("Skin/Wnd/optlogin/按钮_登陆_鼠标经过.png"));
	m_btnOK.MoveWindow(&rc);

	rc.OffsetRect(rc.Width() + 20, 0);
	m_btnCancel.SetImage(TEXT("Skin/Wnd/optlogin/按钮_取消_默认状态.png"),
		TEXT("Skin/Wnd/optlogin/按钮_取消_鼠标经过.png"));
	m_btnCancel.MoveWindow(&rc);

	SetWindowRgn(rgn, TRUE);
	CenterWindow();

	m_edtPassword.SetFocus();
	return FALSE;
}