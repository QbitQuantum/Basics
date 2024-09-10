LRESULT CDlgLineParam::OnChangePosition(WPARAM wParam, LPARAM lParam)
{
	CWnd *pWnd = (CWnd*)wParam;
	SIZE sz = *((SIZE*)lParam);

	CRect rec;
	GetClientRect(&rec);
	pWnd->SetWindowPos(&wndTop, sz.cx, 0, sz.cy, rec.Height(), 
		SWP_SHOWWINDOW);

	return true;
}