void CWndFriendCtrl::OnLButtonUp( UINT nFlags, CPoint point )
{
	m_bDrag = FALSE;

	CPoint pt( 3, 3 );
	CRect rect;

	int count = m_nDrawCount;	
	
	for( int j = 0 ; j < m_nServerCount[g_Neuz.m_uIdofMulti-1] ; ++j, ++count )
	{
		rect.SetRect( pt.x, pt.y, pt.x + m_rectWindow.Width() - m_wndScrollBar.GetClientRect().Width(), pt.y + m_nFontHeight );
		if( rect.PtInRect( point ) )
		{
			m_nCurSelect = count;
			return;
		}
		pt.y += m_nFontHeight;
	}
	
	for( j = 0 ; j < 11 ; ++j )
	{
		if( j == g_Neuz.m_uIdofMulti -1 )
		{
			continue;
		}
		for( int k = 0 ; k < m_nServerCount[j] ; ++k, ++count )
		{
			rect.SetRect( pt.x, pt.y, pt.x + m_rectWindow.Width() - m_wndScrollBar.GetClientRect().Width(), pt.y + m_nFontHeight );
			if( rect.PtInRect( point ) )
			{
				m_nCurSelect = count;
				return;
			}
			pt.y += m_nFontHeight;
		}
	}
	g_WorldMng()->SetObjFocus(NULL);
}