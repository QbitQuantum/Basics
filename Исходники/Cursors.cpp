void MystCursorManager::setCursor(uint16 id) {
	// Zero means empty cursor
	if (id == 0) {
		static const byte emptyCursor[4] = { 0, 0, 0, 0 };
		CursorMan.replaceCursor(&emptyCursor, 2, 2, 0, 0, 0);
		return;
	}

	Common::SeekableReadStream *clrcStream = _vm->getResource(ID_CLRC, id);
	uint16 hotspotX = clrcStream->readUint16LE();
	uint16 hotspotY = clrcStream->readUint16LE();
	delete clrcStream;

	// Both Myst and Myst ME use the "MystBitmap" format for cursor images.
	MohawkSurface *mhkSurface = _vm->_gfx->findImage(id);
	Graphics::Surface *surface = mhkSurface->getSurface();

	// Myst ME stores some cursors as 24bpp images instead of 8bpp
	if (surface->format.bytesPerPixel == 1) {
		// The transparent color is almost always 255, except for the main cursor (100)
		// in the D'ni archive, where it is 0.
		// Using the color of the first pixel as the transparent color for the main cursor always works.
		byte transparentColor;
		if (id == kDefaultMystCursor) {
			transparentColor = ((byte *)surface->getPixels())[0];
		} else {
			transparentColor = 255;
		}
		CursorMan.replaceCursor(surface->getPixels(), surface->w, surface->h, hotspotX, hotspotY, transparentColor);

		// We're using the screen palette for the original game, but we need
		// to use this for any 8bpp cursor in ME.
		if (_vm->getFeatures() & GF_ME)
			CursorMan.replaceCursorPalette(mhkSurface->getPalette(), 0, 256);
	} else {
		Graphics::PixelFormat pixelFormat = g_system->getScreenFormat();
		CursorMan.replaceCursor(surface->getPixels(), surface->w, surface->h, hotspotX, hotspotY, pixelFormat.RGBToColor(255, 255, 255), false, &pixelFormat);
	}
}