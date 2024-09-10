	void SurfaceSDL::writePixels(int bpp, 
		uint32_t rmask, 
		uint32_t gmask, 
		uint32_t bmask, 
		uint32_t amask,
		const void* pixels)
	{
		SDL_FreeSurface(surface_);
		ASSERT_LOG(pixels != nullptr, "nullptr value for pixels while creating surface.");
		surface_ = SDL_CreateRGBSurfaceFrom(const_cast<void*>(pixels), width(), height(), bpp, rowPitch(), rmask, gmask, bmask, amask);
		ASSERT_LOG(surface_ != nullptr, "Error creating surface: " << SDL_GetError());
		setPixelFormat(PixelFormatPtr(new SDLPixelFormat(surface_->format->format)));
	}