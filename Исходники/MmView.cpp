LPARAM MmView::OnSetClientRect(WPARAM wParam, LPARAM lParam) {
	CFrameWnd *mainWnd = (CFrameWnd*) AfxGetMainWnd();

	POINT pt = {0, 0}; // margins

	CRect rc1;
	mainWnd->GetWindowRect(&rc1);

	CRect rc2;
	GetWindowRect(&rc2);
	int dx = rc1.Width() - rc2.Width();
	int dy = rc1.Height() - rc2.Height();

	CSize size(int(wParam) + (2*pt.x + 4) + dx, int(lParam) + (2*pt.y+4) + dy);

	UINT flags = SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOMOVE;
	mainWnd->SetWindowPos(&wndTop, 0, 0, size.cx, size.cy, flags);
	return 0;
}