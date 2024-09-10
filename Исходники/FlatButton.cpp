// For the layout engine.
BOOL ClsFlatButton::OnGetMinSize( ClsSize& szMinSize )
{
	// Add room for the frame.
	szMinSize.CX() += ::GetSystemMetrics( SM_CXFRAME ) * 3;

	// For vista and up we use different numbers.
	if ( ClsGetApp()->GetMajorVersion() >= 6 )
	{
		szMinSize.CY() += ::GetSystemMetrics( SM_CYFRAME ) * 1 + 4;
	}
	else
	{
		szMinSize.CY() += ::GetSystemMetrics( SM_CYFRAME ) * 3;
	}

	// Images?
	int cxi = 0, cyi = 0;
	if ( m_hImages && ImageList_GetImageCount( m_hImages ))
	{
		// Get the image size.
		ImageList_GetIconSize( m_hImages, &cxi, &cyi );

		// Make room.
		cxi += 4;

		// Add sizes.
		szMinSize.CX() += cxi;
		szMinSize.CY() += cyi;
	}

	// Do we have a caption?
	ClsString str( GetSafeHWND());
	if ( str.GetStringLength())
	{
		// Setup the DC.
		ClsGetDC dc( this );
		ClsFont font;
		GetFont( font );
		ClsSelector sel( &dc, font );

		// Measure the caption.
		ClsRect rc;
		dc.DrawText( str, rc, DT_CALCRECT );

		// Add the width of the caption.
		szMinSize.CX() += rc.Width() + 4;

		// Adjust the height if necessary.
		if ( rc.Height() > cyi )
			szMinSize.CY() += rc.Height() - cyi;
	}
	return TRUE;
}