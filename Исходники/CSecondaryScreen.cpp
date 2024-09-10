void
CSecondaryScreen::leave()
{
	LOG((CLOG_INFO "leaving screen"));
	CLock lock(&m_mutex);
	assert(m_active == true);

	getScreen()->syncDesktop();

	// subclass hook
	onPreLeave();

	// restore toggle key state
	setToggleState(m_toggleKeys);

	// warp and hide mouse
	SInt32 x, y;
	getScreen()->getCursorCenter(x, y);
	showWindow(x, y);

	// subclass hook
	onPostLeave();

	// not active anymore
	m_active = false;

	// make sure our idea of clipboard ownership is correct
	getScreen()->checkClipboards();
}