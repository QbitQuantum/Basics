Int32 SFInt32::parse(VRMLParser& parser)
	{
	Int32 result;
	
	/* Parse the current token: */
	result=atoi(parser.getToken());
	
	/* Go to the next token: */
	parser.getNextToken();
	
	return result;
	}