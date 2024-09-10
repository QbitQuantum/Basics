bool TGADecoder::readHeader(Common::SeekableReadStream &tga, byte &imageType, byte &pixelDepth) {
	if (!tga.seek(0)) {
		warning("Failed reading TGA-file");
		return false;
	}

	// TGAs have an optional "id" string in the header
	uint32 idLength = tga.readByte();

	// Number of colors in the color map / palette
	int hasColorMap = tga.readByte();

	// Image type. See header for numeric constants
	imageType = tga.readByte();

	switch (imageType) {
	case TYPE_CMAP:
	case TYPE_TRUECOLOR:
	case TYPE_BW:
	case TYPE_RLE_CMAP:
	case TYPE_RLE_TRUECOLOR:
	case TYPE_RLE_BW:
		break;
	default:
		warning("Unsupported image type: %d", imageType);
		return false;
	}

	// Color map specifications
	if (hasColorMap == 0) {
		tga.skip(5);
	} else {
		_colorMapOrigin = tga.readUint16LE();
		_colorMapLength = tga.readUint16LE();
		_colorMapEntryLength = tga.readByte();
	}
	// Origin-defintions
	tga.skip(2 + 2);

	// Image dimensions
	_surface.w = tga.readUint16LE();
	_surface.h = tga.readUint16LE();

	// Bits per pixel
	pixelDepth = tga.readByte();
	_surface.format.bytesPerPixel = pixelDepth / 8;

	// Image descriptor
	byte imgDesc = tga.readByte();
	int attributeBits = imgDesc & 0x0F;
	assert((imgDesc & 0x10) == 0);
	_originTop = (imgDesc & 0x20);

	// Interleaving is not handled at this point
	//int interleave = (imgDesc & 0xC);
	if (imageType == TYPE_CMAP || imageType == TYPE_RLE_CMAP) {
		if (pixelDepth == 8) {
			_format = PixelFormat::createFormatCLUT8();
		} else {
			warning("Unsupported index-depth: %d", pixelDepth);
			return false;
		}
	} else if (imageType == TYPE_TRUECOLOR || imageType == TYPE_RLE_TRUECOLOR) {
		if (pixelDepth == 24) {
			_format = PixelFormat(3, 8, 8, 8, 0, 16, 8, 0, 0);
		} else if (pixelDepth == 32) {
			// HACK: According to the spec, attributeBits should determine the amount
			// of alpha-bits, however, as the game files that use this decoder seems
			// to ignore that fact, we force the amount to 8 for 32bpp files for now.
			_format = PixelFormat(4, 8, 8, 8, /* attributeBits */ 8, 16, 8, 0, 24);
		} else if (pixelDepth == 16 && imageType == TYPE_TRUECOLOR) {
			// 16bpp TGA is ARGB1555
			_format = PixelFormat(2, 5, 5, 5, attributeBits, 10, 5, 0, 15);
		} else {
			warning("Unsupported pixel depth: %d, %d", imageType, pixelDepth);
			return false;
		}
	} else if (imageType == TYPE_BW || TYPE_RLE_BW) {
		if (pixelDepth == 8) {
			_format = PixelFormat(4, 8, 8, 8, 0, 16, 8, 0, 0);
		} else {
			warning("Unsupported pixel depth: %d, %d", imageType, pixelDepth);
			return false;
		}

	} else {
		warning("Unsupported image type: %d", imageType);
		return false;
	}

	// Skip the id string
	tga.skip(idLength);

	if (hasColorMap) {
		return readColorMap(tga, imageType, pixelDepth);
	}
	return true;
}