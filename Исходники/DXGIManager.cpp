HRESULT DXGIManager::GetOutputBits(BYTE* pBits, RECT& rcDest)
{
	HRESULT hr = S_OK;

	DWORD dwDestWidth = rcDest.right - rcDest.left;
	DWORD dwDestHeight = rcDest.bottom - rcDest.top;

	RECT rcOutput;
	hr = GetOutputRect(rcOutput);
	if( FAILED(hr) )
		return hr;

	DWORD dwOutputWidth = rcOutput.right - rcOutput.left;
	DWORD dwOutputHeight = rcOutput.bottom - rcOutput.top;

	BYTE* pBuf = NULL;
	if(rcOutput.right > (LONG)dwDestWidth || rcOutput.bottom > (LONG)dwDestHeight)
	{
		// Output is larger than pBits dimensions
		if(!m_pBuf || !EqualRect(&m_rcCurrentOutput, &rcOutput))
		{
			DWORD dwBufSize = dwOutputWidth*dwOutputHeight*4;

			if(m_pBuf)
			{
				delete [] m_pBuf;
				m_pBuf = NULL;
			}

			m_pBuf = new BYTE[dwBufSize];

			CopyRect(&m_rcCurrentOutput, &rcOutput);
		}

		pBuf = m_pBuf;
	}
	else
	{
		// Output is smaller than pBits dimensions
		pBuf = pBits;
		dwOutputWidth = dwDestWidth;
		dwOutputHeight = dwDestHeight;
	}

	vector<DXGIOutputDuplication> vOutputs = GetOutputDuplication();

	for(vector<DXGIOutputDuplication>::iterator iter = vOutputs.begin();
		iter != vOutputs.end();
		iter++)
	{
		DXGIOutputDuplication& out = *iter;
	
		DXGI_OUTPUT_DESC outDesc;
		out.GetDesc(outDesc);
		RECT rcOutCoords = outDesc.DesktopCoordinates;

		CComPtr<IDXGISurface1> spDXGISurface1;
		hr = out.AcquireNextFrame(&spDXGISurface1, m_pDXGIPointer);
		if( FAILED(hr) )
			break;

		DXGI_MAPPED_RECT map;
		spDXGISurface1->Map(&map, DXGI_MAP_READ);

		RECT rcDesktop = outDesc.DesktopCoordinates;
		DWORD dwWidth = rcDesktop.right - rcDesktop.left;
		DWORD dwHeight = rcDesktop.bottom - rcDesktop.top;

		OffsetRect(&rcDesktop, -rcOutput.left, -rcOutput.top);

		DWORD dwMapPitchPixels = map.Pitch/4;

		switch(outDesc.Rotation)
		{
			case DXGI_MODE_ROTATION_IDENTITY:
				{
					// Just copying
					DWORD dwStripe = dwWidth*4;
					for(unsigned int i=0; i<dwHeight; i++)
					{
						memcpy_s(pBuf + (rcDesktop.left + (i + rcDesktop.top)*dwOutputWidth)*4, dwStripe, map.pBits + i*map.Pitch, dwStripe);
					}
				}
				break;
			case DXGI_MODE_ROTATION_ROTATE90:
				{
					// Rotating at 90 degrees
					DWORD* pSrc = (DWORD*)map.pBits;
					DWORD* pDst = (DWORD*)pBuf;
					for(unsigned int j=0; j<dwHeight; j++)
					{
						for(unsigned int i=0; i<dwWidth; i++)
						{
							*(pDst + (rcDesktop.left + (j + rcDesktop.top)*dwOutputWidth) + i) = *(pSrc + j + dwMapPitchPixels*(dwWidth - i - 1));
						}
					}
				}
				break;
			case DXGI_MODE_ROTATION_ROTATE180:
				{
					// Rotating at 180 degrees
					DWORD* pSrc = (DWORD*)map.pBits;
					DWORD* pDst = (DWORD*)pBuf;
					for(unsigned int j=0; j<dwHeight; j++)
					{
						for(unsigned int i=0; i<dwWidth; i++)
						{
							*(pDst + (rcDesktop.left + (j + rcDesktop.top)*dwOutputWidth) + i) = *(pSrc + (dwWidth - i - 1) + dwMapPitchPixels*(dwHeight - j - 1));
						}
					}
				}
				break;
			case DXGI_MODE_ROTATION_ROTATE270:
				{
					// Rotating at 270 degrees
					DWORD* pSrc = (DWORD*)map.pBits;
					DWORD* pDst = (DWORD*)pBuf;
					for(unsigned int j=0; j<dwHeight; j++)
					{
						for(unsigned int i=0; i<dwWidth; i++)
						{
							*(pDst + (rcDesktop.left + (j + rcDesktop.top)*dwOutputWidth) + i) = *(pSrc + (dwHeight - j - 1) + dwMapPitchPixels*i);
						}
					}
				}
				break;
		}
		
		spDXGISurface1->Unmap();

		out.ReleaseFrame();
	}

	if(FAILED(hr))
		return hr;

	// Now pBits have the desktop. Let's paint mouse pointer!
	if(pBuf != pBits)
	{
		DrawMousePointer(pBuf, rcOutput, rcOutput);
	}
	else
	{
		DrawMousePointer(pBuf, rcOutput, rcDest);
	}

	// We have the pBuf filled with current desktop/monitor image.
	if(pBuf != pBits)
	{
		// pBuf contains the image that should be resized
		CComPtr<IWICBitmap> spBitmap = NULL;
		hr = m_spWICFactory->CreateBitmapFromMemory(dwOutputWidth, dwOutputHeight, GUID_WICPixelFormat32bppBGRA, dwOutputWidth*4, dwOutputWidth*dwOutputHeight*4, (BYTE*)pBuf, &spBitmap);
		if( FAILED(hr) )
			return hr;

		CComPtr<IWICBitmapScaler> spBitmapScaler = NULL;
		hr = m_spWICFactory->CreateBitmapScaler(&spBitmapScaler);
		if( FAILED(hr) )
			return hr;
		
		dwOutputWidth = rcOutput.right - rcOutput.left;
		dwOutputHeight = rcOutput.bottom - rcOutput.top;

		double aspect = (double)dwOutputWidth/(double)dwOutputHeight;

		DWORD scaledWidth = dwDestWidth;
		DWORD scaledHeight = dwDestHeight;

		if(aspect > 1)
		{
			scaledWidth = dwDestWidth;
			scaledHeight = (DWORD)(dwDestWidth/aspect);
		}
		else
		{
			scaledWidth = (DWORD)(aspect*dwDestHeight);
			scaledHeight = dwDestHeight;
		}

		spBitmapScaler->Initialize(
			spBitmap, scaledWidth, scaledHeight, WICBitmapInterpolationModeNearestNeighbor);

		spBitmapScaler->CopyPixels(NULL, scaledWidth*4, dwDestWidth*dwDestHeight*4, pBits);
	}
	return hr;
}