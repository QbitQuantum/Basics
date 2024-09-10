void RageDisplay_D3D::UpdateTexture( 
	unsigned uTexHandle, 
	RageSurface* img,
	int xoffset, int yoffset, int width, int height )
{
	IDirect3DTexture8* pTex = (IDirect3DTexture8*)uTexHandle;
	ASSERT( pTex != NULL );
	
	RECT rect; 
	rect.left = xoffset;
	rect.top = yoffset;
	rect.right = width - xoffset;
	rect.bottom = height - yoffset;

	D3DLOCKED_RECT lr;
	pTex->LockRect( 0, &lr, &rect, 0 );
	
	D3DSURFACE_DESC desc;
	pTex->GetLevelDesc(0, &desc);
	ASSERT( xoffset+width <= int(desc.Width) );
	ASSERT( yoffset+height <= int(desc.Height) );

	//
	// Copy bits
	//
#if defined(XBOX)
	// Xbox textures need to be swizzled
	XGSwizzleRect(
		img->pixels,	// pSource, 
		img->pitch,		// Pitch,
		NULL,	// pRect,
		lr.pBits,	// pDest,
		img->w,	// Width,
		img->h,	// Height,
		NULL,	// pPoint,
		img->format->BytesPerPixel ); //BytesPerPixel
#else
	int texpixfmt;
	for(texpixfmt = 0; texpixfmt < NUM_PIX_FORMATS; ++texpixfmt)
		if(D3DFORMATS[texpixfmt] == desc.Format) break;
	ASSERT( texpixfmt != NUM_PIX_FORMATS );

	RageSurface *Texture = CreateSurfaceFromPixfmt(PixelFormat(texpixfmt), lr.pBits, width, height, lr.Pitch);
	ASSERT( Texture );
	RageSurfaceUtils::Blit( img, Texture, width, height );

	delete Texture;
#endif

	pTex->UnlockRect( 0 );
}