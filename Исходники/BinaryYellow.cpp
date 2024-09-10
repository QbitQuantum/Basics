void BinaryYellow::CreateBinaryImage(Image &sourceImage, Image &destinationImage) {
	bt->reset();
	bt->start();

	if (sourceImage.GetWidth() != destinationImage.GetWidth() && sourceImage.GetHeight() != destinationImage.GetHeight()) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	for (int y = sourceImage.GetHeight() - 1; y >= 0; y--) {
		for (int x = sourceImage.GetWidth() - 1; x >= 0; x--) {

			// red		= 130	-255 
			// Green	= 80	-255
			// Blue		= 0		-85

			if (((int)sourceImage.GetPixelRed(x, y) >= 130) && ((int)sourceImage.GetPixelGreen(x, y) >= 80) && ((int)sourceImage.GetPixelBlue(x, y) <= 85)){
				destinationImage.SetPixel(x, y, 0xFFFFFFFF);
			}
			else{
				destinationImage.SetPixel(x, y, 0x000000FF);
			}
		}
	}

	bt->stop();
	std::cout << "Time for the binary yellow function: " << bt->elapsedMicroSeconds() << " Microseconds (" << bt->elapsedMilliSeconds() << "ms)" << std::endl;
}