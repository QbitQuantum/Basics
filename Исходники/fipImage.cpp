BOOL fipImage::loadFromMemory(fipMemoryIO& memIO, int flag) {
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	// check the file signature and get its format
	fif = memIO.getFileType();
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		// Free the previous dib
		if(_dib) {
			FreeImage_Unload(_dib);			
		}
		// Load the file
		_dib = memIO.load(fif, flag);
		_bHasChanged = TRUE;
		if(_dib == NULL)
			return FALSE;
		return TRUE;
	}
	return FALSE;
}