RageDisplay::PixelFormat RageDisplay::FindPixelFormat( 
	int bpp, unsigned Rmask, unsigned Gmask, unsigned Bmask, unsigned Amask, bool realtime )
{
	PixelFormatDesc tmp = { bpp, { Rmask, Gmask, Bmask, Amask } };

	for(int pixfmt = 0; pixfmt < NUM_PIX_FORMATS; ++pixfmt)
	{
		const PixelFormatDesc *pf = GetPixelFormatDesc(PixelFormat(pixfmt));
		if(!SupportsTextureFormat( PixelFormat(pixfmt), realtime ))
			continue;

		if(memcmp(pf, &tmp, sizeof(tmp)))
			continue;
		return PixelFormat(pixfmt);
	}

	return NUM_PIX_FORMATS;
}