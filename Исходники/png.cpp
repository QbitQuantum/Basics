bool writePNG(Common::WriteStream &out, const Graphics::Surface &input, const bool bottomUp) {
#ifdef USE_PNG
	const Graphics::PixelFormat requiredFormat_3byte(3, 8, 8, 8, 0, 16, 8, 0, 0);
	const Graphics::PixelFormat requiredFormat_4byte(4, 8, 8, 8, 8, 0, 8, 16, 24);

	if (input.format.bytesPerPixel == 3) {
		if (input.format != requiredFormat_3byte) {
			warning("Cannot currently write PNG with 3-byte pixel format other than %s", requiredFormat_3byte.toString().c_str());
			return false;
		}
	} else if (input.format.bytesPerPixel != 4) {
		warning("Cannot currently write PNG with pixel format of bpp other than 3, 4");
		return false;
	}

	int colorType;
	Graphics::Surface *tmp = NULL;
	const Graphics::Surface *surface;

	if (input.format == requiredFormat_3byte) {
		surface = &input;
		colorType = PNG_COLOR_TYPE_RGB;
	} else {
		if (input.format == requiredFormat_4byte) {
			surface = &input;
		} else {
			surface = tmp = input.convertTo(requiredFormat_4byte);
		}
		colorType = PNG_COLOR_TYPE_RGB_ALPHA;
	}

	png_structp pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pngPtr) {
		return false;
	}
	png_infop infoPtr = png_create_info_struct(pngPtr);
	if (!infoPtr) {
		png_destroy_write_struct(&pngPtr, NULL);
		return false;
	}

	png_set_error_fn(pngPtr, NULL, pngError, pngWarning);
	// TODO: The manual says errors should be handled via setjmp

	png_set_write_fn(pngPtr, &out, pngWriteToStream, pngFlushStream);

	png_set_IHDR(pngPtr, infoPtr, surface->w, surface->h, 8, colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	Common::Array<const uint8 *> rows;
	rows.reserve(surface->h);
	if (bottomUp) {
		for (uint y = surface->h; y-- > 0;) {
			rows.push_back((const uint8 *)surface->getBasePtr(0, y));
		}
	} else {
		for (uint y = 0; y < surface->h; ++y) {
			rows.push_back((const uint8 *)surface->getBasePtr(0, y));
		}
	}

	png_set_rows(pngPtr, infoPtr, const_cast<uint8 **>(&rows.front()));
	png_write_png(pngPtr, infoPtr, 0, NULL);
	png_destroy_write_struct(&pngPtr, &infoPtr);

	// free tmp surface
	if (tmp) {
		tmp->free();
		delete tmp;
	}

	return true;
#else
	return false;
#endif
}