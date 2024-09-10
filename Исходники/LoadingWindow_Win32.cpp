/* Load a file into a GDI surface. */
HBITMAP LoadWin32Surface( CString fn )
{
	CString error;
	RageSurface *s = RageSurfaceUtils::LoadFile( fn, error );
	if( s == NULL )
		return NULL;

	RageSurfaceUtils::ConvertSurface( s, s->w, s->h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0 );

	HBITMAP bitmap = CreateCompatibleBitmap( GetDC(NULL), s->w, s->h );
	ASSERT( bitmap );

	HDC BitmapDC = CreateCompatibleDC( GetDC(NULL) );
	SelectObject( BitmapDC, bitmap );

	/* This is silly, but simple.  We only do this once, on a small image. */
	for( int y = 0; y < s->h; ++y )
	{
		unsigned const char *line = ((unsigned char *) s->pixels) + (y * s->pitch);
		for( int x = 0; x < s->w; ++x )
		{
			unsigned const char *data = line + (x*s->format->BytesPerPixel);
			
			SetPixelV( BitmapDC, x, y, RGB( data[3], data[2], data[1] ) );
		}
	}

	SelectObject( BitmapDC, NULL );
	DeleteObject( BitmapDC );

	delete s;
	return bitmap;
}