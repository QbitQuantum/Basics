CSize CRichElement::GetSize() const
{
	CSize sz( 0, 0 );

	if ( m_nType == retGap )
	{
		_stscanf( m_sText, L"%lu", &sz.cx );
	}
	else if ( m_nType == retBitmap && m_hImage != NULL )
	{
		BITMAP pInfo = {};
		GetObject( (HBITMAP)m_hImage, sizeof(pInfo), &pInfo );

		sz.cx = pInfo.bmWidth;
		sz.cy = pInfo.bmHeight;
	}
	else if ( m_nType == retIcon )
	{
		sz.cx = sz.cy = 16;

		ICONINFO ii;
		if ( GetIconInfo( (HICON)m_hImage, &ii ) )
		{
			BITMAP bmInfo = {};
			GetObject( ii.hbmColor, sizeof(BITMAP), &bmInfo );
			if ( bmInfo.bmWidth > 16 )
				sz.cx = bmInfo.bmWidth;
			if ( bmInfo.bmHeight > 16 )
				sz.cy = bmInfo.bmHeight;
			DeleteObject( ii.hbmColor );
			DeleteObject( ii.hbmMask );
		}

		UINT nID = 0;
		_stscanf( m_sText, L"%u.%li.%li", &nID, &sz.cx, &sz.cy );
	}
	else if ( m_nType == retEmoticon || m_nType == retCmdIcon )
	{
		sz.cx = sz.cy = 16;
	}
	else if ( m_nType == retAnchor )
	{
		sz.cx = sz.cy = 16;
		_stscanf( m_sText, L"%li.%li", &sz.cx, &sz.cy );
	}

	return sz;
}