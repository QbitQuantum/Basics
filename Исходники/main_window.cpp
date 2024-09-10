MainWindow::MainWindow() : QWidget()
, _positionUpdatedTimer(this)
, _body(this)
, _icon(CreateIcon())
, _titleText(qsl("Telegram")) {
	subscribe(Theme::Background(), [this](const Theme::BackgroundUpdate &data) {
		if (data.paletteChanged()) {
			if (_title) {
				_title->update();
			}
			updatePalette();
		}
	});
	subscribe(Global::RefUnreadCounterUpdate(), [this] { updateUnreadCounter(); });
	subscribe(Global::RefWorkMode(), [this](DBIWorkMode mode) { workmodeUpdated(mode); });
	subscribe(Messenger::Instance().authSessionChanged(), [this] { checkAuthSession(); });
	checkAuthSession();

	_isActiveTimer.setCallback([this] { updateIsActive(0); });
	_inactivePressTimer.setCallback([this] { setInactivePress(false); });
}