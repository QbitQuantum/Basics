void CStatusWindow::redraw()
{
//	if ( !ToolCanDraw() )
//		return;

	if ( !m_pScrollbar )
		return;

	CDrawHelper helper( this, RGB( 0, 0, 0 ) );

	RECT rc;
	helper.GetClientRect( rc );

	RECT rcText = rc;

	int lineheight = ( STATUS_FONT_SIZE + 2 );

	InflateRect( &rcText, -4, 0 );
	rcText.bottom = h2() - 4;
	rcText.top = rcText.bottom - lineheight;

	int minval = m_pScrollbar->getMinValue();
	int maxval = m_pScrollbar->getMaxValue();
	int pagesize = m_pScrollbar->getPagesize();
	int curval = m_pScrollbar->getValue();

	int offset = ( maxval - pagesize ) - curval;
	offset = ( offset + lineheight - 1 ) / lineheight;

	offset = max( 0, offset );
	//offset = 0;
	//offset += 10;
	//offset = max( 0, offset );

	for ( int i = 0; i < MAX_TEXT_LINES - offset; i++ )
	{
		int rawline = m_nCurrentLine - i - 1;
		if ( rawline <= 0 )
			continue;

		if ( rcText.bottom < 0 )
			break;

		int line = ( rawline - offset ) & TEXT_LINE_MASK;

		COLORREF clr = RGB( m_rgTextLines[ line ].r, m_rgTextLines[ line ].g, m_rgTextLines[ line ].b );

		char *ptext = m_rgTextLines[ line ].m_szText;
		
		RECT rcTime = rcText;
		rcTime.right = rcTime.left + 50;

		char sz[ 32 ];
		sprintf( sz, "%.3f",  m_rgTextLines[ line ].curtime );

		int len = helper.CalcTextWidth( "Arial", STATUS_FONT_SIZE, FW_NORMAL, sz );

		rcTime.left = rcTime.right - len - 5;

		helper.DrawColoredText( "Arial", STATUS_FONT_SIZE, FW_NORMAL, RGB( 255, 255, 150 ), rcTime, sz );

		rcTime = rcText;
		rcTime.left += 50;

		helper.DrawColoredText( "Arial", STATUS_FONT_SIZE, FW_NORMAL, clr, rcTime, ptext );

		OffsetRect( &rcText, 0, -lineheight );
	}
}