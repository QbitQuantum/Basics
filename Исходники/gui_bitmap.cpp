HBITMAP createGrayBitmap( HBITMAP srcBmp, COLORREF transparent )
{
	HBITMAP destBmp = NULL;

	BITMAP bitmap;
	HDC dcMem = NULL, dcSrc = NULL;
	HBITMAP bmpOldSrc = NULL, bmpOldMem = NULL;

	if( ( dcMem = CreateCompatibleDC( NULL ) ) && ( dcSrc = CreateCompatibleDC( NULL ) ) )
	{
		GetObject( srcBmp, sizeof( bitmap ), &bitmap );

		if( ( destBmp = CreateBitmap( bitmap.bmWidth, bitmap.bmHeight,
			bitmap.bmPlanes, bitmap.bmBitsPixel, NULL ) ) )
		{
			bmpOldMem = (HBITMAP)SelectObject( dcMem, destBmp );
			bmpOldSrc = (HBITMAP)SelectObject( dcSrc, srcBmp );

			if( bmpOldMem && bmpOldSrc )
			{
				BitBlt( dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight,
					dcSrc, 0, 0, SRCCOPY );
				for( int i = 0; i < bitmap.bmWidth; ++i )
					for( int j = 0; j < bitmap.bmHeight; ++j )
					{
						COLORREF color = GetPixel( dcMem, i, j );
						if( color != transparent )
						{
							double grayScale = GetRValue( color ) * 0.3 +
								GetGValue( color ) * 0.59 +
								GetBValue( color ) * 0.11;
							grayScale = grayScale / 2 + 128;
							color = RGB( grayScale, grayScale, grayScale );
							SetPixel( dcMem, i, j, color );
						}
					}
				SelectObject( dcSrc, bmpOldSrc );
				SelectObject( dcMem, bmpOldMem );
			}
		}
	}

	if( dcMem )	DeleteDC( dcMem );
	if( dcSrc )	DeleteDC( dcSrc );
	return destBmp;
}