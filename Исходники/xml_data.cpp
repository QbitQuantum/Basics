char * TXML_Data::FindBlank(char * pChar, int iParsingSign)
{
	iParsingSign = static_cast<int>(copysignf(1.0f, static_cast<float>(iParsingSign)));

	char * pNextChar = pChar + iParsingSign;

	for (int i = 0;; i += iParsingSign)
	{
		if (isspace(pNextChar[i]))
		{
			return &pNextChar[i];
		}
	}
}