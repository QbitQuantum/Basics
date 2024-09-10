bool StreamerPNG::saveBitmap(const Bitmap & bitmap, std::ostream & output) {
	volatile int colorType = 0; // volatile is needed because of the setjmp later on.
	volatile int transforms = 0;

	const PixelFormat & pixelFormat = bitmap.getPixelFormat();
	if(pixelFormat == PixelFormat::RGBA) {
		colorType = PNG_COLOR_TYPE_RGB_ALPHA;
		transforms = PNG_TRANSFORM_IDENTITY;
	} else if(pixelFormat == PixelFormat::BGRA) {
		colorType = PNG_COLOR_TYPE_RGB_ALPHA;
		transforms = PNG_TRANSFORM_BGR;
	} else if(pixelFormat == PixelFormat::RGB) {
		colorType = PNG_COLOR_TYPE_RGB;
		transforms = PNG_TRANSFORM_IDENTITY;
	} else if(pixelFormat == PixelFormat::BGR) {
		colorType = PNG_COLOR_TYPE_RGB;
		transforms = PNG_TRANSFORM_BGR;
	} else if(pixelFormat == PixelFormat::MONO) {
		colorType = PNG_COLOR_TYPE_GRAY;
		transforms = PNG_TRANSFORM_IDENTITY;
	} else if(pixelFormat == PixelFormat::MONO_FLOAT) {
		Reference<Bitmap> tmp = BitmapUtils::convertBitmap(bitmap, PixelFormat::MONO);
		return saveBitmap(*tmp.get(), output);
	} else {
		WARN("Unable to save PNG file. Unsupported color type.");
		return false;
	}

	// Set up the necessary structures for libpng.
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!png_ptr) {
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, nullptr);
		return false;
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return false;
	}

	struct PNGFunctions {
			static void writeData(png_structp write_ptr, png_bytep data, png_size_t length) {
				std::ostream * out = reinterpret_cast<std::ostream *>(png_get_io_ptr(write_ptr));
				out->write(reinterpret_cast<const char*>(data), static_cast<std::streamsize>(length));
			}
			static void flushData(png_structp flush_ptr) {
				std::ostream * out = reinterpret_cast<std::ostream *>(png_get_io_ptr(flush_ptr));
				out->flush();
			}
	};

	png_set_write_fn(png_ptr, reinterpret_cast<png_voidp>(&output), PNGFunctions::writeData, PNGFunctions::flushData);

	const uint32_t width = bitmap.getWidth();
	const uint32_t height = bitmap.getHeight();

	png_set_IHDR(png_ptr, info_ptr, width, height, 8, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	// Write the image.
	std::vector<png_bytep> row_pointers;
	row_pointers.reserve(height);
	const uint8_t bytes = pixelFormat.getBytesPerPixel();
	for (uint_fast32_t row = 0; row < height; ++row) {
		// Take over rows in the same order.
		row_pointers.push_back(reinterpret_cast<png_bytep>(const_cast<uint8_t *>(bitmap.data()) + row * width * bytes));
	}
	png_set_rows(png_ptr, info_ptr, row_pointers.data());

	png_write_png(png_ptr, info_ptr, transforms, nullptr);

	// Clean up.
	png_destroy_write_struct(&png_ptr, &info_ptr);

	return true;
}