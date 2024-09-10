static void skipSpaces( QString::const_iterator& itr, const QString::const_iterator& end)
{
	for (; itr != end && itr->isSpace(); ++itr) {}
}