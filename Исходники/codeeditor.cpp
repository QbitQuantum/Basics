void CodeEditor::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    	case Qt::Key_Return:
		case Qt::Key_Enter:
		{
			QTextCursor tc = textCursor();
			QString t = tc.block().text();
			QString spaces;
			QChar *data = t.data();
			while (!data->isNull() && data->isSpace()) {
				spaces.append(*data);
				++data;
			}
			QPlainTextEdit::keyPressEvent(event);
			insertPlainText(spaces);
		}
        break;
		case Qt::Key_F1:
			insertPlainText("\t");
			break;

		default:
			QPlainTextEdit::keyPressEvent(event);
    }
}