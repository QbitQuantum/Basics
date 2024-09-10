void Life::flush() {
	hsv.addHue(1);
	Rgb rgb = Rgb(hsv);
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
		for (uint8_t y = 0; y < MATRIX_HEIGHT; y++) {
			if (state[x][y] > 0) {
				matrix.setColor(rgb);
			} else {
				matrix.setColor(0,0,0);
			}
			matrix.setPixel(x, y);
		}
    }
	matrix.flush();
}