BOOL CMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect rcClient(0, 0, 463, 215);
	CRgn rgn;
	rgn.CreateRoundRectRgn(rcClient.left, rcClient.top, rcClient.right, rcClient.bottom, 5, 5);

	CRect rc = rcClient;
	rc.left = rc.right - 51;
	rc.right = rc.right - 10;
	rc.bottom = rc.top + 24;
	m_btnClose.MoveWindow(&rc);
	m_btnClose.SetImage(TEXT("Skin/Wnd/Msg/x.png"), TEXT("Skin/Wnd/Msg/x_a.png"));

	rc.left = 10; rc.top = 5;
	rc.bottom = rc.top + 24; rc.right = rc.left + 100;
	m_btnTip.MoveWindow(&rc);
	m_btnTip.SetTextStyle(DEFAULT_FONT_NAME, 12, RGB(255, 255, 255), RGB(255, 255, 255),
		RGB(255, 255, 255), RGB(255, 255, 255));

	rc.left = 200; rc.top = 175;
	rc.right = rc.left + 97; rc.bottom = rc.top + 25;
	m_btnOK.SetImage(TEXT("Skin/Wnd/Msg/button01.png"));
	m_btnOK.MoveWindow(&rc);

	m_btnContent.MoveWindow(10, 40, 440, 80);
	m_btnContent.SetWindowText(m_strContent);
	m_btnContent.SetTextStyle(DEFAULT_FONT_NAME, 12, RGB(255, 255, 0), RGB(255, 255, 0),
		RGB(255, 255, 0), RGB(255, 255, 0), CButtonEx::BTEXT_CENTER);

	MoveWindow(&rcClient, FALSE);
	CenterWindow();
	SetWindowRgn(rgn, TRUE);

	return TRUE;
}