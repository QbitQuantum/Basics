QString CWidgetReturnEmitTextEdit::textUnderCursor() const
{
	QTextCursor tc = textCursor();
	tc.select(QTextCursor::WordUnderCursor);

	// Save selected positions of current word.
	int selectionStart = tc.selectionStart();
	int selectionEnd = tc.selectionEnd();

	// If selection is at beginning of text edit then there can't be a slash to check for
	if (selectionStart == 0)
		return tc.selectedText();

	// Modify selection to include previous character
	tc.setPosition(selectionStart - 1, QTextCursor::MoveAnchor);
	tc.setPosition(selectionEnd, QTextCursor::KeepAnchor);

	// If previous character was / return current selection for command completion
	if(tc.selectedText().startsWith('/'))
		return tc.selectedText();
	else {
		// Else restore original selection and return for nick completion
		tc.setPosition(selectionStart, QTextCursor::MoveAnchor);
		tc.setPosition(selectionEnd, QTextCursor::KeepAnchor);
		return tc.selectedText();
	}
}