// Compute MOPs descriptors.
void ComputeMOPSDescriptors(CFloatImage &image, FeatureSet &features)
{
	CFloatImage grayImage=ConvertToGray(image);
	CFloatImage blurredImage;
	
	Convolve(grayImage, blurredImage, ConvolveKernel_7x7);

	CFloatImage postHomography = CFloatImage();
	CFloatImage gaussianImage = GetImageFromMatrix((float *)gaussian5x5Float, 5, 5);


	//first make the image invariant to changes in illumination by subtracting off the mean
	int grayHeight = grayImage.Shape().height;
	int grayWidth = grayImage.Shape().width;

	// now make this rotation invariant
    vector<Feature>::iterator featureIterator = features.begin();
    while (featureIterator != features.end()) {
		Feature &f = *featureIterator;

		CTransform3x3 scaleTransform = CTransform3x3();
		CTransform3x3 translationNegative;
		CTransform3x3 translationPositive;
		CTransform3x3 rotation;

		double scaleFactor = 41/8;
		scaleTransform[0][0] = scaleFactor;
		scaleTransform[1][1] = scaleFactor;

		translationNegative = translationNegative.Translation(f.x,f.y);
		translationPositive = translationPositive.Translation(-4, -4);
		rotation = rotation.Rotation(f.angleRadians * 180/ PI);
		
		CTransform3x3 finalTransformation = translationNegative * rotation * scaleTransform * translationPositive;
		//CFloatImage sample61x61Window = 
		//CFloatImage pixelWindow = GetXWindowAroundPixel(grayImage, f.x, f.y, 61);

		WarpGlobal(blurredImage, postHomography, finalTransformation, eWarpInterpLinear, 1.0f);

		//now we get the 41x41 box around the feature
		for(int row=0; row< 8; row++)
		{
			for(int col=0;col< 8;col++)
			{
				f.data.push_back(postHomography.Pixel(col, row, 0));
			}
		}
		/*
		// now we do the subsampling first round to reduce to a 20x20
		int imgSize = 41;
		subsample(&f, imgSize, gaussianImage);

		//second round of subsampling to get it to a 10x10
		imgSize = 20;
		subsample(&f, imgSize, gaussianImage);	

		imgSize = 10;
		CFloatImage img = featureToImage(f, imgSize, imgSize);
		CFloatImage blurredImg(img.Shape());
		Convolve(img, blurredImg, gaussianImage);
		featuresFromImage(&f,blurredImg,imgSize,imgSize);
		
		int count = 0;
		for(int y=0; y<imgSize; y++)
		{
			for(int x=0; x<imgSize; x++)
			{
				if(x == 3 || x == 7 || y == 3 || y == 7)
				{
					f.data.erase(f.data.begin() + count);
				}
				else
				{
					count++;
				}
			}
		}
		*/
		normalizeIntensities(&f, 8, 8);
		featureIterator++;

	}
}