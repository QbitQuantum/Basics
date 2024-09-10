/* Create a tinted texture by combining the tint map with the tint colors.
 *
 * This is currently all done here in software and has several drawbacks:
 * - Slow
 * - We're creating lots of uncompressed RBGA texture, so it
 *   takes up a lot of memory, both on the GPU and in system RAM
 *
 * TODO: We really need to do this in shaders in the future.
 */
void ModelNode_NWN2::createTint() {
	if (_tintMap.empty())
		return;

	ImageDecoder *tintMap   = 0;
	Surface      *tintedMap = 0;
	try {
		// Load and uncompress the texture
		tintMap = Texture::loadImage(_tintMap);
		if (tintMap->isCompressed())
			tintMap->decompress();

		const ImageDecoder::MipMap &tintImg = tintMap->getMipMap(0);

		// Create a new target surface with the same dimensions
		tintedMap = new Surface(tintImg.width, tintImg.height);
		ImageDecoder::MipMap &tintedImg = tintedMap->getMipMap();

		// Iterate over all pixels: read values, mix tints, write pixel to target surface
		for (int n = 0; n < tintImg.width * tintImg.height; n++) {
			float srcColor[4], dstColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			tintImg.getPixel(n, srcColor[0], srcColor[1], srcColor[2], srcColor[3]);

			if (srcColor[3] != 0.0f) {
				// Mix using the value and the alpha components as intensities
				// TODO: Verify how the mixing is actually done in NWN2!
				for (int i = 0; i < 3; i++) {
					for (int j = 0; j < 3; j++)
						dstColor[j] += _tint[i][j] * srcColor[i] * _tint[i][3] * srcColor[3] * _diffuse[i];
				}
			} else
				// Source alpha is 0.0f: No tinting for this pixel
				for (int i = 0; i < 3; i++)
					dstColor[i] = _diffuse[i] * _tint[i][3];

			tintedImg.setPixel(n, dstColor[0], dstColor[1], dstColor[2], dstColor[3]);
		}

	} catch (...) {
		delete tintMap;
		delete tintedMap;
		return;
	}

	delete tintMap;

	// And add the new texture to the TextureManager
	TextureHandle tintedTexture = TextureMan.add(Texture::create(tintedMap));

	_textures.push_back(tintedTexture);
	_tintedMapIndex = _textures.size() - 1;
}