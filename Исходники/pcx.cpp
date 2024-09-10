bool PCXDecoder::loadStream(Common::SeekableReadStream &stream) {
	destroy();

	if (stream.readByte() != 0x0a)	// ZSoft PCX
		return false;

	byte version = stream.readByte();	// 0 - 5
	if (version > 5)
		return false;

	bool compressed = stream.readByte(); // encoding, 1 = run length encoding
	byte bitsPerPixel = stream.readByte();	// 1, 2, 4 or 8

	// Window
	uint16 xMin = stream.readUint16LE();
	uint16 yMin = stream.readUint16LE();
	uint16 xMax = stream.readUint16LE();
	uint16 yMax = stream.readUint16LE();

	uint16 width  = xMax - xMin + 1;
	uint16 height = yMax - yMin + 1;

	if (xMax < xMin || yMax < yMin) {
		warning("Invalid PCX image dimensions");
		return false;
	}

	stream.skip(4);	// HDpi, VDpi

	// Read the EGA palette (colormap)
	_palette = new byte[16 * 3];
	for (uint16 i = 0; i < 16; i++) {
		_palette[i * 3 + 0] = stream.readByte();
		_palette[i * 3 + 1] = stream.readByte();
		_palette[i * 3 + 2] = stream.readByte();
	}

	if (stream.readByte() != 0)	// reserved, should be set to 0
		return false;

	byte nPlanes = stream.readByte();
	uint16 bytesPerLine = stream.readUint16LE();
	uint16 bytesPerscanLine = nPlanes * bytesPerLine;

	if (bytesPerscanLine < width * bitsPerPixel * nPlanes / 8) {
		warning("PCX data is corrupted");
		return false;
	}

	stream.skip(60);	// PaletteInfo, HscreenSize, VscreenSize, Filler

	_surface = new Graphics::Surface();

	byte *scanLine = new byte[bytesPerscanLine];
	byte *dst;
	int x, y;

	if (nPlanes == 3 && bitsPerPixel == 8) {	// 24bpp
		Graphics::PixelFormat format = Graphics::PixelFormat(4, 8, 8, 8, 8, 24, 16, 8, 0);
		_surface->create(width, height, format);
		dst = (byte *)_surface->getPixels();
		_paletteColorCount = 0;

		for (y = 0; y < height; y++) {
			decodeRLE(stream, scanLine, bytesPerscanLine, compressed);

			for (x = 0; x < width; x++) {
				byte b = scanLine[x];
				byte g = scanLine[x +  bytesPerLine];
				byte r = scanLine[x + (bytesPerLine << 1)];
				uint32 color = format.RGBToColor(r, g, b);

				*((uint32 *)dst) = color;
				dst += format.bytesPerPixel;
			}
		}
	} else if (nPlanes == 1 && bitsPerPixel == 8) {	// 8bpp indexed
		_surface->create(width, height, Graphics::PixelFormat::createFormatCLUT8());
		dst = (byte *)_surface->getPixels();
		_paletteColorCount = 16;

		for (y = 0; y < height; y++, dst += _surface->pitch) {
			decodeRLE(stream, scanLine, bytesPerscanLine, compressed);
			memcpy(dst, scanLine, width);
		}

		if (version == 5) {
			if (stream.readByte() != 12) {
				warning("Expected a palette after the PCX image data");
				delete[] scanLine;
				return false;
			}

			// Read the VGA palette
			delete[] _palette;
			_palette = new byte[256 * 3];
			for (uint16 i = 0; i < 256; i++) {
				_palette[i * 3 + 0] = stream.readByte();
				_palette[i * 3 + 1] = stream.readByte();
				_palette[i * 3 + 2] = stream.readByte();
			}

			_paletteColorCount = 256;
		}
	} else if ((nPlanes == 2 || nPlanes == 3 || nPlanes == 4) && bitsPerPixel == 1) {	// planar, 4, 8 or 16 colors
		_surface->create(width, height, Graphics::PixelFormat::createFormatCLUT8());
		dst = (byte *)_surface->getPixels();
		_paletteColorCount = 16;

		for (y = 0; y < height; y++, dst += _surface->pitch) {
			decodeRLE(stream, scanLine, bytesPerscanLine, compressed);

			for (x = 0; x < width; x++) {
				int m = 0x80 >> (x & 7), v = 0;
				for (int i = nPlanes - 1; i >= 0; i--) {
					v <<= 1;
					v  += (scanLine[i * bytesPerLine + (x >> 3)] & m) == 0 ? 0 : 1;
				}
				dst[x] = v;
			}
		}
	} else {