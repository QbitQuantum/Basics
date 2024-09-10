void SysmgrIMEModel::sendKeyEvent(QEvent::Type type, Qt::Key key, Qt::KeyboardModifiers modifiers)
{
    QWidget* focusedWidget = QApplication::focusWidget();
    if (focusedWidget && (type == QEvent::KeyPress || type == QEvent::KeyRelease)) {
		QChar qchar;
		switch(key) {
		case Qt::Key_Return:
		case Qt::Key_Enter:
			qchar = '\r';
			break;
		case Qt::Key_Tab:
			qchar = '\t';
			break;
		case Qt::Key_Backspace:
			qchar = '\b';
			break;
		default:
			qchar = QChar(key);
		}

		// only lower case A to Z. Other keys are unicode characters with proper casing already...
		if (key >= Qt::Key_A && key <= Qt::Key_Z && !(modifiers & Qt::ShiftModifier))
			qchar = qchar.toLower();
		QApplication::postEvent(focusedWidget, new QKeyEvent(type, key, modifiers, qchar));
    }
}