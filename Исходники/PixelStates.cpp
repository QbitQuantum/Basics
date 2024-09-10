// drawPixel sets or clears a certain pixel depending on whether the colour
// is greater than 0 or not
void PixelStates::drawPixel(int16_t x, int16_t y, uint16_t color) {
	uint16_t pixelIdx = getPixelIdx(x, y);

	if(pixelIdx < 0) {
		return;
	}

	if(color > 0) {
		setPixel(pixelIdx);
	} else {
		clearPixel(pixelIdx);
	}
}