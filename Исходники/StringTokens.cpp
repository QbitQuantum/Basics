// string tokenizer constructor and destructor
StringTokens::StringTokens(const String &s, const String &d):
	tokenStart(0), tokenEnd(0),
	stringLength(s.strlen()), delimiterLength(d.strlen()),
	string(s), delimiter(d)
{
	// sanity check
	MustBeTrue(delimiterLength > 0);

	// skip leading delimiters
	int is;
	for (is = 0; is < stringLength; is++)
	{
		int match = 0;
		for (int id = 0; id < delimiterLength; id++)
		{
			if (string[is] == delimiter[id])
			{
				match = 1;
				break;
			}
		}
		if (!match) break;
	}
	tokenStart = is;

	// find end of token
	int ie;
	for (ie = tokenStart; ie < stringLength; ie++)
	{
		int match = 0;
		for (int id = 0; id < delimiterLength; id++)
		{
			if (string[ie] == delimiter[id])
			{
				match = 1;
				break;
			}
		}
		if (match) break;
	}
	tokenEnd = ie;
}