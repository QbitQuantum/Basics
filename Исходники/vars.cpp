int Vars::LoadFromFile(char *filename)
{
	char buffer[256];
	Parser parser;

	if (!parser.StartParseFile(filename)) return 0;

	gCommands->AddToConsole = false;

	while (parser.GetToken())
	{
		// if the variable exist
		if (isKey(parser.token))
		{
			strncpy(buffer, parser.token, 256);
			parser.GetToken();
			SetKeyValue(buffer, parser.token);
		}
		while (parser.GetToken(false));	// get to next line
	}
	parser.StopParse();

	gCommands->AddToConsole = true;
	return 1;
}