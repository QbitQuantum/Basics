void RequestManager::init() {
	clearList();

	if (!createThread())
		throw Common::Exception("Failed to create requests thread: %s", SDL_GetError());
}