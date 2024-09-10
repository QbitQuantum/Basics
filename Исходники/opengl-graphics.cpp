void OpenGLGraphicsManager::setMouseCursor(const void *buf, uint w, uint h, int hotspotX, int hotspotY, uint32 keycolor, bool dontScale, const Graphics::PixelFormat *format) {
	Graphics::PixelFormat inputFormat;
#ifdef USE_RGB_COLOR
	if (format) {
		inputFormat = *format;
	} else {
		inputFormat = Graphics::PixelFormat::createFormatCLUT8();
	}
#else
	inputFormat = Graphics::PixelFormat::createFormatCLUT8();
#endif

	// In case the color format has changed we will need to create the texture.
	if (!_cursor || _cursor->getFormat() != inputFormat) {
		delete _cursor;
		_cursor = nullptr;

		GLenum glIntFormat, glFormat, glType;

		Graphics::PixelFormat textureFormat;
		if (inputFormat.bytesPerPixel == 1 || (inputFormat.aBits() && getGLPixelFormat(inputFormat, glIntFormat, glFormat, glType))) {
			// There is two cases when we can use the cursor format directly.
			// The first is when it's CLUT8, here color key handling can
			// always be applied because we use the alpha channel of
			// _defaultFormatAlpha for that.
			// The other is when the input format has alpha bits and
			// furthermore is directly supported.
			textureFormat = inputFormat;
		} else {
			textureFormat = _defaultFormatAlpha;
		}
		_cursor = createTexture(textureFormat, true);
		assert(_cursor);
		_cursor->enableLinearFiltering(_currentState.graphicsMode == GFX_LINEAR);
	}

	_cursorKeyColor = keycolor;
	_cursorHotspotX = hotspotX;
	_cursorHotspotY = hotspotY;
	_cursorDontScale = dontScale;

	_cursor->allocate(w, h);
	if (inputFormat.bytesPerPixel == 1) {
		// For CLUT8 cursors we can simply copy the input data into the
		// texture.
		_cursor->copyRectToTexture(0, 0, w, h, buf, w * inputFormat.bytesPerPixel);
	} else {
		// Otherwise it is a bit more ugly because we have to handle a key
		// color properly.

		Graphics::Surface *dst = _cursor->getSurface();
		const uint srcPitch = w * inputFormat.bytesPerPixel;

		// Copy the cursor data to the actual texture surface. This will make
		// sure that the data is also converted to the expected format.
		Graphics::crossBlit((byte *)dst->getPixels(), (const byte *)buf, dst->pitch, srcPitch,
		                    w, h, dst->format, inputFormat);

		// We apply the color key by setting the alpha bits of the pixels to
		// fully transparent.
		const uint32 aMask = (0xFF >> dst->format.aLoss) << dst->format.aShift;
		if (dst->format.bytesPerPixel == 2) {
			if (inputFormat.bytesPerPixel == 2) {
				applyColorKey<uint16, uint16>((uint16 *)dst->getPixels(), (const uint16 *)buf, w, h,
				                              dst->pitch, srcPitch, keycolor, aMask);
			} else if (inputFormat.bytesPerPixel == 4) {
				applyColorKey<uint16, uint32>((uint16 *)dst->getPixels(), (const uint32 *)buf, w, h,
				                              dst->pitch, srcPitch, keycolor, aMask);
			}
		} else {
			if (inputFormat.bytesPerPixel == 2) {
				applyColorKey<uint32, uint16>((uint32 *)dst->getPixels(), (const uint16 *)buf, w, h,
				                              dst->pitch, srcPitch, keycolor, aMask);
			} else if (inputFormat.bytesPerPixel == 4) {
				applyColorKey<uint32, uint32>((uint32 *)dst->getPixels(), (const uint32 *)buf, w, h,
				                              dst->pitch, srcPitch, keycolor, aMask);
			}
		}

		// Flag the texture as dirty.
		_cursor->flagDirty();
	}

	// In case we actually use a palette set that up properly.
	if (inputFormat.bytesPerPixel == 1) {
		updateCursorPalette();
	}

	// Update the scaling.
	recalculateCursorScaling();
}