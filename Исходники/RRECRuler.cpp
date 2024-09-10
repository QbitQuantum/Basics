void CRRECRuler::OnPaint()
/* ============================================================
	Function :		CRRECRuler::OnPaint
	Description :	Handles the "WM_PAINT" message from Windows.
					Draws the ruler to a memory "CDC" that is 
					blitted to the screen (double buffering)
	Access :		Protected
					
	Return :		void
	Parameters :	none

	Usage :			Called from MFC

   ============================================================*/
{
	CPaintDC mainDC(this);

	// Set up data
	int pos = GetParent()->SendMessage( urm_GETSCROLLPOS );

	CRect rect;
	GetClientRect( rect );

	// Create off-screen canvas
	CDC dc;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap( &mainDC, rect.Width(), rect.Height() );
	dc.CreateCompatibleDC( &mainDC );
	CBitmap* oldbmp = dc.SelectObject( &bmp );

	dc.FillSolidRect( rect, m_crBack);

	// Set up canvas
	BOOL bEnabled = IsWindowEnabled();

	COLORREF crBack = GetSysColor(bEnabled ? COLOR_WINDOW : COLOR_3DFACE);
	COLORREF crText = GetSysColor(bEnabled ? COLOR_WINDOWTEXT : COLOR_3DSHADOW);

	// Set up data for the inner ruler window
	CRect winRect( rect );
	winRect.top += 3;
	winRect.bottom -= 5;
	winRect.right -= 3;
	winRect.left += m_margin - 2;

	if (bEnabled) // else same as dialog bk color
		dc.FillSolidRect( winRect, GetSysColor(COLOR_WINDOW));

	// Frame the inside
	CThemed th(this, _T("EDIT"));

	if (th.AreControlsThemed()) 
	{
		winRect.InflateRect(0, 1, 0, 1);

		int nState = ETS_NORMAL;

		if (!bEnabled)
			nState = ETS_DISABLED;
		else if (GetStyle() & ES_READONLY)
			
			nState = ETS_READONLY;

		th.DrawBackground(&dc, EP_EDITTEXT, nState, winRect);

		// get the theme bk color for the text
		crBack = th.GetThemeColor(EP_EDITTEXT, nState, TMT_FILLCOLOR);
	}
	else
	{
		dc.Draw3dRect(winRect, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DHILIGHT));
		winRect.DeflateRect(1, 1);
		dc.Draw3dRect(winRect, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DFACE));
		winRect.InflateRect(1, 1);
	}

	int midpoint = winRect.top + ( winRect.Height() / 2 );
	int leftmarg = winRect.left + 2 - pos;
	int width = winRect.Height();
	int t;

	// Print the values in the ruler scale
	dc.SetBkColor(crBack);
	dc.SetTextColor(crText);
	dc.SelectStockObject( BLACK_PEN );
	dc.SelectStockObject( DEFAULT_GUI_FONT );
	
	if( m_mode == MODE_INCH )
	{
		int inch4 = ( int ) ( ( double ) m_physicalInch / 4.0 +.5 );
		int inch8 = ( int ) ( ( double ) m_physicalInch / 8.0 +.5 );

		// Drawing scale markers
		for( t = ( leftmarg + ( int ) ( inch8 +.5 ) ) ; t < rect.right - m_margin ; t += ( int ) ( inch8 + .5 ) )
		{
			dc.MoveTo( t, midpoint - 1 );
			dc.LineTo( t, midpoint + 1 );
		}

		for( t = leftmarg + inch4 ; t < rect.right - m_margin ; t += inch4 )
		{
			dc.MoveTo( t, midpoint - 3 );
			dc.LineTo( t, midpoint + 3 );
		}

		CRect rectInch;
		CString counter;
		int count = 1;

		// Drawing numbers
		for( t = leftmarg + m_physicalInch ; t < rect.right - m_margin ; t += m_physicalInch )
		{

			rectInch.SetRect( t - width / 2, winRect.top + 2, t + width / 2, winRect.bottom - 2 );
			counter.Format( _T( "%i" ), count );
			dc.DrawText( counter, rectInch, DT_SINGLELINE | DT_CENTER | DT_VCENTER );
			count++;

		}
	}
	else
	{
		int cm = ( int ) ( ( double ) m_physicalInch / 2.54 + .5 );
		int cm2 = ( int ) ( ( double ) cm / 2.0 );

		// Drawing scale markers
		for( t = leftmarg + cm2 ; t < rect.right - m_margin ; t += cm2 )
		{
			dc.MoveTo( t, midpoint - 1 );
			dc.LineTo( t, midpoint + 2 );
		}

		CRect rectNum;
		CString counter;
		int count = 1;

		// Drawing numbers
		for( t = leftmarg + cm ; t < rect.right - m_margin ; t += cm )
		{
			rectNum.SetRect( t - width / 2, winRect.top + 2, t + width / 2, winRect.bottom - 2 );
			counter.Format( _T( "%i" ), count );
			dc.DrawText( counter, rectNum, DT_SINGLELINE | DT_CENTER | DT_VCENTER );
			count++;

		}
	}

	// Draw tab markers
	int max = m_tabs.GetSize();
	for( t = 0 ; t < max ; t++ )
	{

		int x = ( leftmarg + m_tabs[ t ] - 2 );
		if( x > winRect.left && x + 3 < winRect.right )
		{
			dc.MoveTo( x, midpoint + 5 );
			dc.LineTo( x + 6, midpoint + 5 );
			dc.MoveTo( x, midpoint + 6 );
			dc.LineTo( x + 6, midpoint + 6 );

			dc.MoveTo( x + 2, midpoint + 7 );
			dc.LineTo( x + 2, midpoint + 10 );
			dc.MoveTo( x + 3, midpoint + 7 );
			dc.LineTo( x + 3, midpoint + 10 );
		}
	}

	//... and out to screen
	mainDC.BitBlt( 0, 0, rect.Width(), rect.Height(), &dc, 0, 0, SRCCOPY );
	dc.SelectObject( oldbmp );
}