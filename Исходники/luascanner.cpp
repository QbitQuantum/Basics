FormatToken Scanner::readOperator()
{
	QString const EXCLUDED_CHARS = QLatin1String("\"'_");
	QChar ch = m_src.peek();
	while(ch.isPunct() && !EXCLUDED_CHARS.contains(ch)) {
		if(ch == QLatin1Char('-') && m_src.peek(1) == QLatin1Char('-'))
			break;
		m_src.move();
		ch = m_src.peek();
	}
	return FormatToken(Format_Operator, m_src.anchor(), m_src.length());
}