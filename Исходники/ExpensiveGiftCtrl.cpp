void CExpensiveGiftCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{ 
	if ( !m_bTrackLeave) {
		//Track the mouse leave event
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = GetSafeHwnd();
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		m_bTrackLeave = true;

		if (m_toolTip.m_hWnd == NULL)
		{
			m_toolTip.Create(this, TTS_ALWAYSTIP);
			m_toolTip.AddTool(this, sNowInfo);
			m_toolTip.SetMaxTipWidth(1000);
			//m_toolTip.Activate(FALSE);
		}
		else
		m_toolTip.UpdateTipText(sNowInfo,this);
		//::PostMessage(GetParent()->GetSafeHwnd(),WM_SCROLL_TIP,1,(LPARAM)(LPCTSTR)sNowInfo);

	}
	
	CWnd::OnMouseMove(nFlags, point);
}