//显示指定单个摄像头，并修改画面风格标志//
void CVedioChiDlg::ShowOneVedio(CRealplayxctrl1 &vedio)
{
	CRect RectOfChiDlg, rect1;
	GetWindowRect(RectOfChiDlg);
	ScreenToClient(RectOfChiDlg);
	rect1.left = RectOfChiDlg.left;
	rect1.top = RectOfChiDlg.top;
	rect1.bottom = RectOfChiDlg.bottom / 16 * 14.7;
	rect1.right = RectOfChiDlg.right;
	vedio.MoveWindow(rect1);

	for (int n = 0; n < 18; n++)
		m_vectVedio[n]->ShowWindow(SW_HIDE);
	
	vedio.ShowWindow(SW_SHOW);
	m_nPicStyle = 1;
}