bool GSDevice7::Create(HWND hWnd, bool vsync)
{
	if(!__super::Create(hWnd, vsync))
	{
		return false;
	}

	if(FAILED(DirectDrawCreateEx(NULL, (VOID**)&m_dd, IID_IDirectDraw7, NULL)))
	{
		return false;
	}

	// TODO: fullscreen

	if(FAILED(m_dd->SetCooperativeLevel(hWnd, DDSCL_NORMAL)))
	{
		return false;
	}

    DDSURFACEDESC2 desc;

	memset(&desc, 0, sizeof(desc));

	desc.dwSize = sizeof(desc);
    desc.dwFlags = DDSD_CAPS;
    desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
    
	if(FAILED(m_dd->CreateSurface(&desc, &m_primary, NULL)))
	{
		return false;
	}

	CComPtr<IDirectDrawClipper> clipper;

    if(FAILED(m_dd->CreateClipper(0, &clipper, NULL))
	|| FAILED(clipper->SetHWnd(0, hWnd))
	|| FAILED(m_primary->SetClipper(clipper)))
	{
		return false;
	}

	Reset(1, 1, true);

	return true;
}