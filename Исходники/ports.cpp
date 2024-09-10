void GfxPorts::endUpdate(Window *wnd) {
	Port *oldPort = setPort(_wmgrPort);
	const PortList::iterator end = _windowList.end();
	PortList::iterator it = Common::find(_windowList.begin(), end, wnd);

	// wnd has to be in _windowList
	assert(it != end);

	while (++it != end) {
		// We also store Port objects in the window list, but they
		// shouldn't be encountered during this iteration.
		assert((*it)->isWindow());

		updateWindow((Window *)*it);
	}

	if (getSciVersion() < SCI_VERSION_1_EGA_ONLY)
		g_sci->_gfxPaint16->kernelGraphRedrawBox(_curPort->rect);

	setPort(oldPort);
}