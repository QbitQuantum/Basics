void CTimeAxis::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRBtnDown = FALSE;
	ReleaseCapture();

	CSize sz = point - m_ptTimeR;
	if ((sz.cx < 3 && sz.cx > -3)
		&& (sz.cy < 3 && sz.cy > -3))	// 单击
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU_TIMEAXIS));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		ClientToScreen(&point);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}

	// 	CStatic::OnRButtonUp(nFlags, point);
}