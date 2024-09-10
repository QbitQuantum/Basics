void CXTPSyntaxEditTipWnd::OnNcPaint()
{
	CXTPWindowRect rc(this);
	rc.OffsetRect(-rc.TopLeft());

	CWindowDC dc(this);
	dc.SetBkColor(GetBackColor());
	dc.SetTextColor(GetTextColor());
	dc.FillSolidRect(&rc, dc.GetBkColor());
	dc.DrawFocusRect(&rc);
}