	const bool mxSurfacePainter::setPixel(int x, int y, Uint32 color)
	{
		if(locked == false) return false;

		setpixel(pbuf, x, y, color, surface->getSurface()->format->BytesPerPixel, surface->getSurface()->pitch);

		return true;

	}