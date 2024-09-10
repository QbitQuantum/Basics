void draw(Image image) {
	uint32_t *data;

	data = (uint32_t *) image.data;

	for (int y = 0; y < height; y++) {
		Pixel blackAlpha = {0};

		blackAlpha.A = y;

		for (int x = 0; x < width; x++) {
			*data++ = alphaBlend(blackAlpha, (Pixel) *data).value;
		}
	}
}