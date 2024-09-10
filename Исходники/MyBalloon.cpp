void CMyBalloon::OnPaint() 
{
	CPaintDC dc(this); 

	CRgn rgn; 
	rgn.CreateRectRgn (0,0,0,0);
	GetWindowRgn (rgn);
	
	CBrush brWnd; brWnd.CreateSolidBrush (m_pContent->getBkColor ());
	CBrush br1; br1.CreateSolidBrush (m_pContent->getTextColor ());
	dc.FillRgn (&rgn, &brWnd);
	dc.FrameRgn (&rgn, &br1, 1, 1);
}