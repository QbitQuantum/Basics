void ofPixels_<PixelType>::copyFrom(const ofPixels_<PixelType> & mom){
	if(mom.isAllocated()) {
		allocate(mom.getWidth(), mom.getHeight(), mom.getPixelFormat());
		memcpy(pixels, mom.getData(), getTotalBytes());
	}
}