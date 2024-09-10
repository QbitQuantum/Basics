void Lexeme::PrintValue(FILE* F)
{
	if (type == TypeInteger)
		fprintf_s(F, "\t%s", text.c_str());
	if (type == TypeReal)
		fprintf_s(F, "\t%.4e", atof(text.c_str()));
	if (type == TypeString)
		fprintf_s(F, "\t%s", text.substr(1, text.length() - 2).c_str());
	if (type == TypeChar)
	{
		if (text[0] == '\'')
			return;
		if (text[1] == '$') //hex
			fprintf_s(F, "\t%c", atoi(FromHexToInt(text.substr(2, text.length() - 2)).c_str()));
		else
			fprintf(F, "\t%c", atoi(text.substr(1, text.length() - 1).c_str()));
	}
	if (type == TypeHex)
		fprintf_s(F, "\t%s", FromHexToInt(text).c_str());
	return;
}