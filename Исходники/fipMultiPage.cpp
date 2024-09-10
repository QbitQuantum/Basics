BOOL fipMultiPage::open(fipMemoryIO& memIO, int flags) {
	// try to guess the file format from the filename
	FREE_IMAGE_FORMAT fif = memIO.getFileType();

	// check for supported file types
	if((fif == FIF_UNKNOWN) || (fif != FIF_TIFF) && (fif != FIF_ICO) && (fif != FIF_GIF))
		return FALSE;

	// open the stream
	_mpage = FreeImage_LoadMultiBitmapFromMemory(fif, memIO, flags);

	return (NULL != _mpage ) ? TRUE : FALSE;
}