BaseSurface *BaseFontTT::renderTextToTexture(const WideString &text, int width, TTextAlign align, int maxHeight, int &textOffset) {
	//TextLineList lines;
	// TODO: Use WideString-conversion here.
	//WrapText(text, width, maxHeight, lines);
	Common::Array<WideString> lines;
	_font->wordWrapText(text, width, lines);

	while (maxHeight > 0 && lines.size() * _lineHeight > maxHeight) {
		lines.pop_back();
	}
	if (lines.size() == 0) {
		return nullptr;
	}

	Graphics::TextAlign alignment = Graphics::kTextAlignInvalid;
	if (align == TAL_LEFT) {
		alignment = Graphics::kTextAlignLeft;
	} else if (align == TAL_CENTER) {
		alignment = Graphics::kTextAlignCenter;
	} else if (align == TAL_RIGHT) {
		alignment = Graphics::kTextAlignRight;
	}

	// TODO: This debug call does not work with WideString because text.c_str() returns an uint32 array.
	//debugC(kWintermuteDebugFont, "%s %d %d %d %d", text.c_str(), RGBCOLGetR(_layers[0]->_color), RGBCOLGetG(_layers[0]->_color), RGBCOLGetB(_layers[0]->_color), RGBCOLGetA(_layers[0]->_color));
//	void drawString(Surface *dst, const Common::String &str, int x, int y, int w, uint32 color, TextAlign align = kTextAlignLeft, int deltax = 0, bool useEllipsis = true) const;
	Graphics::Surface *surface = new Graphics::Surface();
	surface->create((uint16)width, (uint16)(_lineHeight * lines.size()), _gameRef->_renderer->getPixelFormat());
	uint32 useColor = 0xffffffff;
	Common::Array<WideString>::iterator it;
	int heightOffset = 0;
	for (it = lines.begin(); it != lines.end(); ++it) {
		_font->drawString(surface, *it, 0, heightOffset, width, useColor, alignment);
		heightOffset += (int)_lineHeight;
	}

	BaseSurface *retSurface = _gameRef->_renderer->createSurface();

	if (_deletableFont) {
		// Reconstruct the alpha channel of the font.

		// Since we painted it with color 0xFFFFFFFF onto a black background,
		// the alpha channel is gone, but the color value of each pixel corresponds
		// to its original alpha value.

		Graphics::PixelFormat format = _gameRef->_renderer->getPixelFormat();
		uint32 *pixels = (uint32 *)surface->getPixels();

		// This is a Surface we created ourselves, so no empty space between rows.
		for (int i = 0; i < surface->w * surface->h; ++i) {
			uint8 a, r, g, b;
			format.colorToRGB(*pixels, r, g, b);
			a = r;
			*pixels++ = format.ARGBToColor(a, r, g, b);
		}
	}

	retSurface->putSurface(*surface, true);
	surface->free();
	delete surface;
	return retSurface;
	// TODO: _isUnderline, _isBold, _isItalic, _isStriked
}