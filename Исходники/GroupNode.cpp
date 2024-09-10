GroupNode::GroupNode(VRMLParser& parser)
	:haveBoundingBox(false),
	 boundingBox(Box::empty)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("GroupNode::GroupNode: Missing opening brace in node definition, have %s instead",parser.getToken());
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
		else if(parser.isToken("children"))
			{
			/* Parse the node's children: */
			parseChildren(parser);
			}
		else
			Misc::throwStdErr("GroupNode::GroupNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	
	/* Construct the explicit bounding box: */
	setBoundingBox(bboxCenter,bboxSize);
	}