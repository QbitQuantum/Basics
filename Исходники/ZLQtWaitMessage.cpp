ZLQtWaitMessage::~ZLQtWaitMessage() {
	if (myCursorIsStored) {
		QWidget *main = qApp->mainWidget();
		if (main != 0) {
			main->setCursor(myStoredCursor);
		}
	}
}