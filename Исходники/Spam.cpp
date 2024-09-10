int Spam::GetSpamNick(char ** nicks, char *test)
{
	int j_st, w_fill, c_nick = 0;
	char *oth;

	for(int i = 0; i < strlen(test); i++)
	{
		if(test[i] == '3' && test[i+1] == '5' && test[i+2] == '3')
		{	
			j_st = i;
			w_fill = 0;
			oth = new char[1024];
			strnset(oth, '\0', 1024);

			for(int j = j_st; j < strlen(test); j++)
			{
				oth[w_fill] = test[j];
				w_fill++;
			}
		}
	}

	string nick;
	char *a1, *a2;
	a1 = oth; a2 = oth;

	while(*a2 && !strchr(":", *a2))
		++a2;
	nick.assign(a1, a2 - a1);
	if(*a2 != ':')
		a1 = ++a2;
    a1 = ++a2;

	while(*a2 != ':')
	{
		while(*a2 && !strchr(" ", *a2))
			++a2;
		nick.assign(a1, a2 - a1);
		if(*a2 != isspace(*a2))
			a1 = ++a2;

		char *tmp_nick = new char[strlen(nick.c_str())];
		strnset(tmp_nick, '\0', strlen(nick.c_str()));
		strcpy(tmp_nick, nick.c_str());

		nicks[c_nick] = tmp_nick;
		c_nick++;
	}

	return c_nick;
}