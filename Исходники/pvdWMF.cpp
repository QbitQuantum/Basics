BOOL __stdcall pvdFileOpen2(void *pContext, const wchar_t *pFileName, INT64 lFileSize, const BYTE *pBuf, UINT32 lBuf, pvdInfoImage2 *pImageInfo)
{
	_ASSERTE(pImageInfo->cbSize >= sizeof(pvdInfoImage2));

	WmfContext *pw = (WmfContext*)CALLOC(sizeof(WmfContext));
	if (!pw) {
		pImageInfo->nErrNumber = PWE_NOT_ENOUGH_MEMORY;
		return FALSE;
	}
	//pw->h = GetEnhMetaFile ( pFileName+4 );

	const wchar_t *p = GetExtension(pFileName);
	if (!p) {
		pImageInfo->nErrNumber = PWE_NO_EXTENSION;
		return FALSE;
	}

	pImageInfo->nErrNumber = PWE_WIN32_ERROR; // заранее

	//if (pImageInfo->PreferredSize.cx && pImageInfo->PreferredSize.cy) {
	//	pw->PreferredSize = pImageInfo->PreferredSize;
	//} else {
	pw->PreferredSize.cx = 1000; pw->PreferredSize.cy = 1000;
	//}

	// First try to read it as an enhanced metafile
	// If it works, simply return the handle
	pw->h = SetEnhMetaFileBits(lBuf, pBuf);
	gnLastWin32Error = GetLastError();

	if (!pw->h) {
		pw->h = GetEnhMetaFile( pFileName );
		gnLastWin32Error = GetLastError();
	}

	if (!pw->h) {
		HMETAFILE		hOld;
		DWORD			dwSize;
		LPBYTE			pBits;
		METAFILEPICT	mp;
		HDC				hDC;

		if( (hOld = GetMetaFile( pFileName )) != NULL )
		{
			// Ok, it is a 16bit windows metafile
			// How big are the bits?
			if( (dwSize = GetMetaFileBitsEx( hOld, 0, NULL )) == 0 )
			{
				gnLastWin32Error = GetLastError();
				DeleteMetaFile( hOld );
				//MessageBox( hWndParent, "Failed to Get MetaFile Bits Size", "Error Reading MetaFile", MB_OK );
			} else {
				// Allocate that much memory
				if( (pBits = (LPBYTE)CALLOC( dwSize )) == NULL )
				{
					pImageInfo->nErrNumber = PWE_NOT_ENOUGH_MEMORY;
					gnLastWin32Error = GetLastError();
					DeleteMetaFile( hOld );
					//MessageBox( hWndParent, "Failed to Allocate Memory for Metafile Bits", "Error Reading MetaFile", MB_OK );
					//return NULL;
				} else {
					// Get the metafile bits
					if( GetMetaFileBitsEx( hOld, dwSize, pBits ) == 0 )
					{
						gnLastWin32Error = GetLastError();
						FREE( pBits );
						DeleteMetaFile( hOld );
						//MessageBox( hWndParent, "Failed to Get MetaFile Bits", "Error Reading MetaFile", MB_OK );
						//return NULL;
					} else {
						// Fill out a METAFILEPICT structure
						mp.mm = MM_ANISOTROPIC;
						mp.xExt = 1000;
						mp.yExt = 1000;
						mp.hMF = NULL;
						// Get a reference DC
						hDC = GetDC( NULL );
						// Make an enhanced metafile from the windows metafile
						pw->h = SetWinMetaFileBits( dwSize, pBits, hDC, &mp );
						gnLastWin32Error = GetLastError();
						// Clean up
						ReleaseDC( NULL, hDC );
						DeleteMetaFile( hOld );
						FREE( pBits );
					}
				}
			}
		}
	}

	if (!pw->h) {
		DWORD			dwSize = lBuf;
		LPBYTE			pBits = (LPBYTE)pBuf;
		METAFILEPICT	mp;
		HDC				hDC;

		// Is it a placeable metafile? (check the key)
		if( ((PAPMHEADER)pBits)->dwKey != 0x9ac6cdd7l )
		{
			// Not a metafile that we know how to recognise - bail out
			//MessageBox( hWndParent, "Not a Valid Metafile", szFileName, MB_OK );
			//return NULL;
			pImageInfo->nErrNumber = PWE_NOT_VALID_METAFILE;
		} else {
			// Ok, its a placeable metafile
			// Fill out a METAFILEPICT structure
			mp.mm = MM_ANISOTROPIC;
			mp.xExt = ((PAPMHEADER)pBits)->bbox.Right - ((PAPMHEADER)pBits)->bbox.Left;
			mp.xExt = ( mp.xExt * 2540l ) / (DWORD)(((PAPMHEADER)pBits)->wInch);
			mp.yExt = ((PAPMHEADER)pBits)->bbox.Bottom - ((PAPMHEADER)pBits)->bbox.Top;
			mp.yExt = ( mp.yExt * 2540l ) / (DWORD)(((PAPMHEADER)pBits)->wInch);
			mp.hMF = NULL;
			// Get a reference DC
			hDC = GetDC( NULL );
			// Create an enhanced metafile from the bits
			pw->h = SetWinMetaFileBits( dwSize, &(pBits[sizeof(APMHEADER)]), hDC, &mp );
			gnLastWin32Error = GetLastError();
			// Clean up
			ReleaseDC( NULL, hDC );
			//free( pBits );
			//if( hTemp == NULL )
			//	MessageBox( hWndParent, "Failed to Create MetaFile from Bits", "Error Reading MetaFile", MB_OK );
			//return hTemp;
		}
	}

	//if (pw->h) {
	//	//pw->hCompDC = CreateCompatibleDC(NULL);
	//	pw->mfp.mm = MM_ISOTROPIC;
	//	pw->mfp.xExt = pw->PreferredSize.cx;
	//	pw->mfp.yExt = pw->PreferredSize.cy;
	//	pw->h = (HENHMETAFILE)SetMetaFileBitsEx (lBuf, pBuf);
	//	gnLastWin32Error = GetLastError();
	//	pw->h = SetWinMetaFileBits(lBuf, pBuf, NULL, NULL); //pw->hCompDC, &pw->mfp);
	//	gnLastWin32Error = GetLastError();
	//}

	if (!pw->h) {
		//gnLastWin32Error = GetLastError(); -- уже
		FREE(pw);
		return FALSE;
	}

	pw->AddRef();
	_ASSERTE(pw->nRefCount == 1);

	ENHMETAHEADER	emh = {0};
	DWORD			PixelsX, PixelsY, MMX, MMY;
	emh.nSize = sizeof(ENHMETAHEADER);
	if( GetEnhMetaFileHeader( pw->h, sizeof( ENHMETAHEADER ), &emh ) )
	{
		// Get the characteristics of the output device
		HDC hDC = GetDC(NULL);
		PixelsX = GetDeviceCaps( hDC, HORZRES );
		PixelsY = GetDeviceCaps( hDC, VERTRES );
		MMX = GetDeviceCaps( hDC, HORZSIZE ) * 100;
		MMY = GetDeviceCaps( hDC, VERTSIZE ) * 100;
		ReleaseDC(NULL, hDC);

		// Calculate the rect in which to draw the metafile based on the
		// intended size and the current output device resolution
		// Remember that the intended size is given in 0.01mm units, so
		// convert those to device units on the target device
		//pw->PreferredSize.cx = (int)((float)(emh.rclFrame.right - emh.rclFrame.left) * PixelsX / (MMX));
		//pw->PreferredSize.cy = (int)((float)(emh.rclFrame.bottom - emh.rclFrame.top) * PixelsY / (MMY));
		pw->PreferredSize.cx = ip.MulDivI32((emh.rclFrame.right - emh.rclFrame.left), PixelsX, MMX);
		pw->PreferredSize.cy = ip.MulDivI32((emh.rclFrame.bottom - emh.rclFrame.top), PixelsY, MMY);
		_ASSERTE(pw->PreferredSize.cx>0 && pw->PreferredSize.cy>0);
		if (pw->PreferredSize.cx < 0) pw->PreferredSize.cx = -pw->PreferredSize.cx;
		if (pw->PreferredSize.cy < 0) pw->PreferredSize.cy = -pw->PreferredSize.cy;
	}

	pImageInfo->pImageContext = pw;
	pImageInfo->nPages = 1;
	pImageInfo->Flags = 0;
	pImageInfo->pFormatName = L"WMF";
	pImageInfo->pCompression = NULL;
	pImageInfo->pComments = NULL;

	return TRUE;
}