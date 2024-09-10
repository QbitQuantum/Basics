HANDLE CViewBitmap::CreateDIB(int *pbmData)
{
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
// create DIB header from our BITMAP header
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
 BITMAPINFOHEADER bi;
 memset( &bi, 0, sizeof( bi ) );
 bi.biSize = sizeof( BITMAPINFOHEADER );
 bi.biPlanes = 1;
 bi.biCompression = BI_RGB;
// get and store dimensions of bitmap
 BITMAP bm;
 GetObject( sizeof( bm ),( LPSTR )&bm );
 bi.biWidth = bm.bmWidth ;
 bi.biHeight = bm.bmHeight;
// get number of bits required per pixel
 int bits = bm.bmPlanes * bm.bmBitsPixel;
 if ( bits <= 1 )
 bi.biBitCount = 1;
 else if ( bits <= 4 )
 bi.biBitCount = 4;
 else if ( bits <= 8 )
 bi.biBitCount = 8;
 else
 bi.biBitCount = 24;
// calculate color table size
 int biColorSize = 0;
 if ( bi.biBitCount!=24)
	 biColorSize = (1 << bi.biBitCount );
 biColorSize*=sizeof( RGBQUAD);
// calculate picture data size
 bi.biSizeImage = ( DWORD )bm.bmWidth * bi.biBitCount; // bits per row
 bi.biSizeImage = ( ( ( bi.biSizeImage ) + 31 ) / 32 ) * 4;
// DWORD aligned 
 bi.biSizeImage*=bm.bmHeight; // bytes required for whole bitmap
// return size to caler in case they want to save to file
 if ( pbmData )
 *pbmData = bi.biSize + biColorSize;
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
// get DIB color table and picture data
/// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
// allocate a hunk of memory to hold header, color table and picture data
 HANDLE hDIB = GlobalAlloc( GHND, bi.biSize + biColorSize +bi.biSizeImage );
// get a memory pointer to this hunk by locking it
 LPBITMAPINFOHEADER lpbi = ( LPBITMAPINFOHEADER )GlobalLock( hDIB );
// copy our header structure into hunk
 *lpbi = bi;
// get a device context and select our bitmap's palette into it
 CDC dc;
 dc.Attach( ::GetDC( NULL ) );
 CPalette *pPal = dc.SelectPalette( m_pPalette,FALSE );
 dc.RealizePalette() ;
// load our memory hunk with the color table and picture data
 GetDIBits( dc.m_hDC, ( HBITMAP )m_hObject, 0, ( UINT )bi.biHeight,( LPSTR )lpbi + ( WORD )lpbi -> biSize + biColorSize,( LPBITMAPINFO )lpbi, DIB_RGB_COLORS );
// clean up
 GlobalUnlock( hDIB );
 dc.SelectPalette( pPal,FALSE );
 dc.RealizePalette();
// return handle to the DIB
 return hDIB;
}