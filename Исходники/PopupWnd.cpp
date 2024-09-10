void CPopupWnd::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == 1 )
	{
		KillTimer( nIDEvent );	
		CWnd::OnTimer(nIDEvent);
		DestroyWindow();
	}
	else
	{
		CWnd::OnTimer(nIDEvent);
		BOOL bDestroy = TRUE;
		if ( m_hTargetWnd && ::IsWindow( m_hTargetWnd) )
		{
			CRect rect;
			::GetWindowRect( m_hTargetWnd, &rect );
			if ( rect.EqualRect( m_rectTarget ) )
			{
				bDestroy = FALSE;
			}
		}

		if ( bDestroy )
		{
			KillTimer( nIDEvent );	
			DestroyWindow();
		}
	}
	
}