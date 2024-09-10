void CDDraw::InitFullscreen(HWND hWnd)
{
	MoveWindow(hWnd, 0, 0, p->ResolutionX, p->ResolutionY, 1);
	FullScreen = 1;
	this->hWnd = hWnd;

	long hr;

	if ((hr = DirectDrawCreateEx(NULL, (void **)&DirectDraw, IID_IDirectDraw7, NULL)) != DD_OK)
	{
		MessageBox(NULL, "Error: DirectDrawCreateEX", "Error", 0);
	}

	if ((hr = DirectDraw->SetCooperativeLevel(hWnd, DDSCL_NORMAL)) != DD_OK)
	{
		MessageBox(NULL, "Error: SetCooperativeLevel", "Error", 0);
	}

	DDSURFACEDESC2 ddsd;
	if ((hr = DirectDraw->CreateClipper(NULL, &Clipper, NULL)) != DD_OK)
	{
		MessageBox(NULL, "Error: CreateClipper", "Error", 0);
	}

	if ((hr = DirectDraw->SetDisplayMode(p->ResolutionX, p->ResolutionY, 16, 0, 0)) != DD_OK)
	{
		MessageBox(NULL, "Error: SetDisplayMode", "Error", 0);
	}

	Clipper->SetHWnd(0, hWnd);

	memset (&ddsd, 0, sizeof(ddsd));
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	if ((hr = DirectDraw->CreateSurface(&ddsd, &Primary, NULL)) != DD_OK)
	{
		MessageBox(NULL, "Error: CreateSurface", "Error", 0);
	}

	if ((hr = Primary->SetClipper(Clipper)) != DD_OK)
	{
		MessageBox(NULL, "Error: SetClipper", "Error", 0);
	}

	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = p->ResolutionX;
	ddsd.dwHeight = p->ResolutionY;

	if ((hr = DirectDraw->CreateSurface(&ddsd, &Back, NULL)) != DD_OK)
	{
		MessageBox(NULL, "Error: CreateBackSurface", "Error", 0);
	}

	LoadSurfaces();
	GetWindowRect(hWnd, &dest);
}