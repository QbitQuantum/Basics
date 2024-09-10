void SciDoc::stripTrailingSpaces() {
//	LOGGER;
	if ( int_->curEdit_ == NULL ) return;

	int line, col;
	getCursorPos(line, col);
	QString text = int_->curEdit_->text();
	QStringList lines = text.split(LineSeparatorRx);
	QRegExp rx("[ \t]+$");
	int i = 0;

	beginUndoAction();
	foreach (QString str, lines) {
		int pos = str.indexOf(rx);
		if ( pos >= 0 ) {
			int_->curEdit_->setSelection(i, 0, i, str.length());
			str.truncate(pos);
			replaceSelectedText(str);
		}
		++i;
	}