/**
 * Calculates the color of the biome with a biome color image.
 */
uint32_t Biome::getColor(const Image& colors, bool flip_xy) const {
	// x is temperature
	double tmp_temperature = temperature;
	// y is temperature * rainfall
	double tmp_rainfall = rainfall * temperature;

	// check if temperature and rainfall are valid
	if(tmp_temperature > 1)
		tmp_temperature = 1;
	if (tmp_rainfall > 1)
		tmp_rainfall = 1;

	// calculate positions
	int x = 255 - (255 * tmp_temperature);
	int y = 255 - (255 * tmp_rainfall);

	// flip them, if needed
	if (flip_xy) {
		int tmp = x;
		x = 255 - y;
		y = 255 - tmp;
	}

	// get color at this position
	uint32_t color = colors.getPixel(x, y);
	if (extra_r != 255 || extra_g != 255 || extra_b != 255) {
		// multiply with fixed biome color values if specified
		// necessary for the swampland biome
		return rgba_multiply(color, (uint8_t) extra_r, (uint8_t) extra_g, (uint8_t) extra_b, 255);
	}
	return color;
}