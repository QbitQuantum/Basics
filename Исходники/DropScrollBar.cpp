void CDropScrollBar::VScroll(UINT nSBCode, UINT nPos) 
{
	if( !m_pListBox )
		return;

	SCROLLINFO info;

	info.cbSize = sizeof(SCROLLINFO);
	if( !GetScrollInfo( &info, SIF_ALL|SIF_DISABLENOSCROLL ) )
		return;

	switch( nSBCode )
	{
	case SB_BOTTOM: // Scroll to bottom.
		break;

	case SB_ENDSCROLL: // End scroll.
		//+++
		ReleaseCapture();
		GetParent()->PostMessage( WM_VRC_SETCAPTURE );
		break;

	case SB_LINEDOWN: // Scroll one line down.
		info.nPos++;
		if( info.nPos > info.nMax )
			info.nPos = info.nMax;
		m_pListBox->SetTopIdx( info.nPos );
		break;

	case SB_LINEUP: // Scroll one line up.
		info.nPos--;
		if( info.nPos < info.nMin )
			info.nPos = info.nMin;
		m_pListBox->SetTopIdx( info.nPos );
		break;

	case SB_PAGEDOWN: // Scroll one page down.
		info.nPos += info.nPage;
		if( info.nPos > info.nMax )
			info.nPos = info.nMax;
		m_pListBox->SetTopIdx( info.nPos );
		break;

	case SB_PAGEUP: // Scroll one page up.
		info.nPos -= info.nPage;
		if( info.nPos < info.nMin )
			info.nPos = info.nMin;
		m_pListBox->SetTopIdx( info.nPos );
		break;

	case SB_THUMBPOSITION: // Scroll to the absolute position. The current position is provided in nPos.
		info.nPos = nPos;
		m_pListBox->SetTopIdx( info.nPos );
		break;

	case SB_THUMBTRACK: // Drag scroll box to specified position. The current position is provided in nPos.
		info.nPos = nPos;
		m_pListBox->SetTopIdx( info.nPos );
		break;

	case SB_TOP: // Scroll to top. 
		break;

	}
	SetScrollInfo( &info );
			
}