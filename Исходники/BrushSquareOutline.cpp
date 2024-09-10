void BrushSquareOutline::carre(sf::Image& image) {
	FOR_I (image.getSize().x)
		image.setPixel(i, 0, sf::Color::White);
	for (int j = 1; j < image.getSize().y - 1; j++) {
		image.setPixel(0, j, sf::Color::White);
		image.setPixel(image.getSize().x - 1, j, sf::Color::White);
	}
	FOR_I (image.getSize().x)
		image.setPixel(i, image.getSize().y - 1, sf::Color::White);
}