void MenuMainScreen::setCurrentOption(QGraphicsSimpleTextItem *option) {
	QBrush whiteBrush(Qt::white);
	QBrush yellowBrush(Qt::yellow);

	if (!!_currentOption)
		_currentOption->setBrush(whiteBrush);

	_currentOption = option;
	_currentOption->setBrush(yellowBrush);

	if (option->text() == QString("Character"))
		_textField->setPlainText("View more information about the selected character.");
	else if (option->text() == QString("Equipment"))
		_textField->setPlainText("View or change the equipment the selected character is wearing.");
	else if (option->text() == QString("Abilities"))
		_textField->setPlainText("View the abilities of the selected character.");
	else if (option->text() == QString("Inventory"))
		_textField->setPlainText("View the items collected by the party.");
	else if (option->text() == QString("Exit"))
		_textField->setPlainText("Exit the menu.");

	QFont font("Times", 12, QFont::Bold);
	_textField->setFont(font);

	QTextBlockFormat format;
	format.setAlignment(Qt::AlignLeft);
	QTextCursor cursor = _textField->textCursor();
	cursor.select(QTextCursor::Document);
	cursor.mergeBlockFormat(format);
	cursor.clearSelection();
	_textField->setTextCursor(cursor);
}