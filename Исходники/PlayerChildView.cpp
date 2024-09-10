LRESULT CChildView::OnNcHitTest(CPoint point)
{
	UINT nHitTest = CWnd::OnNcHitTest(point);

	CMainFrame* pFrame = ((CMainFrame*)GetParentFrame());

	WINDOWPLACEMENT wp;
	pFrame->GetWindowPlacement(&wp);

	if (!pFrame->m_fFullScreen && wp.showCmd != SW_SHOWMAXIMIZED && AfxGetAppSettings().iCaptionMenuMode==MODE_BORDERLESS) {
		CRect rcClient, rcFrame;
		GetWindowRect(&rcFrame);
		rcClient = rcFrame;

		CSize sizeBorder(GetSystemMetrics(SM_CXBORDER), GetSystemMetrics(SM_CYBORDER));

		rcClient.InflateRect(-(5 * sizeBorder.cx), -(5 * sizeBorder.cy));
		rcFrame.InflateRect(sizeBorder.cx, sizeBorder.cy);

		if (rcFrame.PtInRect(point)) {
			if (point.x > rcClient.right) {
				if (point.y < rcClient.top) {
					nHitTest = HTTOPRIGHT;
				} else if (point.y > rcClient.bottom) {
					nHitTest = HTBOTTOMRIGHT;
				} else {
					nHitTest = HTRIGHT;
				}
			} else if (point.x < rcClient.left) {
				if (point.y < rcClient.top) {
					nHitTest = HTTOPLEFT;
				} else if (point.y > rcClient.bottom) {
					nHitTest = HTBOTTOMLEFT;
				} else {
					nHitTest = HTLEFT;
				}
			} else if (point.y < rcClient.top) {
				nHitTest = HTTOP;
			} else if (point.y > rcClient.bottom) {
				nHitTest = HTBOTTOM;
			}
		}
	}

	return nHitTest;
}