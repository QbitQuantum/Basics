static QString charFilterRegExp(QString const & filter)
{
	QString re;
	for (int i = 0; i < filter.length(); ++i) {
		QChar c = filter[i];
		if (c.isLower())
			re += ".*[" + QRegExp::escape(c) + QRegExp::escape(c.toUpper()) + "]";
		else
			re += ".*" + QRegExp::escape(c);
	}
	return re;
}