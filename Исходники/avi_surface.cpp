void AVISurface::copyMovieFrame(const Graphics::Surface &src, Graphics::ManagedSurface &dest) {
	// WORKAROUND: Handle rare cases where frame sizes don't match the video size
	Common::Rect copyRect(0, 0, MIN(src.w, dest.w), MIN(src.h, dest.h));

	if (src.format.bytesPerPixel == 1) {
		// Paletted 8-bit, so convert to 16-bit and copy over
		const byte *palette = _decoder->getPalette();
		if (palette) {
			Graphics::Surface *s = src.convertTo(dest.format, palette);
			dest.blitFrom(*s, copyRect, Common::Point(0, 0));
			s->free();
			delete s;
		}
	} else if (src.format.bytesPerPixel == 2) {
		// Source is already 16-bit, with no alpha, so do a straight copy
		dest.blitFrom(src, copyRect, Common::Point(0, 0));
	} else {
		// Source is 32-bit which may have transparent pixels. Copy over each
		// pixel, replacing transparent pixels with the special transparency color
		byte a, r, g, b;
		assert(src.format.bytesPerPixel == 4 && dest.format.bytesPerPixel == 2);
		uint16 transPixel = _videoSurface->getTransparencyColor();

		for (uint y = 0; y < MIN(src.h, dest.h); ++y) {
			const uint32 *pSrc = (const uint32 *)src.getBasePtr(0, y);
			uint16 *pDest = (uint16 *)dest.getBasePtr(0, y);

			for (uint x = 0; x < MIN(src.w, dest.w); ++x, ++pSrc, ++pDest) {
				src.format.colorToARGB(*pSrc, a, r, g, b);
				assert(a == 0 || a == 0xff);

				*pDest = (a == 0) ? transPixel : dest.format.RGBToColor(r, g, b);
			}
		}
	}
}