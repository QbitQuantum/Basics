sf::Color sfImageGetPixelFloat(const sf::Image& image, float x, float y) {
	auto size = image.getSize();
	return image.getPixel(x*size.x, y*size.y);
}