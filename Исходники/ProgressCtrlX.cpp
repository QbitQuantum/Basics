void CProgressCtrlX::DrawClippedText(const CDrawInfo& info, const CRect& rcClip, CString& sText, const CPoint& ptWndOrg)
{
	CDC *pDC = info.pDC;
	CRgn rgn;
	CRect rc = ConvertToReal(info, rcClip);
	rc.OffsetRect(-ptWndOrg);
	rgn.CreateRectRgn(rc.left, rc.top, rc.right, rc.bottom);
	pDC->SelectClipRgn(&rgn);
	pDC->TextOut (0, 0, sText);
	rgn.DeleteObject();
}