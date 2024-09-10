//-----------------------------------------------------------------------------
// Name : CreateDisplay ()
// Desc : Create the display windows, devices etc, ready for rendering.
//-----------------------------------------------------------------------------
bool CDDGameApp::CreateDisplay()
{
    CDDInitialize   Initialize;
    HRESULT         ddReturnVal = 0;
	char cpErrorBuf[1000];
	
	// create dd object and test for error
	ddReturnVal = DirectDrawCreateEx(NULL, (void **)&m_lpddObj, DD_VERSION, NULL);
	if(DDFailedCheck(ddReturnVal, "DirectDrawCreateEx() failed", cpErrorBuf ))
	{	MessageBox(m_hWnd, cpErrorBuf, "Init()", MB_ICONEXCLAMATION); return (0); }
	
	//Give the utilities class to the init class for use with clippers and creating surfaces
	Initialize.setUtilities( m_Utils );
	Initialize.setDirectDObj( m_lpddObj );
	
	//Create the window and setup dd
	if ( FAILED( Initialize.CreateDisplay( m_DDSettings, 0, m_hWnd, StaticWndProc, m_WindowTitle, this ) ))
    {
        MessageBox( m_hWnd, _T("Device creation failed. The application will now exit."), _T("Fatal Error!"), MB_OK | MB_ICONSTOP | MB_APPLMODAL );
        return false;
    
    } // End if Failed
    
	// Retrieve created items
	setPrimarySurf( Initialize.getPrimarySurface() );
	setSecondarySurf( Initialize.getSecondarySurface() );
	m_hWnd = Initialize.getHWND();

	// Load icon and menu
    m_hIcon = LoadIcon( (HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE( IDI_ICON1 ) );
    m_hMenu = LoadMenu( (HINSTANCE)GetModuleHandle(NULL), MAKEINTRESOURCE( IDR_MENU1 ) );

    // Set application icon
    SetClassLong( m_hWnd, GCL_HICON, (long)m_hIcon );
	
    // Set menu only in windowed mode
    if ( m_DDSettings.Windowed )
    {
        SetMenu( m_hWnd, m_hMenu );
    } // End if Windowed

	 // Retrieve the final client size of the window
	if(m_DDSettings.Windowed)
		::GetClientRect( m_hWnd, &m_wndRect );
	else
		::GetWindowRect(m_hWnd, &m_wndRect );

    //Fill in the utilities class
	m_Utils.setWindowHandle( Initialize.getHWND() );
	m_Utils.setWndRect( m_wndRect );
	m_Utils.setSettingsClass( m_DDSettings );
   
    // Show the window
	ShowWindow(m_hWnd, SW_SHOW);

    // Success!!
    return true;
}