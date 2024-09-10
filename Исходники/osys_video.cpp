void OSystem_IPHONE::drawMouseCursorOnRectUpdate(const Common::Rect& updatedRect, const Common::Rect& mouseRect) {
	//draw mouse on top
	if (_mouseVisible && (updatedRect.intersects(mouseRect))) {
		int srcX = 0;
		int srcY = 0;
		int left = _mouseX - _mouseHotspotX;
		if (left < 0) {
			srcX -= left;
			left = 0;
		}
		int top = _mouseY - _mouseHotspotY;
		if (top < 0) {
			srcY -= top;
			top = 0;
		}

		int bottom = top + _mouseHeight;
		if (bottom > _screenWidth)
			bottom = _screenWidth;

		int displayWidth = _mouseWidth;
		if (_mouseWidth + left > _screenWidth)
			displayWidth = _screenWidth - left;

		int displayHeight = _mouseHeight;
		if (_mouseHeight + top > _screenHeight)
			displayHeight = _screenHeight - top;

		byte *src = &_mouseBuf[srcY * _mouseWidth + srcX];
		uint16 *dst = &_fullscreen[top * _screenWidth + left];
		for (int y = displayHeight; y > srcY; y--) {
			for (int x = displayWidth; x > srcX; x--) {
				if (*src != _mouseKeyColour)
					*dst = _palette[*src];
				dst++;
				src++;
			}
			dst += _screenWidth - displayWidth + srcX;
			src += _mouseWidth - displayWidth + srcX;
		}
	}
}