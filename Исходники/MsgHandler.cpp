void CDisplayWindow::ExtractThumbnailImageInternal(ThumbnailEntry_t *pte)
{
	IExtractImage *pExtractImage = NULL;
	IShellFolder *pShellFolder = NULL;
	LPITEMIDLIST pidlParent = NULL;
	LPITEMIDLIST pidlFull = NULL;
	LPITEMIDLIST pridl = NULL;
	HBITMAP hBitmap;
	BITMAP bm;
	RECT rc;
	SIZE size;
	TCHAR szImage[MAX_PATH];
	DWORD dwPriority;
	DWORD dwFlags;
	HRESULT hr;

	m_bThumbnailExtracted = TRUE;
	m_bThumbnailExtractionFailed = TRUE;

	hr = GetIdlFromParsingName(m_ImageFile,&pidlFull);

	if(SUCCEEDED(hr))
	{
		pidlParent = ILClone(pidlFull);
		ILRemoveLastID(pidlParent);

		pridl = ILClone(ILFindLastID(pidlFull));

		hr = BindToIdl(pidlParent, IID_PPV_ARGS(&pShellFolder));

		if(SUCCEEDED(hr))
		{
			hr = GetUIObjectOf(pShellFolder, NULL, 1, (LPCITEMIDLIST *) &pridl,
				IID_PPV_ARGS(&pExtractImage));

			if(SUCCEEDED(hr))
			{
				GetClientRect(m_hDisplayWindow,&rc);

				/* First, query the thumbnail so that its actual aspect
				ratio can be calculated. */
				dwFlags = IEIFLAG_OFFLINE|IEIFLAG_QUALITY|IEIFLAG_ORIGSIZE;
				size.cx = GetRectHeight(&rc) - THUMB_HEIGHT_DELTA;
				size.cy = GetRectHeight(&rc) - THUMB_HEIGHT_DELTA;

				hr = pExtractImage->GetLocation(szImage,SIZEOF_ARRAY(szImage),
					&dwPriority,&size,32,&dwFlags);

				if(SUCCEEDED(hr))
				{
					hr = pExtractImage->Extract(&hBitmap);

					if(SUCCEEDED(hr))
					{
						/* Get bitmap information (including height and width). */
						GetObject(hBitmap,sizeof(BITMAP),&bm);

						/* Delete the original bitmap. */
						DeleteObject(hBitmap);

						/* ...now query the thumbnail again, this time adjusting
						the width of the suggested area based on the actual aspect
						ratio. */
						dwFlags = IEIFLAG_OFFLINE|IEIFLAG_QUALITY|IEIFLAG_ASPECT|IEIFLAG_ORIGSIZE;
						size.cy = GetRectHeight(&rc) - THUMB_HEIGHT_DELTA;
						size.cx = (LONG)((double)size.cy * ((double)bm.bmWidth / (double)bm.bmHeight));
						m_iImageWidth = size.cx;
						m_iImageHeight = size.cy;
						pExtractImage->GetLocation(szImage,SIZEOF_ARRAY(szImage),
							&dwPriority,&size,32,&dwFlags);
						hr = pExtractImage->Extract(&m_hbmThumbnail);

						if(SUCCEEDED(hr))
						{
							/* Check first if we've been cancelled. This might happen,
							for example, if another file is selected while the current
							thumbnail is been found. */
							EnterCriticalSection(&m_csDWThumbnails);

							if(!pte->bCancelled)
							{
								m_bThumbnailExtractionFailed = FALSE;
								InvalidateRect(m_hDisplayWindow,NULL,FALSE);
							}

							LeaveCriticalSection(&m_csDWThumbnails);
						}
						else
						{
							m_bThumbnailExtractionFailed = TRUE;
							m_hbmThumbnail = NULL;
						}
					}
				}

				pExtractImage->Release();
			}

			pShellFolder->Release();
		}

		CoTaskMemFree(pidlFull);
		CoTaskMemFree(pidlParent);
		CoTaskMemFree(pridl);
	}
}