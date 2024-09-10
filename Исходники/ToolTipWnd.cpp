// --------------------------------------------------------------------------
void CToolTipWnd::OnTimer( UINT nIDEvent ) 
{
	if (nIDEvent == ID_TIMER_TOOLTIP_HIDE)
	{
		KillTimer();
		KillShowTimer();
		ShowWindow(SW_HIDE);

	}
	else if (nIDEvent == ID_TIMER_TOOLTIP_SHOW)
	{
		POINT pt;

		// Where is the mouse right now?
		if (GetCursorPos(&pt))
		{
			// Over which window?
			CWnd* pWnd = WindowFromPoint(pt);

			// Save the relevant window handles
			TTWNDSTRUCT ws;
			ZeroMemory(&ws, sizeof(ws));
			ws.hWndToolTip = GetSafeHwnd();
			ws.hWndToolTipParent = pWnd->GetSafeHwnd();

			// Now do the window handle comparisons
			EnumChildWindows(m_hParentWnd, EnumChildProc, (LPARAM)&ws); 
		}
 
	}


	CWnd::OnTimer(nIDEvent);
}