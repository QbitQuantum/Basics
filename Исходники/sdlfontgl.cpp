void SDLFontGL::setupColors(std::vector<SDL_Color> colors) {
	assert(!colors.empty());
	m_colors = colors;

	updateColors();
	// cursor does a manual color lookup
	updateCursor();
}