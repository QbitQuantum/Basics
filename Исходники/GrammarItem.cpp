bool	CGrammarItem::AddAttribute(string Name, string Value, MorphLanguageEnum Language, string& ErrorStr)
{
    if (Value.length() > 0) 
	    if (Value[0] == '"')
	    {
		    if ( (Value.length()<2) || (Value[Value.length() - 1] != '"'))
		    {
			    ErrorStr = Format("no matching quotation mark for attribute value \"%s\"",Value.c_str());
			    return false;
		    };
		    Value = Value.substr(1, Value.length()-2);
	    };

	if (Name == "root")
	{
		m_bSynMain = true;
		return true;
	};

	if (Name == "type")
	{
		m_TokenType = StringToTokenType(Value);
		if (m_TokenType == OTHER_TOKEN_TYPE)
		{
			ErrorStr = Format("unknown token type:%s ",Value.c_str());
			return false;
		}
	};

	if (Name == "hom")
	{
		if (Value == "yes")
			m_bCanHaveManyHomonyms = true;
		else
			if (Value == "no")
				m_bCanHaveManyHomonyms = false;
			else
			{
				ErrorStr = Format("Bad value for attribute \"hom\" (\"%s\"). It can be \"yes\" or \"no\"",Value.c_str());
				return false;
			};

		if (m_TokenType == OTHER_TOKEN_TYPE)
				m_TokenType = (Language == morphRussian) ? RLE : LLE;
		return true;
	};


	if	(Name == "grm") 
	{
		m_MorphPattern.m_GrmAttribute = Value;
		if (m_TokenType == OTHER_TOKEN_TYPE)
				m_TokenType = (Language == morphRussian) ? RLE : LLE;
		return true;
	};

	if	(Name == "form") 
	{
		m_Token = Value;
		RmlMakeUpper(m_Token, Language);
		m_ItemStrId = Value;

		if ( (m_TokenType == OTHER_TOKEN_TYPE) && !m_Token.empty())
		{
			if (ispunct((BYTE)m_Token[0]))
				m_TokenType = PUNCTUAT;
			else
			if (isdigit((BYTE)m_Token[0]))
				m_TokenType = NUM;
			else
			if (Language == morphRussian)
			{
				if (CheckLanguage(m_Token, Language))
					m_TokenType = RLE;
			}
			else
			{
				if (CheckLanguage(m_Token, Language))
					m_TokenType = LLE;
			}
		};

		return true;
	};

	if (Name == "register")
	{
		if (Value == "AA")
			m_Register = UpUp;
		else
			if (Value == "aa")
				m_Register = LowLow;
			else
			if (Value == "Aa")
				m_Register = UpLow;
			else
			{
				ErrorStr = Format("Bad value for attribute \"register\" (\"%s\"). It can be \"AA\", \"aa\" or \"Aa\"",Value.c_str());
				return false;
			};
		if (m_TokenType == OTHER_TOKEN_TYPE)
				m_TokenType = (Language == morphRussian) ? RLE : LLE;
		return true;
	};

	if (Name == "filename")
	{
		Value = GetPathByFile(CurrentSourceFileName) + Value;
		if (m_TokenType == OTHER_TOKEN_TYPE)
				m_TokenType = (Language == morphRussian) ? RLE : LLE;
	}


	m_Attributes[Name] = Value;

	return true;
};