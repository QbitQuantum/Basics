//
//	WM_TIMER handler
//
//	Used to handle mouse-scrolling 
//
LRESULT	GridView::OnTimer(UINT_PTR nTimer)
{
	RECT rect;
	POINT pt;
	int dx = 0, dy = 0;
	
	// get the current client-rectangle
	GetActiveClientRect(&rect);

	// get the mouse's client-coordinates
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);

	//
	// scrolling up/down?
	//
	if(pt.y < rect.top)
		dy = ScrollDir(m_nScrollCounter, pt.y - rect.top);

	else if(pt.y >= rect.bottom)
		dy = ScrollDir(m_nScrollCounter, pt.y - rect.bottom);

	//
	// scrolling left / right?
	//
	if(pt.x < rect.left)					
		dx = ScrollDir(m_nScrollCounter, pt.x - rect.left);

	else if(pt.x > rect.right)		
		dx = ScrollDir(m_nScrollCounter, pt.x - rect.right);


	HRGN hrgnUpdate = ScrollRgn(dx * 10, dy, true);

	if(hrgnUpdate != NULL)
	{
		OnMouseMove(pt.x, pt.y);

		InvalidateRgn(m_hWnd, hrgnUpdate, FALSE);
		DeleteObject(hrgnUpdate);
	
		UpdateWindow(m_hWnd);
	}

	m_nScrollCounter++;

	return 0;
}