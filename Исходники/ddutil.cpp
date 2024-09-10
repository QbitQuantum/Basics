//-----------------------------------------------------------------------------
// Name: CreateWindowedDisplay()
// Desc:
//-----------------------------------------------------------------------------
HRESULT CDisplay::CreateWindowedDisplay( HWND hWnd, DWORD dwWidth, DWORD dwHeight )
{
    HRESULT hr;

    // Cleanup anything from a previous call
    DestroyObjects();

    // DDraw stuff begins here
    if( FAILED( hr = DirectDrawCreateEx( NULL, (VOID**)&m_pDD,
                                         IID_IDirectDraw7, NULL ) ) )
        return E_FAIL;

    // Set cooperative level
    hr = m_pDD->SetCooperativeLevel( hWnd, DDSCL_NORMAL );
    if( FAILED(hr) )
        return E_FAIL;

    RECT  rcWork;
    RECT  rc;
    DWORD dwStyle;

    // If we are still a WS_POPUP window we should convert to a normal app
    // window so we look like a windows app.
    dwStyle  = GetWindowStyle( hWnd );
    dwStyle &= ~WS_POPUP;
    dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX;
    SetWindowLong( hWnd, GWL_STYLE, dwStyle );

    // Aet window size
    SetRect( &rc, 0, 0, dwWidth, dwHeight );

    AdjustWindowRectEx( &rc, GetWindowStyle(hWnd), GetMenu(hWnd) != NULL,
                        GetWindowExStyle(hWnd) );

    SetWindowPos( hWnd, NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
                  SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE );

    SetWindowPos( hWnd, HWND_NOTOPMOST, 0, 0, 0, 0,
                  SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE );

    //  Make sure our window does not hang outside of the work area
    SystemParametersInfo( SPI_GETWORKAREA, 0, &rcWork, 0 );
    GetWindowRect( hWnd, &rc );
    if( rc.left < rcWork.left ) rc.left = rcWork.left;
    if( rc.top  < rcWork.top )  rc.top  = rcWork.top;
    SetWindowPos( hWnd, NULL, rc.left, rc.top, 0, 0,
                  SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE );

    LPDIRECTDRAWCLIPPER pcClipper;
    
    // Create the primary surface
    DDSURFACEDESC2 ddsd;
    ZeroMemory( &ddsd, sizeof( ddsd ) );
    ddsd.dwSize         = sizeof( ddsd );
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    if( FAILED( m_pDD->CreateSurface( &ddsd, &m_pddsFrontBuffer, NULL ) ) )
        return E_FAIL;

    // Create the backbuffer surface
    ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;    
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
    ddsd.dwWidth        = dwWidth;
    ddsd.dwHeight       = dwHeight;

    if( FAILED( hr = m_pDD->CreateSurface( &ddsd, &m_pddsBackBuffer, NULL ) ) )
        return E_FAIL;

    if( FAILED( hr = m_pDD->CreateClipper( 0, &pcClipper, NULL ) ) )
        return E_FAIL;

    if( FAILED( hr = pcClipper->SetHWnd( 0, hWnd ) ) )
    {
        pcClipper->Release();
        return E_FAIL;
    }

    if( FAILED( hr = m_pddsFrontBuffer->SetClipper( pcClipper ) ) )
    {
        pcClipper->Release();
        return E_FAIL;
    }

    // Done with clipper
    pcClipper->Release();

    m_hWnd      = hWnd;
    m_bWindowed = TRUE;
    UpdateBounds();

    return S_OK;
}