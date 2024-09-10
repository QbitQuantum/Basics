void CColumnResizer::MoveWnd(int WndIdx, int x, int Width)
{
	static const LMARGIN = -2;
	static const RMARGIN = 4;
	ASSERT(WndIdx >= 0 && WndIdx <= m_Parent.WndIdx);
	if (WndIdx == m_Parent.WndIdx)
		x -= GetHScroll();
	else {
		x += LMARGIN;
		Width = Width - (LMARGIN + RMARGIN);
	}
	int Rows = m_WndList == NULL ? GetRowCount() : 1;
	for (int i = 0; i < Rows; i++) {
		CRect	r;
		CWnd	*wp = m_WndList == NULL ? 
			GetWndList(i)[WndIdx] : m_WndList[WndIdx];
		wp->GetWindowRect(r);
		wp->GetParent()->ScreenToClient(r);
		int	PrevWidth = r.Width();
		r.left = x;
		r.right = x + Width;
		wp->MoveWindow(r);
		// if control width changed, must invalidate, otherwise certain control
		// types paint incorrectly, e.g. static control with horiz. centered text
		if (r.Width() != PrevWidth && WndIdx != m_Parent.WndIdx)
			wp->Invalidate(FALSE);
	}
}