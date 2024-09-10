BOOL mfc_render_init(HWND hWnd)
{
	DDSURFACEDESC    ddsd;
	DDCAPS           ddcaps;

	HRESULT          hRet;

	///////////////////////////////////////////////////////////////////////////
	// Create the main DirectDraw object
	///////////////////////////////////////////////////////////////////////////
	hRet = DirectDrawCreate(NULL, &g_pDD, NULL);
	if (hRet != DD_OK)
		return PRINT_ERRMSG(TEXT("DirectDrawCreate FAILED"));

	// Get exclusive mode
	hRet = g_pDD->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
	if (hRet != DD_OK)
		return PRINT_ERRMSG(TEXT("SetCooperativeLevel FAILED"));


	// Get a primary surface interface pointer (only needed for init.)

	memset(&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	hRet = g_pDD->CreateSurface(&ddsd, &g_pDDSPrimary, NULL);
	if (hRet != DD_OK)
		return PRINT_ERRMSG(TEXT("CreateSurface FAILED"));

	// See if we can support overlays.
	memset(&ddcaps, 0, sizeof(ddcaps));
	ddcaps.dwSize = sizeof(ddcaps);
	hRet = g_pDD->GetCaps(&ddcaps, NULL);
	if (hRet != DD_OK)
		return PRINT_ERRMSG(TEXT("GetCaps FAILED"));

	if (ddcaps.dwOverlayCaps == 0)
		return PRINT_ERRMSG(TEXT("Overlays are not supported in hardware!"));


	// SW YUV->RGB conversion table initialization
	_initConvTab();

	return TRUE;
}