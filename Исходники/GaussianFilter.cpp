IntensityImageStudent GaussianFilter::applyFilter(const IntensityImage &image)
{
	IntensityImageStudent filteredImage = IntensityImageStudent(image.getWidth() - 2 * radius, image.getHeight() - 2 * radius);
	
	for (int y = 0; y < filteredImage.getHeight(); y++){
		for (int x = 0; x < filteredImage.getWidth(); x++){
			double filteredIntensity = 0.0;
			for (unsigned int i = 0; i < gaussKernel.size(); i++){
				filteredIntensity += gaussKernel[i] * image.getPixel(x + (i % (2 * radius + 1)), y + i / (2 * radius + 1));
			}
			filteredImage.setPixel(x, y, static_cast<Intensity>(filteredIntensity));
		}
	}
	return filteredImage;
}