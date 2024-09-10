IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	int height = image.getHeight();
	int width = image.getWidth();
	int size = height * width;

	IntensityImageStudent* grayImage = new IntensityImageStudent(height, width);

	for (int i = 0; i < size; i++){
		//int gray = ( std::max( std::max(image.getPixel(i).r, image.getPixel(i).g) , image.getPixel(i).b) + std::min( std::min(image.getPixel(i).r , image.getPixel(i).g) , image.getPixel(i).b) ); //Algoritme lichtheid
		int gray = ((image.getPixel(i).r + image.getPixel(i).g + image.getPixel(i).b) / 3); // Algotitme: gemiddelde
		//int gray = (0.21 * image.getPixel(i).r) + (0.72 * image.getPixel(i).g) + (0.07 * image.getPixel(i).b); //Algortime helderheid

		grayImage->setPixel(i, gray);
	}

	return grayImage;
}