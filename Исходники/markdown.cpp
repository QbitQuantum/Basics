CMarkdown::HSTR CMarkdown::GetInnerText()
{
	Scan();
	const char *p = first;
	const char *q = upper;
	char bracket = '>';
	if (p < upper && ++p < upper && *p == '!' && ++p < upper)
	{
		bracket = *p;
		if (bracket != '-')
		{
			bracket = '[';
		}
	}
	p = lower;
	unsigned quoting = 0;
	while (p < upper && (quoting || *p != bracket))
	{
		switch (*p)
		{
		case '"':
			if (!(quoting & 1))
				quoting ^= 2;
			break;
		case '\'': 
			if (!(quoting & 2))
				quoting ^= 1;
			break;
		}
		++p;
	}
	if (p < q && p < --q && p < --q)
	{
		++p;
	}
	return (HSTR)SysAllocStringByteLen(p, q - p);
}