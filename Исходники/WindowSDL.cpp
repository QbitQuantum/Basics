//! ---|> Window
void WindowSDL::doHideCursor() {
	static std::unique_ptr<Cursor> hiddenCursor;
	if(hiddenCursor.get() == nullptr) {
		Reference<Bitmap> bitmap = new Bitmap(1, 1);
		bitmap->data()[0] = 0;
		bitmap->data()[1] = 0;
		bitmap->data()[2] = 0;
		bitmap->data()[3] = 0;
		hiddenCursor = createCursor(bitmap, 0, 0);
	}
	doSetCursor(hiddenCursor.get());
}