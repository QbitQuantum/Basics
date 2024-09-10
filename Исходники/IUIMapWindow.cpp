void IUIMapWindow::start ()
{
	_startButton->setVisible(false);
	_waitLabel->setVisible(false);
	if (_cursorActive)
		showCursor(false);
	_nodeMap->start();
	Config.setBindingsSpace(BINDINGS_MAP);
}