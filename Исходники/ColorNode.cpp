ColorNode::ColorNode(VRMLParser& parser)
	:VRMLNode(parser)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("ColorNode::ColorNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("color"))
			{
			/* Parse the color array: */
			parser.getNextToken();
			colors=MFColor::parse(parser);
			}
		else
			Misc::throwStdErr("ColorNode::ColorNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	
	}