ConeNode::ConeNode(VRMLParser& parser)
	:bottom(true),side(true),
	 height(2.0f),bottomRadius(1.0f)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("ConeNode::ConeNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("bottom"))
			{
			parser.getNextToken();
			bottom=SFBool::parse(parser);
			}
		else if(parser.isToken("side"))
			{
			parser.getNextToken();
			side=SFBool::parse(parser);
			}
		else if(parser.isToken("height"))
			{
			parser.getNextToken();
			height=SFFloat::parse(parser);
			}
		else if(parser.isToken("bottomRadius"))
			{
			parser.getNextToken();
			bottomRadius=SFFloat::parse(parser);
			}
		else
			Misc::throwStdErr("ConeNode::ConeNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}