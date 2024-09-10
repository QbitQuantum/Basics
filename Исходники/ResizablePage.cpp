void CResizablePage::AddAnchor(HWND wnd, CSize tl_type, CSize br_type)
{
	ASSERT(wnd != NULL && ::IsWindow(wnd));
	ASSERT(::IsChild(*this, wnd));
	ASSERT(tl_type != NOANCHOR);

	// get control's window class
	
	CString st;
	GetClassName(wnd, st.GetBufferSetLength(MAX_PATH), MAX_PATH);
	st.ReleaseBuffer();
	st.MakeUpper();

	// add the style 'clipsiblings' to a GroupBox
	// to avoid unnecessary repainting of controls inside
	if (st == "BUTTON")
	{
		DWORD style = GetWindowLong(wnd, GWL_STYLE);
		if (style & BS_GROUPBOX)
			SetWindowLong(wnd, GWL_STYLE, style | WS_CLIPSIBLINGS);
	}

	// wnd classes that don't redraw client area correctly
	// when the hor scroll pos changes due to a resizing
	BOOL hscroll = FALSE;
	if (st == "LISTBOX")
		hscroll = TRUE;

	// wnd classes that need refresh when resized
	BOOL refresh = FALSE;
	if (st == "STATIC")
	{
		DWORD style = GetWindowLong(wnd, GWL_STYLE);

		switch (style & SS_TYPEMASK)
		{
		case SS_LEFT:
		case SS_CENTER:
		case SS_RIGHT:
			// word-wrapped text needs refresh
			refresh = TRUE;
		}

		// centered images or text need refresh
		if (style & SS_CENTERIMAGE)
			refresh = TRUE;

		// simple text never needs refresh
		if ((style & SS_TYPEMASK) == SS_SIMPLE)
			refresh = FALSE;
	}

	// get dialog's and control's rect
	CRect wndrc, objrc;

	GetClientRect(&wndrc);
	::GetWindowRect(wnd, &objrc);
	ScreenToClient(&objrc);
	
	CSize tl_margin, br_margin;

	if (br_type == NOANCHOR)
		br_type = tl_type;
	
	// calculate margin for the top-left corner

	tl_margin.cx = objrc.left - wndrc.Width() * tl_type.cx / 100;
	tl_margin.cy = objrc.top - wndrc.Height() * tl_type.cy / 100;
	
	// calculate margin for the bottom-right corner

	br_margin.cx = objrc.right - wndrc.Width() * br_type.cx / 100;
	br_margin.cy = objrc.bottom - wndrc.Height() * br_type.cy / 100;

	// add to the list
	m_plLayoutList.AddTail(new Layout(wnd, tl_type, tl_margin,
		br_type, br_margin, hscroll, refresh));
}