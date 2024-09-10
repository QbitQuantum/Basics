SphereNode::SphereNode(VRMLParser& parser)
	:radius(1.0f)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("SphereNode::SphereNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("radius"))
			{
			parser.getNextToken();
			radius=SFFloat::parse(parser);
			}
		else
			Misc::throwStdErr("SphereNode::SphereNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}