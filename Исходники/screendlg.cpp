void CScreenDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if (nSBCode != SB_ENDSCROLL)
	{
		SCROLLINFO hStructure;
		GetScrollInfo(SB_HORZ, &hStructure);
		hStructure.nPos = nPos;
		SetScrollInfo(SB_HORZ, &hStructure);
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}