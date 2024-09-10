WZSMDToken ScriptEncode::GetToken()
{
	char ch;
	TokenString[0] = '\0';
	do
	{
		if ( (ch =(char) GetC() ) == EOF) return T_END;

		if (ch == '/')
		{
			if ((ch =(char) GetC() )=='/')	
			{
				while ((ch != '\n') && (ch != EOF))	ch =(char) GetC();
			}
		}
	} while(  isspace(ch) );

	char *p, TempString[100];
	switch(ch)
	{	
	case '#':
		return CurrentToken = T_COMMAND;
	case ';':
		return CurrentToken = T_SEMICOLON;
	case ',':
		return CurrentToken = T_COMMA;
	case '{':
		return CurrentToken = T_LP;
	case '}':
		return CurrentToken = T_RP;
	case '0':	case '1':	case '2':	case '3':	case '4':
	case '5':	case '6':	case '7':	case '8':	case '9':
	case '.':	case '-':
		UnGetC(ch);
		p = TempString;
		while ( (  (ch = GetC() ) !=EOF) && (ch=='.' || isdigit(ch) || ch=='-') )
			*p++ = ch;
		*p = 0;
		TokenNumber = (float)atof(TempString);
		return CurrentToken = T_NUMBER;
	case '"':
		p = TokenString;
		while ( (  (ch = GetC() ) !=EOF) && (ch!='"'))
			*p++ = ch;
		if (ch!='"')
			UnGetC(ch);
		*p = 0;
		return CurrentToken = T_NAME;
	default:
		if (isalpha(ch))	
		{
			p = TokenString;
			*p++ = ch;
			while ( (  (ch = GetC() ) !=EOF) && (ch=='.' || ch=='_' || isalnum(ch)) )
				*p++ = ch;
			UnGetC(ch);
			*p = 0;
			return CurrentToken = T_NAME;
		}
		return CurrentToken = T_SMD_ERROR;
	}
}