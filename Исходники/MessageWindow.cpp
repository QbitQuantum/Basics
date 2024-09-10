MessageWindow::MessageWindow( const RString &sClassName )
{
	AppInstance inst;
	WNDCLASS WindowClass =
	{
		CS_OWNDC | CS_BYTEALIGNCLIENT,
		WndProc,
		0,				/* cbClsExtra */
		0,				/* cbWndExtra */
		inst,				/* hInstance */
		NULL,				/* set icon later */
		LoadCursor( NULL, IDC_ARROW ),	/* default cursor */
		NULL,				/* hbrBackground */
		NULL,				/* lpszMenuName */
		sClassName			/* lpszClassName */
	}; 

	if( !RegisterClassA(&WindowClass) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS )
		RageException::Throw( "%s", werr_ssprintf( GetLastError(), "RegisterClass" ).c_str() );

	// XXX: on 2k/XP, use HWND_MESSAGE as parent
	m_hWnd = CreateWindow( sClassName, sClassName, WS_DISABLED, 0, 0, 0, 0, NULL, NULL, inst, NULL );
	ASSERT( m_hWnd != NULL );

	SetProp( m_hWnd, "MessageWindow", this );
}