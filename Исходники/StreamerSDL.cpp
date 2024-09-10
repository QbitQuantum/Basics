bool StreamerSDL::saveBitmap(const Bitmap & bitmap, std::ostream & output) {
	if(bitmap.getPixelFormat() == PixelFormat::MONO_FLOAT) {
		Reference<Bitmap> tmp = BitmapUtils::convertBitmap(bitmap, PixelFormat::MONO);
		return saveBitmap(*tmp.get(), output);
	}
	SDL_Surface * surface = BitmapUtils::createSDLSurfaceFromBitmap(bitmap);
	if (surface == nullptr) {
		return false;
	}
	// Save the bitmap to a file temporarily.
	static TemporaryDirectory tempDir("StreamerSDL");

	FileName fileName(tempDir.getPath());
	do {
		fileName.setFile(StringUtils::createRandomString(16) + ".bmp");
	} while(FileUtils::isFile(fileName));

	int success = SDL_SaveBMP(surface, fileName.getPath().c_str());
	SDL_FreeSurface(surface);
	if(success != 0) {
		FileUtils::remove(fileName);
		return false;
	}

	std::ifstream fileInput(fileName.getPath().c_str(), std::ios_base::binary);
	output << fileInput.rdbuf();
	fileInput.close();

	FileUtils::remove(fileName);

	return true;
}