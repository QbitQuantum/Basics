void TPC::fixupCubeMap() {
	/* Do various fixups to the cube maps. This includes rotating and swapping a
	 * few sides around. This is done by the original games as well.
	 */

	if (!isCubeMap())
		return;

	for (size_t j = 0; j < getMipMapCount(); j++) {
		assert(getLayerCount() > 0);

		const size_t index0 = 0 * getMipMapCount() + j;
		assert(index0 < _mipMaps.size());

		const  int32 width  = _mipMaps[index0]->width;
		const  int32 height = _mipMaps[index0]->height;
		const uint32 size   = _mipMaps[index0]->size;

		for (size_t i = 1; i < getLayerCount(); i++) {
			const size_t index = i * getMipMapCount() + j;
			assert(index < _mipMaps.size());

			if ((width  != _mipMaps[index]->width ) ||
			    (height != _mipMaps[index]->height) ||
			    (size   != _mipMaps[index]->size  ))
				throw Common::Exception("Cube map layer dimensions mismatch");
		}
	}

	// Since we need to rotate the individual cube sides, we need to decompress them all
	decompress();

	// Swap the first two sides of the cube maps
	for (size_t j = 0; j < getMipMapCount(); j++) {
		const size_t index0 = 0 * getMipMapCount() + j;
		const size_t index1 = 1 * getMipMapCount() + j;
		assert((index0 < _mipMaps.size()) && (index1 < _mipMaps.size()));

		MipMap &mipMap0 = *_mipMaps[index0];
		MipMap &mipMap1 = *_mipMaps[index1];

		SWAP(mipMap0.data, mipMap1.data);
	}

	const int bpp = (_formatRaw == kPixelFormatRGB8) ? 3 : ((_formatRaw == kPixelFormatRGBA8) ? 4 : 0);
	if (bpp == 0)
		return;

	// Rotate the cube sides so that they're all oriented correctly
	for (size_t i = 0; i < getLayerCount(); i++) {
		for (size_t j = 0; j < getMipMapCount(); j++) {
			const size_t index = i * getMipMapCount() + j;
			assert(index < _mipMaps.size());

			MipMap &mipMap = *_mipMaps[index];

			static const int rotation[6] = { 1, 3, 0, 2, 2, 0 };

			rotate90(mipMap.data, mipMap.width, mipMap.height, bpp, rotation[i]);
		}
	}

}