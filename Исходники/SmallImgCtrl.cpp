void CSmallImgCtrl::OnPaint () {
	CPaintDC dc (this);
	dc.DrawIcon (0, 0, theApp.LoadIcon (m_nID));
}