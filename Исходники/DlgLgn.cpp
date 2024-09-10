BOOL CDlgLgn::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetWindowText(TEXT("挂机锁"));


	CRect rc(0, 0, 463, 215);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
	MoveWindow(&rc, FALSE);

	CRgn rgn;
	rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 5, 5);

	CRect rx(rc.right - 51, 3, rc.right - 10, 27);
	m_btnClose.MoveWindow(&rx);
	m_btnClose.SetImage(IDB_CLOSE, IDB_CLOSE1, IDB_CLOSE2);

	rx = CRect(250, 100, 435, 100+15);
 	m_edtPwd.MoveWindow(&rx);

	rx.OffsetRect(0, 30);
	m_edtPwd2.MoveWindow(&rx);

	rx = CRect(182, 160, 182+97, 160+25);
	m_btnOk.MoveWindow(&rx);
	m_btnOk.SetImage(IDB_OK);

	rx.OffsetRect(rx.Width() + 10, 0);
	m_btnCancel.MoveWindow(&rx);
	m_btnCancel.SetImage(IDB_CANCEL);

	MoveWindow(&rc, FALSE);
	SetWindowRgn(rgn, TRUE);
	CenterWindow();

	m_edtPwd.SetFocus();
	return FALSE;
}