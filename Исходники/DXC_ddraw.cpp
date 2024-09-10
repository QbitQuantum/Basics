BOOL DXC_ddraw::bInit(HWND hWnd)
{
 HRESULT        ddVal;
 DDSURFACEDESC2 ddsd;
 int            iS, iD;

	SetRect(&m_rcClipArea, 0,0, 640, 480);

	ddVal = DirectDrawCreateEx(NULL, (VOID**)&m_lpDD4, IID_IDirectDraw7, NULL);
    if (ddVal != DD_OK) return FALSE;

	if( m_bFullMode == TRUE )
	{
		DDSCAPS2       ddscaps;
		ddVal = m_lpDD4->SetCooperativeLevel(hWnd, DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (ddVal != DD_OK) return FALSE;

		ddVal = m_lpDD4->SetDisplayMode(640, 480, 16,0,0);
		if (ddVal != DD_OK) return FALSE;
		memset( (VOID *)&ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.dwBackBufferCount = 1;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
		
		ddVal = m_lpDD4->CreateSurface(&ddsd, &m_lpFrontB4, NULL);
		if (ddVal != DD_OK) return FALSE;

		ZeroMemory(&ddscaps, sizeof(ddscaps));
		ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
		ddVal = m_lpFrontB4->GetAttachedSurface(&ddscaps, &m_lpBackB4flip);
		if (ddVal != DD_OK) return FALSE;
		SetRect(&m_rcFlipping, 0, 0, 640, 480); // our fictitious sprite bitmap is 
	}
	else
	{
		int cx = GetSystemMetrics(SM_CXFULLSCREEN);
		int cy = GetSystemMetrics(SM_CYFULLSCREEN);

		ddVal = m_lpDD4->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
		if (ddVal != DD_OK) return FALSE;
		
		cx = cx/2;
		cy = cy/2;
		if(cy>280) cy -= 40;
		SetWindowPos( hWnd, HWND_TOP, cx-320, cy-240, 640, 480, SWP_SHOWWINDOW);
		memset( (VOID *)&ddsd, 0, sizeof(ddsd) );
		ddsd.dwSize = sizeof( ddsd );
		ddsd.dwFlags = DDSD_CAPS;
		//ddsd.dwBackBufferCount = 0;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
		
		ddVal = m_lpDD4->CreateSurface(&ddsd, &m_lpFrontB4, NULL);
		if (ddVal != DD_OK) return FALSE;

		SetRect(&m_rcFlipping, cx-320, cy-240, cx+320, cy+240); // our fictitious sprite bitmap is 
	}

	InitFlipToGDI(hWnd);
	m_lpBackB4 = pCreateOffScreenSurface(640, 480);
	if (m_lpBackB4 == NULL) return FALSE;

	// Pre-draw background surface
	m_lpPDBGS = pCreateOffScreenSurface(640+32, 480+32);
	if (m_lpPDBGS == NULL) return FALSE;

	ddsd.dwSize = sizeof(ddsd);
	if (m_lpBackB4->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL) != DD_OK) return FALSE;
	m_pBackB4Addr        = (WORD *)ddsd.lpSurface;
	m_sBackB4Pitch       = (short)ddsd.lPitch >> 1;
	m_lpBackB4->Unlock(NULL);

	_TestPixelFormat();
	for (iS = 0; iS < 64; iS++)
	for (iD = 0; iD < 64; iD++) {
		m_lTransRB100[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 1.0f);
		m_lTransG100[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 1.0f);

		m_lTransRB70[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.7f);
		m_lTransG70[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.7f);
		
		m_lTransRB50[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.5f);
		m_lTransG50[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.5f);

		m_lTransRB25[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.25f);
		m_lTransG25[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.25f);

		m_lTransRB2[iD][iS] = _CalcMaxValue(iS, iD, 'R', 2, 1.0f);
		m_lTransG2[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 2, 1.0f);

		m_lFadeRB[iD][iS]  = _CalcMinValue(iS, iD, 'R');
		m_lFadeG[iD][iS]   = _CalcMinValue(iS, iD, 'G');

		G_lTransRB100[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 1.0f);
		G_lTransG100[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 1.0f);

		G_lTransRB70[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.7f);
		G_lTransG70[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.7f);
		
		G_lTransRB50[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.5f);
		G_lTransG50[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.5f);

		G_lTransRB25[iD][iS] = _CalcMaxValue(iS, iD, 'R', 1, 0.25f);
		G_lTransG25[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 1, 0.25f);

		G_lTransRB2[iD][iS] = _CalcMaxValue(iS, iD, 'R', 2, 1.0f);
		G_lTransG2[iD][iS]  = _CalcMaxValue(iS, iD, 'G', 2, 1.0f);
	}

	m_hFontInUse = NULL;	
	m_hFontInUse = CreateFont(16,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, "Trebuchet MS") ;
	m_hDC = NULL;
		
	return TRUE;
}