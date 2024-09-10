//+------------------------------------------------------------------------
//
//  Member:     COffScreenContext::CreateDDSurface
//
//  Synopsis:   Create a DD surface with the specified dimensions and palette.
//
//-------------------------------------------------------------------------
BOOL COffScreenContext::CreateDDSurface(long width, long height, HPALETTE hpal)
{
	HRESULT hr = InitSurface();
	if(FAILED(hr))
	{
		return FALSE;
	}

	DDPIXELFORMAT* pPF = PixelFormat(_hdcWnd, _cBitsPixel);
	if(!pPF)
	{
		return FALSE;
	}

	DDSURFACEDESC ddsd;

	ddsd.dwSize = sizeof(ddsd);
	ddsd.ddpfPixelFormat = *pPF;
	ddsd.dwFlags = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH|DDSD_PIXELFORMAT;
	ddsd.ddsCaps.dwCaps = DDSCAPS_DATAEXCHANGE|DDSCAPS_OWNDC;
	if(_fUse3D)
	{
		ddsd.ddsCaps.dwCaps |= DDSCAPS_3DDEVICE;
	}
	ddsd.dwWidth = width;
	ddsd.dwHeight = height;
	hr = g_pDirectDraw->CreateSurface(&ddsd, &_pDDSurface, NULL);
	if(FAILED(hr))
	{
		return FALSE;
	}

	// set color table
	if(_cBitsPixel <= 8)
	{
		IDirectDrawPalette*	pDDPal;
		PALETTEENTRY*		pPal;
		PALETTEENTRY		pal256[256];
		long				cEntries;
		DWORD				pcaps;

		if(_cBitsPixel == 8)
		{
			cEntries = GetPaletteEntries(hpal, 0, 256, pal256);
			pPal = pal256;
			pcaps = DDPCAPS_8BIT;
		}
		else if(_cBitsPixel == 4)
		{
			cEntries = 16;
			pPal = g_pal16;
			pcaps = DDPCAPS_4BIT;
		}
		else if(_cBitsPixel == 1)
		{
			cEntries = 2;
			pPal = g_pal2;
			pcaps = DDPCAPS_1BIT;
		}
		else
		{
			Assert(0 && "invalid cBitsPerPixel");
			return FALSE;
		}

		// create and initialize a new DD palette
		hr = g_pDirectDraw->CreatePalette(pcaps|DDPCAPS_INITIALIZE, pPal, &pDDPal, NULL);
		if(SUCCEEDED(hr))
		{
			// attach the DD palette to the DD surface
			hr = _pDDSurface->SetPalette(pDDPal);
			pDDPal->Release();
		}
		if(FAILED(hr))
		{
			return FALSE;
		}
	}

	hr = _pDDSurface->GetDC(&_hdcMem);
	return SUCCEEDED(hr);
}