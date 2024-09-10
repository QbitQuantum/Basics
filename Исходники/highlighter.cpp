bool Highlighter::eventFilter(QObject* watched, QEvent* event)
{
	if (watched != m_text->viewport() || event->type() != QEvent::ContextMenu || !m_enabled) {
		return QSyntaxHighlighter::eventFilter(watched, event);
	} else {
		// Check spelling of text block under mouse
		QContextMenuEvent* context_event = static_cast<QContextMenuEvent*>(event);
		m_start_cursor = m_text->cursorForPosition(context_event->pos());
		QTextBlock block = m_start_cursor.block();
		int cursor = m_start_cursor.position() - block.position();

		bool under_mouse = false;
		QStringRef word;
		QVector<QStringRef> words = static_cast<BlockStats*>(block.userData())->misspelled();
		for (int i = 0; i < words.count(); ++i) {
			word = words.at(i);
			int delta = cursor - word.position();
			if (delta >= 0 && delta <= word.length()) {
				under_mouse = true;
				break;
			}
		}

		if (!under_mouse) {
			return false;
		} else {
			// Select misspelled word
			m_cursor = m_start_cursor;
			m_cursor.setPosition(word.position() + block.position());
			m_cursor.setPosition(m_cursor.position() + word.length(), QTextCursor::KeepAnchor);
			m_word = m_cursor.selectedText();
			m_text->setTextCursor(m_cursor);

			// List suggestions in context menu
			QMenu* menu = new QMenu;
			QStringList guesses = m_dictionary->suggestions(m_word);
			if (!guesses.isEmpty()) {
				foreach (const QString& guess, guesses) {
                                        menu->addAction(guess);
				}
			} else {