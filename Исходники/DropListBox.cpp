void CDropListBox::OnMouseMove(UINT nFlags, CPoint point) 
{
	//
	// Is mouse within listbox
	CRect rcClient;
	GetClientRect( rcClient );
	if( !rcClient.PtInRect( point ) )
	{
		ReleaseCapture();
		GetParent()->SendMessage( WM_VRC_SETCAPTURE );
	}

	//
	// Set selection item under mouse
	int nPos = point.y / GetItemHeight(0) + GetTopIndex();
	PLIST_ITEM pItem = (PLIST_ITEM)GetItemDataPtr(nPos);
	if( (DWORD)pItem != -1 )
	{
		if( GetCurSel() != nPos && !pItem->bDisabled )
		{
			SetCurSel( nPos );
		}
	}

	//
	// Check if we have autoscrolled
	if( m_nLastTopIdx != GetTopIndex() )
	{
		int nDiff = m_nLastTopIdx - GetTopIndex();
		m_nLastTopIdx = GetTopIndex();

		SCROLLINFO info;
		info.cbSize = sizeof(SCROLLINFO);
		if( m_pScroll->GetScrollInfo( &info, SIF_ALL|SIF_DISABLENOSCROLL ) )
		{
			info.nPos = m_nLastTopIdx;
			m_pScroll->SetScrollInfo( &info );
		}
	}


//	OutputDebugString( "DropListBox MouseMove\n" );

	CListBox::OnMouseMove(nFlags, point);

}