//This method defines edges by applying a x and y mask. The magnitude of both directions x and y will be combined resulting a value that represents an edge.
void SobelFilter::CreateSobelImage(Image &destinationImage) {
	Image sourceImage(destinationImage);

	int srcHeight = sourceImage.GetHeight();
	int srcWidth = sourceImage.GetWidth();

	int dstHeight = destinationImage.GetHeight();
	int dstWidth = destinationImage.GetWidth();

	if (srcWidth != dstWidth && srcHeight != dstHeight) {
		std::cout << "Error images are not the same size" << std::endl;
		return;
	}

	//The masks
	double kernelY[3][3] = { {1, 0, -1 },
							{ 2, 0, -2 },
							{ 1, 0, -1 } };

	double kernelX[3][3] = { {	1,	2,  1 },
							 {	0,  0,  0 },
							 { -1, -2, -1 } };

	//For each pixel, apply the masks and combine them.
	for (int x = 1; x < dstWidth - 1; ++x){
		for (int y = 1; y < dstHeight - 1; ++y){
			double magX = 0.0;
			double magY = 0.0;

			//Applying the masks to the pixel resulting a magnitude for both the X and Y direction.
			for (int a = 0; a < 3; a++)
			{
				for (int b = 0; b < 3; b++)
				{
					int xn = x + a - 1;
					int yn = y + b - 1;

					magX += sourceImage.GetPixelRed(xn, yn) * kernelX[a][b];
					magY += sourceImage.GetPixelRed(xn, yn) * kernelY[a][b];
				}
			}

			if (magX < 0) { magX = 0; }
			else if (magX > 255) { magX = 255; }
			if (magY < 0) { magY = 0; }
			else if (magY > 255) { magY = 255; }

			//Combine the masks 
			double mag = sqrt(magX * magX + magY * magY);

			if (mag < 0) { mag = 0; }
			else if (mag > 255) { mag = 255; }

			int mg = (int)mag;
			destinationImage.SetPixel(x, y, mg << redPixelShift | mg << greenPixelShift | mg << bluePixelShift);
		}
	}
}