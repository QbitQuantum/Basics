static int ReadList(playlist* p,tchar_t* Path,int PathLen,tchar_t* DispName,int DispNameLen,tick_t* Length)
{
	tchar_t s[MAXLINE];

	DispName[0] = 0;
	*Length = -1;

	while (ParserLine(&p->Parser,s,MAXLINE))
	{
		if (s[0]=='#')
		{
			tcsuprto(s,':');
			if (stscanf(s,T("#EXTINF: %d ,"),Length)==1)
			{
				tchar_t* p = tcschr(s,',');
				if (p++)
				{
					while (IsSpace(*p)) ++p;
					tcscpy_s(DispName,DispNameLen,p);
				}
				if (*Length >= 0)
					*Length *= TICKSPERSEC;
			}
		}
		else
		if (s[0])
		{
			tcscpy_s(Path,PathLen,s);
			return ERR_NONE;
		}
	}

	return ERR_END_OF_FILE;
}