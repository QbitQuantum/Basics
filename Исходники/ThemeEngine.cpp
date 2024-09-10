ThemeEngine::~ThemeEngine() {
	delete _vectorRenderer;
	_vectorRenderer = 0;
	_screen.free();
	_backBuffer.free();

	unloadTheme();

	// Release all graphics surfaces
	for (ImagesMap::iterator i = _bitmaps.begin(); i != _bitmaps.end(); ++i) {
		Graphics::Surface *surf = i->_value;
		if (surf) {
			surf->free();
			delete surf;
		}
	}
	_bitmaps.clear();

	delete _parser;
	delete _themeEval;
	delete[] _cursor;
	delete _themeArchive;
}