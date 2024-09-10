static bool saveImage(const ofPixels_<PixelType> & _pix, const std::filesystem::path& _fileName, ofImageQualityType qualityLevel) {
	ofInitFreeImage();
	if (_pix.isAllocated() == false){
		ofLogError("ofImage") << "saveImage(): couldn't save \"" << _fileName << "\", pixels are not allocated";
		return false;
	}

	ofFilePath::createEnclosingDirectory(_fileName);
	std::string fileName = ofToDataPath(_fileName);
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFileType(fileName.c_str(), 0);
	if(fif == FIF_UNKNOWN) {
		// or guess via filename
		fif = FreeImage_GetFIFFromFilename(fileName.c_str());
	}
	if(fif==FIF_JPEG && (_pix.getNumChannels()==4 || _pix.getBitsPerChannel() > 8)){
		ofPixels pix3 = _pix;
		pix3.setNumChannels(3);
		return saveImage(pix3,_fileName,qualityLevel);
	}

	FIBITMAP * bmp = nullptr;
	#ifdef TARGET_LITTLE_ENDIAN
	if(sizeof(PixelType) == 1 && (_pix.getPixelFormat()==OF_PIXELS_RGB || _pix.getPixelFormat()==OF_PIXELS_RGBA)) {	// Make a local copy.
		ofPixels_<PixelType> pix = _pix;
		pix.swapRgb();
		bmp	= getBmpFromPixels(pix);
	}else{
	#endif

		bmp	= getBmpFromPixels(_pix);


	#ifdef TARGET_LITTLE_ENDIAN
	}
	#endif

	bool retValue = false;
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		if(fif == FIF_JPEG) {
			int quality = JPEG_QUALITYSUPERB;
			switch(qualityLevel) {
				case OF_IMAGE_QUALITY_WORST: quality = JPEG_QUALITYBAD; break;
				case OF_IMAGE_QUALITY_LOW: quality = JPEG_QUALITYAVERAGE; break;
				case OF_IMAGE_QUALITY_MEDIUM: quality = JPEG_QUALITYNORMAL; break;
				case OF_IMAGE_QUALITY_HIGH: quality = JPEG_QUALITYGOOD; break;
				case OF_IMAGE_QUALITY_BEST: quality = JPEG_QUALITYSUPERB; break;
			}
			retValue = FreeImage_Save(fif, bmp, fileName.c_str(), quality);
		} else {
			if(qualityLevel != OF_IMAGE_QUALITY_BEST) {
				ofLogWarning("ofImage") << "saveImage(): ofImageCompressionType only applies to JPEGs,"
					<< " ignoring value for \" "<< fileName << "\"";
			}

			if (fif == FIF_GIF) {
				FIBITMAP* convertedBmp;
				if(_pix.getImageType() == OF_IMAGE_COLOR_ALPHA) {
					// this just converts the image to grayscale so it can save something
					convertedBmp = FreeImage_ConvertTo8Bits(bmp);
				} else {
					// this will create a 256-color palette from the image
					convertedBmp = FreeImage_ColorQuantize(bmp, FIQ_NNQUANT);
				}
				retValue = FreeImage_Save(fif, convertedBmp, fileName.c_str());
				if (convertedBmp != nullptr){
					FreeImage_Unload(convertedBmp);
				}
			} else {
				retValue = FreeImage_Save(fif, bmp, fileName.c_str());
			}
		}
	}

	if (bmp != nullptr){
		FreeImage_Unload(bmp);
	}

	return retValue;
}