bool PNGLoader::doDecodeImage(const byte *fileDataPtr, uint fileSize, byte *&uncompressedDataPtr, int &width, int &height, int &pitch) {
#ifndef USE_INTERNAL_PNG_DECODER
	png_structp png_ptr = NULL;
	png_infop   info_ptr = NULL;

	int         bitDepth;
	int         colorType;
	int         interlaceType;
	int         i;

	// Check for valid PNG signature
	if (!doIsCorrectImageFormat(fileDataPtr, fileSize)) {
		error("png_check_sig failed");
	}

	// Create both PNG structures
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		error("Could not create libpng read struct.");
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		error("Could not create libpng info struct.");
	}

	// Use alternative reading function
	const byte **ref = &fileDataPtr;
	png_set_read_fn(png_ptr, (void *)ref, png_user_read_data);

	// Read PNG header
	png_read_info(png_ptr, info_ptr);

	// Read out PNG informations

	png_uint_32 w, h;
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &bitDepth, &colorType, &interlaceType, NULL, NULL);
	width = w;
	height = h;

	// Calculate pitch of output image
	pitch = GraphicEngine::calcPitch(GraphicEngine::CF_ARGB32, width);

	// Allocate memory for the final image data.
	// To keep memory framentation low this happens before allocating memory for temporary image data.
	uncompressedDataPtr = new byte[pitch * height];
	if (!uncompressedDataPtr) {
		error("Could not allocate memory for output image.");
	}

	// Images of all color formates will be transformed into ARGB images
	if (bitDepth == 16)
		png_set_strip_16(png_ptr);
	if (colorType == PNG_COLOR_TYPE_PALETTE)
		png_set_expand(png_ptr);
	if (bitDepth < 8)
		png_set_expand(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_expand(png_ptr);
	if (colorType == PNG_COLOR_TYPE_GRAY ||
	        colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	png_set_bgr(png_ptr);

	if (colorType != PNG_COLOR_TYPE_RGB_ALPHA)
		png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);

	// After the transformations have been registered, the image data is read again.
	png_read_update_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &w, &h, &bitDepth, &colorType, NULL, NULL, NULL);
	width = w;
	height = h;

	if (interlaceType == PNG_INTERLACE_NONE) {
		// PNGs without interlacing can simply be read row by row.
		for (i = 0; i < height; i++) {
			png_read_row(png_ptr, uncompressedDataPtr + i * pitch, NULL);
		}
	} else {
		// PNGs with interlacing require us to allocate an auxillary
		// buffer with pointers to all row starts.

		// Allocate row pointer buffer
		png_bytep *pRowPtr = new png_bytep[height];
		if (!pRowPtr) {
			error("Could not allocate memory for row pointers.");
		}

		// Initialize row pointers
		for (i = 0; i < height; i++)
			pRowPtr[i] = uncompressedDataPtr + i * pitch;

		// Read image data
		png_read_image(png_ptr, pRowPtr);

		// Free row pointer buffer
		delete[] pRowPtr;
	}

	// Read additional data at the end.
	png_read_end(png_ptr, NULL);

	// Destroy libpng structures
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
#else
	Common::MemoryReadStream *fileStr = new Common::MemoryReadStream(fileDataPtr, fileSize, DisposeAfterUse::NO);
	Graphics::PNG *png = new Graphics::PNG();
	if (!png->read(fileStr))	// the fileStr pointer, and thus pFileData will be deleted after this is done
		error("Error while reading PNG image");

	Graphics::PixelFormat format = Graphics::PixelFormat(4, 8, 8, 8, 8, 16, 8, 0, 24);
	Graphics::Surface *pngSurface = png->getSurface(format);

	width = pngSurface->w;
	height = pngSurface->h;
	uncompressedDataPtr = new byte[pngSurface->pitch * pngSurface->h];
	memcpy(uncompressedDataPtr, (byte *)pngSurface->pixels, pngSurface->pitch * pngSurface->h);
	pngSurface->free();

	delete pngSurface;
	delete png;

#endif
	// Signal success
	return true;
}