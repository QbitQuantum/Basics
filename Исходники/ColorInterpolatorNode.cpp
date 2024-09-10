ColorInterpolatorNode::ColorInterpolatorNode(VRMLParser& parser)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("ColorInterpolatorNode::ColorInterpolatorNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("key"))
			{
			/* Read the array of key values: */
			parser.getNextToken();
			key=MFFloat::parse(parser);
			}
		else if(parser.isToken("keyValue"))
			{
			/* Read the array of control points: */
			parser.getNextToken();
			keyValue=MFColor::parse(parser);
			}
		else
			Misc::throwStdErr("ColorInterpolatorNode::ColorInterpolatorNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}