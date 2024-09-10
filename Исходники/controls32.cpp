void GfxControls32::destroyScrollWindow(const reg_t id) {
	ScrollWindow *scrollWindow = getScrollWindow(id);
	scrollWindow->hide();
	_scrollWindows.erase(id.getOffset());
	delete scrollWindow;
}