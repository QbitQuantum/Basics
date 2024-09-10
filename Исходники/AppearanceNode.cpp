AppearanceNode::AppearanceNode(VRMLParser& parser)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("AppearanceNode::AppearanceNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("material"))
			{
			/* Parse the material node: */
			parser.getNextToken();
			material=parser.getNextNode();
			}
		else if(parser.isToken("texture"))
			{
			/* Parse the texture node: */
			parser.getNextToken();
			texture=parser.getNextNode();
			}
		else if(parser.isToken("textureTransform"))
			{
			/* Parse the texture transformation node: */
			parser.getNextToken();
			textureTransform=parser.getNextNode();
			}
		else
			Misc::throwStdErr("AppearanceNode::AppearanceNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}