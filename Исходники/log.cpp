// Strip special controle char, like color, bold, ...
CString CLogMod::Sanitize(const CString& sLine)
{
	unsigned int i,l;

	// Color codes format (regex): \x03([0-9]{1,2}(,[0-9]{1,2})?)?
	// e: escape, if true, we have met an escape char (\x03) and are still striping.
	bool e;
	// c: comma, if we passed the comma yet or not
	bool c;
	// d: the number of digits we already striped (maximum 2 each time)
	unsigned int d=0;

	CString sRet;
	l = sLine.length();
	sRet.reserve(l);
	e=false;
	d=0;
	c=false;
	for(i=0; i<l; i++)
	{
		unsigned char ch = sLine[i];
		switch (ch)
		{
			case '\x02': // Bold
			case '\x0f': // Reset
			case '\x12': // Reverse Color
			case '\x15': // Underline
			case '\x16': // Reverse
			case '\x1D': // Italic
			case '\x1f': // Underline
				continue;
			case '\x03': // Color
				e=true;
				d=0;
				c=false;
				continue;
			case ',':
				if (e)
				{
					if(!c && d>0)
					{
						c=true;
						d=0;
						continue;
					}
				}
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (e && d <2)
				{
					d++;
					continue;
				}
			default:
				e=false;
				sRet += ch;
		}
	}
	sRet.reserve(0);
	return sRet;
}