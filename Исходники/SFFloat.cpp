Float SFFloat::parse(VRMLParser& parser)
	{
	Float result;
	
	/* Parse the current token: */
	result=float(atof(parser.getToken()));
	
	/* Go to the next token: */
	parser.getNextToken();
	
	return result;
	}