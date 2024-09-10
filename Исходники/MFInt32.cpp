std::vector<Int32> MFInt32::parse(VRMLParser& parser)
	{
	std::vector<Int32> result;
	
	/* Check for the opening bracket: */
	if(parser.isToken("["))
		{
		/* Skip the opening bracket: */
		parser.getNextToken();
		
		/* Parse integers until closing bracket: */
		while(!parser.isToken("]"))
			{
			/* Parse and store the current token: */
			result.push_back(atoi(parser.getToken()));
			
			/* Go to the next token: */
			parser.getNextToken();
			}
		
		/* Skip the closing bracket: */
		parser.getNextToken();
		}
	else
		{
		/* Parse and store the current token: */
		result.push_back(atoi(parser.getToken()));
		
		/* Go to the next token: */
		parser.getNextToken();
		}
	
	return result;
	}