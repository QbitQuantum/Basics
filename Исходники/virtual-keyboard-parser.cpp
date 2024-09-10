bool VirtualKeyboardParser::parserCallback_layout(ParserNode *node) {
	assert(!_mode->resolution.empty());

	String res = node->values["resolution"];

	if (res != _mode->resolution) {
		node->ignore = true;
		return true;
	}

	_mode->bitmapName = node->values["bitmap"];

	SeekableReadStream *file = _keyboard->_fileArchive->createReadStreamForMember(_mode->bitmapName);
	if (!file)
		return parserError("Bitmap '" + _mode->bitmapName + "' not found");

	const Graphics::PixelFormat format = g_system->getOverlayFormat();

	{
		Graphics::BitmapDecoder bmp;
		if (!bmp.loadStream(*file))
			return parserError("Error loading bitmap '" + _mode->bitmapName + "'");

		_mode->image = bmp.getSurface()->convertTo(format);
	}

	delete file;

	int r, g, b;
	if (node->values.contains("transparent_color")) {
		if (!parseIntegerKey(node->values["transparent_color"], 3, &r, &g, &b))
			return parserError("Could not parse color value");
	} else {
		// default to purple
		r = 255;
		g = 0;
		b = 255;
	}
	_mode->transparentColor = format.RGBToColor(r, g, b);

	if (node->values.contains("display_font_color")) {
		if (!parseIntegerKey(node->values["display_font_color"], 3, &r, &g, &b))
			return parserError("Could not parse color value");
	} else {
		r = g = b = 0; // default to black
	}
	_mode->displayFontColor = format.RGBToColor(r, g, b);

	_layoutParsed = true;

	return true;
}