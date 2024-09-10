void PreprocessingResults::computePreprocessings(	const PreprocessingParameters parameters,
							const GrayImage<> &glyphImage)
{
	this->clear();

	// 1st: preprocess glyph image:
	mpProcessedImage = new GrayImage<>();
	PreprocessingResults::preprocessGlyph(parameters, glyphImage, *mpProcessedImage, &isWhiteSpace);
//	pImageChar->pPreprImage = mpProcessedImage;
//	std::cout << "finished processing image " << i << std::endl;
//	std::cout << mProcessedImagesVec[i] << std::endl;

	if (isWhiteSpace) { // jump out as this is a whitespace character
		return;
	}

#if 1
	// 2nd: compute integral invariant image:
	int radius = 2; bool oddSize = true;
	Kernel<> mask;
	Kernel<>::createSphereKernel( mask, radius, oddSize );
//	std::cout << mask << std::endl;
	mpIntInvImage = new GrayImage<float>();
	ImageIntegralInvariant::calcIntegralInvariantImage( mask, *mpProcessedImage, *mpIntInvImage );
#endif

#if 1
	// 3rd: compute distance transform of inverted(!) glyph:
	GrayImage<> invPreprocessedGlyphImage = *mpProcessedImage;
	invPreprocessedGlyphImage.invert();
	mpDistTransformImage = new GrayImage<float>();
	ImageFilter::distTransform(invPreprocessedGlyphImage, *mpDistTransformImage);
#endif

	return;
}