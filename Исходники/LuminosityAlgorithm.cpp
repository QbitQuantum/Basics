void LuminosityAlgorithm::doAlgorithm(const RGBImage& input, IntensityImage& output)
{
	// Check image size
	if (input.getWidth() != output.getWidth() || input.getHeight() != output.getHeight()) {
		output.set(input.getWidth(), input.getHeight());
	}

	// Lunimosity Algorithm defined as
	// Gray = (Red * 0.2126 + Green * 0.7152 + Blue * 0.0722)
	for (int i = 0; i < input.getWidth()*input.getHeight(); i++) {
		RGB pixel = input.getPixel(i);
		output.setPixel(i, pixel.r * 0.2126 + pixel.g * 0.7152 + pixel.b * 0.0722);
	}
}