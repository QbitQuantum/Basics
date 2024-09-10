void OSystem_3DS::flushCursor() {
	if (_cursor.getPixels()) {
		Graphics::Surface *converted = _cursor.convertTo(_pfGameTexture, _cursorPaletteEnabled ? _cursorPalette : _palette);
		_cursorTexture.copyRectToSurface(*converted, 0, 0, Common::Rect(converted->w, converted->h));
		_cursorTexture.markDirty();
		converted->free();
		delete converted;
	
		if (_pfCursor.bytesPerPixel == 1) {
			uint* dest = (uint*) _cursorTexture.getPixels();
			byte* src = (byte*) _cursor.getPixels();
			for (int y = 0; y < _cursor.h; ++y) {
				for (int x = 0; x < _cursor.w; ++x) {
					if (*src++ == _cursorKeyColor)
						*dest++ = 0;
					else
						dest++;
				}
				dest += _cursorTexture.w - _cursorTexture.actualWidth;
			}
		}
	}
}