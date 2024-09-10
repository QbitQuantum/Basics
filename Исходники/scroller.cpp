void CScrollerCorner::OnLButtonDown(wxMouseEvent &event)
{
#ifdef GERRYXXX
	CWnd::OnLButtonDown(nFlags, pt);

	CWnd* pParent = GetParent();
	CRect rWin;
	pParent->GetWindowRect(&rWin);

	// calc screen coords of bottom-right frame corner
	pt.x = rWin.Width() - 1;
	pt.y = rWin.Height() - 1;
	pParent->ClientToScreen(&pt);

	pParent->SendMessage(WM_NCLBUTTONDOWN, WPARAM(HTSIZE),
						 MAKELPARAM(WORD(pt.x), WORD(pt.y)));
#endif
}