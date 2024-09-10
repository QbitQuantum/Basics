/**
 * Handles changes in the cursor position.
 * Emits a signal with the new line and column numbers.
 */
void EditorPage::slotCursorPosChange()
{
	uint nLine, nCol;
	
	// Find the new line and column number, and emit the signal
	if (!getCursorPos(nLine, nCol))
		return;
		
	emit cursorPosChanged(nLine, nCol);
	
	// Select the relevant symbol in the tag list
	if (Config().getAutoTagHl() && (m_nLine != nLine)) {
		m_pCtagsList->gotoLine(nLine);
		m_nLine = nLine;
	}
	
	// Abort code completion on cursor changes during the completion
	// process
	m_pCompletion->abort();
}