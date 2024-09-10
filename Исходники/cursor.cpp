void Cursor::loadAvailableCursors() {
	assert(_textures.empty());

	// Load available cursors
	for (uint i = 0; i < ARRAYSIZE(availableCursors); i++) {
		// Check if a cursor sharing the same texture has already been loaded
		if (_textures.contains(availableCursors[i].nodeID)) continue;

		// Load the cursor bitmap
		const DirectorySubEntry *cursorDesc = _vm->getFileDescription("GLOB", availableCursors[i].nodeID, 0, DirectorySubEntry::kRawData);
		if (!cursorDesc)
			error("Cursor %d does not exist", availableCursors[i].nodeID);

		Common::MemoryReadStream *bmpStream = cursorDesc->getData();

		Image::BitmapDecoder bitmapDecoder;
		if (!bitmapDecoder.loadStream(*bmpStream))
			error("Could not decode Myst III bitmap");
		const Graphics::Surface *surfaceBGRA = bitmapDecoder.getSurface();
		Graphics::Surface *surfaceRGBA = surfaceBGRA->convertTo(Graphics::PixelFormat(4, 8, 8, 8, 8, 0, 8, 16, 24));

		delete bmpStream;

		// Apply the colorkey for transparency
		for (uint u = 0; u < surfaceRGBA->w; u++) {
			for (uint v = 0; v < surfaceRGBA->h; v++) {
				uint32 *pixel = (uint32*)(surfaceRGBA->getBasePtr(u, v));
				if (*pixel == 0xFF00FF00)
					*pixel = 0x0000FF00;

			}
		}

		// Create and store the texture
		_textures.setVal(availableCursors[i].nodeID, _vm->_gfx->createTexture(surfaceRGBA));

		surfaceRGBA->free();
		delete surfaceRGBA;
	}
}