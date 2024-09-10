void ElementTitle::startTextInteraction()
{
	// Already interacting?
	if (hasFocus())
		return;

	mOldText = toHtml();

	// Clear scene selection
	//if (!(event->modifiers() & Qt::ControlModifier)) - was here.
	scene()->clearSelection();
	parentItem()->setSelected(true);

	if (mReadOnly)
		setTextInteractionFlags(Qt::TextBrowserInteraction);
	else
		setTextInteractionFlags(Qt::TextEditorInteraction);
	setFocus(Qt::OtherFocusReason);

	// Set full text selection
	QTextCursor cursor = QTextCursor(document());
	cursor.select(QTextCursor::Document);
	setTextCursor(cursor);
	setCursor(Qt::IBeamCursor);
}