/******************************************************************
*  Creates a DIB Section from the converted IWICBitmapSource      *
******************************************************************/
HRESULT UserImageFactory_CreateDIBSectionFromBitmapSource( IWICBitmapSource *pToRenderBitmapSource, HBITMAP& hBitmapInOut )
{
	HRESULT hr = S_OK;

	UINT nWidth = 0;
	UINT nHeight = 0;

	void *pvImageBits = NULL;
	BITMAPINFO bminfo;
	HWND hWindow = NULL;
	HDC hdcScreen = NULL;

	WICPixelFormatGUID pixelFormat;

	UINT cbStride = 0;
	UINT cbImage = 0;


	// Check BitmapSource format
	//hr = IWICBitmapSource_GetPixelFormat( pToRenderBitmapSource, &pixelFormat );
	hr = pToRenderBitmapSource->GetPixelFormat( &pixelFormat );

	if( SUCCEEDED( hr ) )
	{
		//hr = IWICBitmapSource_GetSize( pToRenderBitmapSource, &nWidth, &nHeight );
		hr = pToRenderBitmapSource->GetSize( &nWidth, &nHeight );
	}

	// Create a DIB section based on Bitmap Info
	// BITMAPINFO Struct must first be setup before a DIB can be created.
	// Note that the height is negative for top-down bitmaps
	if( SUCCEEDED( hr ) )
	{
		ZeroMemory( &bminfo, sizeof( bminfo ) );
		bminfo.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
		bminfo.bmiHeader.biWidth = nWidth;
		bminfo.bmiHeader.biHeight = -(LONG)nHeight;
		bminfo.bmiHeader.biPlanes = 1;
		bminfo.bmiHeader.biBitCount = 32;
		bminfo.bmiHeader.biCompression = BI_RGB;

		hWindow = GetActiveWindow();
		while( GetParent( hWindow ) != NULL )
			hWindow = GetParent( hWindow );

		// Get a DC for the full screen
		hdcScreen = GetDC( hWindow );
		hr = hdcScreen ? S_OK : E_FAIL;

		// Release the previously allocated bitmap 
		if( SUCCEEDED( hr ) )
		{
			if( hBitmapInOut )
			{
				DeleteObject( hBitmapInOut );
			}

			//	TBD: check this. As a handle this should just be as-is, right?
			hBitmapInOut = CreateDIBSection( hdcScreen, &bminfo, DIB_RGB_COLORS, &pvImageBits, NULL, 0 );

			ReleaseDC( NULL, hdcScreen );

			hr = hBitmapInOut ? S_OK : E_FAIL;
		}
	}

	if( SUCCEEDED( hr ) )
	{
		// Size of a scan line represented in bytes: 4 bytes each pixel
		hr = UIntMult( nWidth, sizeof( ARGB ), &cbStride );
	}

	if( SUCCEEDED( hr ) )
	{
		// Size of the image, represented in bytes
		hr = UIntMult( cbStride, nHeight, &cbImage );
	}

	// Extract the image into the HBITMAP    
	if( SUCCEEDED( hr ) )
	{
		hr = pToRenderBitmapSource->CopyPixels(
			//hr = IWICBitmapSource_CopyPixels( pToRenderBitmapSource,
			NULL,
			cbStride,
			cbImage,
			(BYTE*)pvImageBits );
	}

	// Image Extraction failed, clear allocated memory
	if( FAILED( hr ) )
	{
		DeleteObject( hBitmapInOut );
		hBitmapInOut = NULL;
	}

	return hr;
}