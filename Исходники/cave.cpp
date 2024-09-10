void CaveRendermode::draw(RGBAImage& image, const mc::BlockPos& pos,
		uint16_t id, uint16_t data) {
	// a nice color gradient to see something
	// (because the whole map is just full of cave stuff,
	// one can't differentiate the single caves)

	double h1 = (double) (64 - pos.y) / 64;
	if (pos.y > 64)
		h1 = 0;

	double h2 = 0;
	if (pos.y >= 64 && pos.y < 96)
		h2 = (double) (96 - pos.y) / 32;
	else if (pos.y > 16 && pos.y < 64)
		h2 = (double) (pos.y - 16) / 48;

	double h3 = 0;
	if (pos.y > 64)
		h3 = (double) (pos.y - 64) / 64;
	
	int R = h1 * 128.0 + 128.0;
	int G = h2 * 255.0;
	int B = h3 * 255.0;
	
	int Y = (R*3+G*10+B)/14; //get luminance of recolor
	
	// We try to do luminance-neutral additive/subtractive color instead of alpha blending, for better contrast
	// So first subtract luminance from each component.
	R = (R-Y)/3; // /3 is similar to alpha=85
	G = (G-Y)/3;
	B = (B-Y)/3;
	
	int size = image.getWidth();
	for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++) {
			uint32_t pixel = image.getPixel(x, y);
			if (pixel != 0) {				
				image.setPixel(x,y, rgba_add_clamp(pixel, R, G, B));
			}
		}
}