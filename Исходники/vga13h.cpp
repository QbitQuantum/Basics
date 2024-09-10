void Vga::update() {
	SWAP(Vga::_page[0], Vga::_page[1]);

	if (_setPal) {
		updateColors();
		_setPal = false;
	}

	g_system->copyRectToScreen((const byte *)Vga::_page[0]->getBasePtr(0, 0), kScrWidth, 0, 0, kScrWidth, kScrHeight);
	g_system->updateScreen();
}