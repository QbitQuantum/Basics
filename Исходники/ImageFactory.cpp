IntensityImage * ImageFactory::newIntensityImage(const IntensityImage &other) {
	IntensityImage * image = ImageFactory::newIntensityImage(other.getWidth(), other.getHeight());
	int size = other.getHeight() * other.getWidth();
	for (int i = 0; i < size; i++) {
		image->setPixel(i, other.getPixel(i));
	}
	return image;
}