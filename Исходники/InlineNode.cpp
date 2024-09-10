InlineNode::InlineNode(VRMLParser& parser)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("InlineNode::InlineNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	Vec3f bboxCenter(0.0f,0.0f,0.0f);
	Vec3f bboxSize(-1.0f,-1.0f,-1.0f);
	while(!parser.isToken("}"))
		{
		if(parser.isToken("bboxCenter"))
			{
			parser.getNextToken();
			bboxCenter=SFVec3f::parse(parser);
			}
		else if(parser.isToken("bboxSize"))
			{
			parser.getNextToken();
			bboxSize=SFVec3f::parse(parser);
			}
		else if(parser.isToken("url"))
			{
			parser.getNextToken();
			
			/* Load the external VRML file: */
			VRMLParser externalParser(parser.getFullUrl(parser.getToken()).c_str());
			
			/* Read nodes from the external VRML file until end-of-file: */
			while(!externalParser.eof())
				{
				/* Read the next node and add it to the group: */
				addChild(externalParser.getNextNode());
				}
			
			parser.getNextToken();
			}
		else
			Misc::throwStdErr("InlineNode::InlineNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	
	/* Construct the explicit bounding box: */
	setBoundingBox(bboxCenter,bboxSize);
	}