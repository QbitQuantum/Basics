void NormalWindow::saveWindowGeometryAndState()
{
	if (isWindow())
	{
		Options::setFileValue(saveState(),"messages.messagewindow.state",tabPageId());
		Options::setFileValue(saveGeometry(),"messages.messagewindow.geometry",tabPageId());
	}
	Options::setFileValue(ui.sprReceivers->saveState(),"messages.messagewindow.splitter-receivers-state");
}