void RivenGraphics::drawRect(Common::Rect rect, bool active) {
	// Useful with debugging. Shows where hotspots are on the screen and whether or not they're active.
	Graphics::Surface *screen = _vm->_system->lockScreen();

	if (active)
		screen->frameRect(rect, _pixelFormat.RGBToColor(0, 255, 0));
	else
		screen->frameRect(rect, _pixelFormat.RGBToColor(255, 0, 0));

	_vm->_system->unlockScreen();
}