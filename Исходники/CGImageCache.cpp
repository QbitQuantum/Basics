ALERROR CGImageCache::LoadBitmapImage (DWORD dwImageUNID, DWORD dwTransparencyUNID, DWORD dwDepthUNID, int *retiIndex)

//	LoadBitmapImage
//
//	Loads an image into the cache. This should only be called once
//	when the cache is initialized or when an image is first requested.

	{
	ALERROR error;
	HRESULT result;
	HBITMAP hBitmap;
	DDSURFACEDESC ddsd;
	BITMAP bm;
	LPDIRECTDRAWSURFACE7 pSurface;
	HDC hDC, hBitmapDC;
	HBITMAP hOldBitmap;
	HBITMAP hDepth;
	CGChannelStruct *pTrans = NULL;

	//	Load the bitmap from the image db

	if (error = m_pMediaDb->LoadBitmap(dwImageUNID, &hBitmap))
		return error;

	//	Get some info from bitmap

	GetObject(hBitmap, sizeof(bm), &bm);

	//	Create a surface of the proper size

	utlMemSet(&ddsd, sizeof(ddsd), 0);
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.dwWidth = bm.bmWidth;
	ddsd.dwHeight = bm.bmHeight;

	if (m_pScreen->GetDD()->CreateSurface(&ddsd, &pSurface, NULL) != DD_OK)
		{
		DeleteObject(hBitmap);
		return ERR_FAIL;
		}

	if (result = pSurface->GetDC(&hDC) != DD_OK)
		{
		pSurface->Release();
		DeleteObject(hBitmap);
		return ERR_FAIL;
		}

	//	Blt the bitmap onto the surface

	hBitmapDC = CreateCompatibleDC(NULL);
	hOldBitmap = (HBITMAP)SelectObject(hBitmapDC, hBitmap);

	BitBlt(hDC,
			0,
			0,
			bm.bmWidth,
			bm.bmHeight,
			hBitmapDC,
			0,
			0,
			SRCCOPY);

	SelectObject(hBitmapDC, hOldBitmap);
	DeleteDC(hBitmapDC);
	DeleteObject(hBitmap);

	pSurface->ReleaseDC(hDC);

	//	Load the transparency bitmap

	if (dwTransparencyUNID)
		{
		HBITMAP hTransparency;

		if (error = m_pMediaDb->LoadBitmap(dwTransparencyUNID, &hTransparency))
			{
			pSurface->Release();
			return error;
			}

		//	Convert this bitmap into an 8-bit map

		error = ConvertToChannel(hTransparency, &pTrans);
		DeleteObject(hTransparency);
		if (error)
			{
			pSurface->Release();
			return error;
			}
		}

	//	Load the depth bitmap

	if (dwDepthUNID)
		{
		if (error = m_pMediaDb->LoadBitmap(dwDepthUNID, &hDepth))
			{
			if (pTrans)
				MemFree(pTrans);
			pSurface->Release();
			return error;
			}
		}
	else
		hDepth = NULL;

	//	Add the surface to our cache

	if (error = AddImage(dwImageUNID, pSurface, pTrans, hDepth, retiIndex))
		{
		if (hDepth)
			DeleteObject(hDepth);
		if (pTrans)
			MemFree(pTrans);
		pSurface->Release();
		return ERR_FAIL;
		}

	return NOERROR;
	}