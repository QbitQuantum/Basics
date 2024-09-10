void SpellChecker::check()
{
	setDisabled(true);
	QProgressDialog wait_dialog(tr("Checking spelling..."), tr("Cancel"), 0, m_document->document()->characterCount(), this);
	wait_dialog.setWindowTitle(tr("Please wait"));
	wait_dialog.setValue(0);
	wait_dialog.setWindowModality(Qt::WindowModal);

	forever {
		// Update wait dialog
		wait_dialog.setValue(m_cursor.position());
		if (wait_dialog.wasCanceled()) {
			m_document->setTextCursor(m_start_cursor);
			reject();
		}

		// Check current line
		QTextBlock block = m_cursor.block();
		QStringRef word =  m_dictionary->check(block.text(), m_cursor.position() - block.position());
		if (word.isNull()) {
			if (block.next().isValid()) {
				m_cursor.movePosition(QTextCursor::NextBlock);
				continue;
			} else {
				break;
			}
		}

		// Select misspelled word
		m_cursor.setPosition(word.position() + block.position());
		m_cursor.setPosition(m_cursor.position() + word.length(), QTextCursor::KeepAnchor);
		m_word = m_cursor.selectedText();

		if (!m_ignored.contains(m_word)) {
			wait_dialog.close();
			setEnabled(true);

			// Show misspelled word in context
			QTextCursor cursor = m_cursor;
			cursor.movePosition(QTextCursor::PreviousWord, QTextCursor::MoveAnchor, 10);
			int end = m_cursor.position() - cursor.position();
			int start = end - m_word.length();
			cursor.movePosition(QTextCursor::NextWord, QTextCursor::KeepAnchor, 21);
			QString context = cursor.selectedText();
			context.insert(end, "</span>");
			context.insert(start, "<span style=\"color: red;\">");
			context.replace("\n", "</p><p>");
			context.replace("\t", "<span style=\"white-space: pre;\">\t</span>");
			context = "<p>" + context + "</p>";
			m_context->setHtml(context);

			// Show suggestions
			m_suggestion->clear();
			m_suggestions->clear();
			QStringList words = m_dictionary->suggestions(m_word);
			if (!words.isEmpty()) {
				foreach (const QString& word, words) {
					m_suggestions->addItem(word);
				}
				m_suggestions->setCurrentRow(0);
			}