bool CFileListItemDelegate::eventFilter(QObject * object, QEvent * event)
{
	QWidget *editor = qobject_cast<QWidget*>(object);
	if (!editor)
		return false;

	if (event->type() == QEvent::KeyPress)
	{
		switch (static_cast<QKeyEvent *>(event)->key())
		{
		case Qt::Key_Tab:
			emit closeEditor(editor, EditNextItem);
			return true;
		case Qt::Key_Backtab:
			emit closeEditor(editor, EditPreviousItem);
			return true;
		case Qt::Key_Enter: // Numpad Enter
		case Qt::Key_Return:
			// don't filter enter key events for QTextEdit
			if (!qobject_cast<QTextEdit *>(editor) && !qobject_cast<QPlainTextEdit*>(editor))
			{
				// commit data
				emit commitData(editor);
				emit closeEditor(editor);
				return true;
			}

			return QStyledItemDelegate::eventFilter(object, event);
		case Qt::Key_Escape:
			// don't commit data
			emit closeEditor(editor, QAbstractItemDelegate::RevertModelCache);
			return true;
		case Qt::Key_Up:
		case Qt::Key_Down:
			// don't commit data
			emit closeEditor(editor, QAbstractItemDelegate::RevertModelCache);
			// Don't consume the event so that the TreeView will handle this event and highlight the next item properly
			return QStyledItemDelegate::eventFilter(object, event);
		default:
			return QStyledItemDelegate::eventFilter(object, event);
		}
	}
	else if (event->type() == QEvent::FocusOut || (event->type() == QEvent::Hide && editor->isWindow()))
	{
		//the Hide event will take care of he editors that are in fact complete dialogs
		if (!editor->isActiveWindow() || (QApplication::focusWidget() != editor))
		{
			QWidget *w = QApplication::focusWidget();
			while (w)
			{ // don't worry about focus changes internally in the editor
				if (w == editor)
					return QStyledItemDelegate::eventFilter(object, event);

				w = w->parentWidget();
			}

			emit closeEditor(editor, NoHint);
		}
	}
	else if (event->type() == QEvent::ShortcutOverride)
	{
		if (static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape)
		{
			event->accept();
			return true;
		}
	}

	return QStyledItemDelegate::eventFilter(object, event);
}