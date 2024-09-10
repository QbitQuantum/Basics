void BlockStats::update(const QString& text)
{
	m_checked = Unchecked;
	m_characters = text.length();
	m_spaces = 0;
	m_words = 0;
	bool word = false;
	QString::const_iterator end = text.constEnd();
	for (QString::const_iterator i = text.constBegin(); i != end; ++i) {
		if (i->isLetterOrNumber() || i->category() == QChar::Punctuation_Dash) {
			if (word == false) {
				word = true;
				m_words++;
			}
		} else if (i->isSpace()) {
			word = false;
			m_spaces++;
		} else if (*i != 0x2019 && *i != 0x0027) {
			word = false;
		}
	}
}