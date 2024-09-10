bool CfgParser::ReadName(const char *&p, string &name, int &index)
{
	SkipWhitesNL(p);

	const char *n_begin, *n_end;
	int _index = 0;

	n_begin = p;
	while(IsAlnum(*p) || *p == '_' || *p=='@' || *p=='$')
		p++;
	n_end = p;

	SkipWhites(p);
	if(*p=='[')
	{
		p++;
		SkipWhites(p);

        _index = ParseInt(p);
		SkipWhites(p);
		if(*p!=']') return false;
		p++;
		SkipWhites(p);
	}
	else if(*p=='*')
	{
		p++;
		_index = auto_index++;
		SkipWhites(p);
	}

	if(*p==':' || *p=='=')
		p++;
	else
	{
		SkipWhitesNL(p);
		if(*p!='{') return false;
	}

	name.assign(n_begin, n_end-n_begin);
	index = _index;

	return true;
}