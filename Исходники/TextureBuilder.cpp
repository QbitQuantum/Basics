void TextureBuilder::PrepareSurface()
{
	if (m_prepared) return;

	if (!m_surface && m_filename.length() > 0)
		LoadSurface();

	TextureFormat targetTextureFormat;
	SDL_PixelFormat *targetPixelFormat;
	bool needConvert = !GetTargetFormat(m_surface->format, &targetTextureFormat, &targetPixelFormat, m_forceRGBA);

	if (needConvert) {
		SDL_Surface *s = SDL_ConvertSurface(m_surface, targetPixelFormat, SDL_SWSURFACE);
		SDL_FreeSurface(m_surface);
		m_surface = s;
	}

	unsigned int virtualWidth, actualWidth, virtualHeight, actualHeight;
	virtualWidth = actualWidth = m_surface->w;
	virtualHeight = actualHeight = m_surface->h;

	if (m_potExtend) {
		// extend to power-of-two if necessary
		actualWidth = ceil_pow2(m_surface->w);
		actualHeight = ceil_pow2(m_surface->h);
		if (actualWidth != virtualWidth || actualHeight != virtualHeight) {
			SDL_Surface *s = SDL_CreateRGBSurface(SDL_SWSURFACE, actualWidth, actualHeight, targetPixelFormat->BitsPerPixel,
				targetPixelFormat->Rmask, targetPixelFormat->Gmask, targetPixelFormat->Bmask, targetPixelFormat->Amask);

			SDL_SetAlpha(m_surface, 0, 0);
			SDL_SetAlpha(s, 0, 0);
			SDL_BlitSurface(m_surface, 0, s, 0);

			SDL_FreeSurface(m_surface);
			m_surface = s;
		}
	}

	else if (m_filename.length() > 0) {
		// power-of-to check
		unsigned long width = ceil_pow2(m_surface->w);
		unsigned long height = ceil_pow2(m_surface->h);

		if (width != virtualWidth || height != virtualHeight)
			fprintf(stderr, "WARNING: texture '%s' is not power-of-two and may not display correctly\n", m_filename.c_str());
	}

	m_descriptor = TextureDescriptor(
		targetTextureFormat,
		vector2f(actualWidth,actualHeight),
		vector2f(float(virtualWidth)/float(actualWidth),float(virtualHeight)/float(actualHeight)),
		m_sampleMode, m_generateMipmaps);
	
	m_prepared = true;
}