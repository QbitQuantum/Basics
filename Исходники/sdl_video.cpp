bool SDLVideo::processOneFrame(Data data) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
				SDL_RenderSetViewport(renderer, nullptr);
				displayrect->w = event.window.data1;
				displayrect->h = event.window.data2;
			}
			break;
		case SDL_QUIT:
#ifdef _MSC_VER
			GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
#else
			std::raise(SIGTERM);
#endif
			return false;
		}
	}

	auto pic = safe_cast<const DataPicture>(data);
	if (pic->getFormat() != pictureFormat) {
		pictureFormat = pic->getFormat();
		createTexture();
	}

	auto const now = m_clock->now();
	auto const timestamp = pic->getTime() + PREROLL_DELAY; // assume timestamps start at zero
	auto const delay = std::max<int64_t>(0, timestamp - now);
	auto const delayInMs = clockToTimescale(delay, 1000);
	SDL_Delay((Uint32)delayInMs);

	if (pictureFormat.format == YUV420P) {
		SDL_UpdateYUVTexture(texture, nullptr,
		                     pic->getPlane(0), (int)pic->getPitch(0),
		                     pic->getPlane(1), (int)pic->getPitch(1),
		                     pic->getPlane(2), (int)pic->getPitch(2));
	} else {
		SDL_UpdateTexture(texture, nullptr, pic->getPlane(0), (int)pic->getPitch(0));
	}
	SDL_RenderCopy(renderer, texture, nullptr, displayrect.get());
	SDL_RenderPresent(renderer);

	m_NumFrames++;

	return true;
}