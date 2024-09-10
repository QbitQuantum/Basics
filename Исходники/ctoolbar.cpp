HBITMAP CToolbar::SetImageList(HBITMAP hBitmap, COLORREF clrMask)
{
	if ( m_himl )
	{
		ImageList_Destroy( m_himl );
		m_himl = NULL;
	}

	BITMAP bmp = { 0 };
	if ( GetObject( hBitmap, sizeof(bmp), &bmp ) )
	{
		UINT uFlags = ILC_COLOR;
		switch(bmp.bmBitsPixel)
		{
		case 16: uFlags = ILC_COLOR16; break;
		case 24: uFlags = ILC_COLOR24; break;
		case 32: uFlags = ILC_COLOR32; break;
		}

		m_himl = ImageList_Create( bmp.bmHeight, bmp.bmHeight, uFlags | ILC_MASK, bmp.bmWidth / bmp.bmHeight, 0 );

		if ( m_himl )
		{
			ImageList_AddMasked( m_himl, hBitmap, clrMask );
			cSendMessage( TB_SETIMAGELIST, 0, (LPARAM) m_himl );
			m_szButton.cx = m_szButton.cy = bmp.bmHeight;
		}
	}

	return hBitmap;
}