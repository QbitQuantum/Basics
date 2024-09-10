static QString makeMixedCaseHeader(const QString &s)
{
	QString out;
	for(int n = 0; n < s.length(); ++n)
	{
		QChar c = s[n];
		if(n == 0 || (n - 1 >= 0 && s[n - 1] == '-'))
			out += c.toUpper();
		else
			out += c;
	}

	return out;
}