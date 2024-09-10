void CSTimeGraphics::drawRect(Common::Rect rect, byte color) {
	rect.clip(Common::Rect(640, 480));

	// Useful with debugging. Shows where hotspots are on the screen and whether or not they're active.
	if (!rect.isValidRect() || rect.width() == 0 || rect.height() == 0)
		return;

	Graphics::Surface *screen = _vm->_system->lockScreen();

	screen->frameRect(rect, color);

	_vm->_system->unlockScreen();
}