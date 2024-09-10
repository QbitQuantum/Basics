HWND OGLWindow::InitInstance(HINSTANCE hInstance, HWND hParent, bool doubleBuf, int x, int y, int w, int h)
{
	// Create the main Window.
	m_hWnd = CreateWindow( 
		m_ClassName,        // name of Window class 
		m_WindowTitle,       // title-bar string 
		WS_BORDER | WS_CHILD/* | WS_CLIPSIBLINGS | WS_CLIPCHILDREN*/, //  
		0,       // default horizontal position 
		0,       // default vertical position 
		1,       // default width 
		1,       // default height 
		hParent,         // no owner Window 
		(HMENU) NULL,        // use class menu 
		hInstance,           // handle to application instance 
		(LPVOID) NULL);      // no Window-creation data 

	if ( !CreateContext() )
	{
		DestroyWindow(m_hWnd);
		m_hWnd = NULL;
	}

	m_width = w;
	m_height = h;

	MoveWindow(m_hWnd, x, y, w, h, FALSE);
	ShowWindow(m_hWnd, SW_HIDE); 

	BOOL makeCurResult = wglMakeCurrent( m_hDC, m_Context );

	return m_hWnd; 
}