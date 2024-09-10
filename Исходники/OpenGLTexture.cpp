void OpenGlTexture::updateLevel(uint32 level, const Graphics::Surface *surface, const byte *palette) {
	if (level == 0) {
		_width = surface->w;
		_height = surface->h;
	}

	if (surface->format.bytesPerPixel != 4) {
		// Convert the surface to texture format
		Graphics::Surface *convertedSurface = surface->convertTo(Graphics::PixelFormat(4, 8, 8, 8, 8, 0, 8, 16, 24), palette);

		glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, convertedSurface->w, convertedSurface->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, convertedSurface->getPixels());

		convertedSurface->free();
		delete convertedSurface;
	} else {
		glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, surface->getPixels());
	}
}