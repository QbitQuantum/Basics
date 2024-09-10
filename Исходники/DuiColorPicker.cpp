void CDuiColorPicker::OnPaint( CDCHandle dc )
{
	CRect rcClient;
	GetClient(&rcClient);
	ALPHAINFO ai;
	CGdiAlpha::AlphaBackup(dc,rcClient,ai);
	dc.FillSolidRect(&rcClient,m_crCur);
	dc.DrawEdge(&rcClient, BDR_RAISEDINNER, BF_RECT);
	CGdiAlpha::AlphaRestore(dc,ai);
}