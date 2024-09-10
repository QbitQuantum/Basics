TextureTransformNode::TextureTransformNode(VRMLParser& parser)
	:center(0.0f,0.0f),
	 rotation(0.0f),
	 scale(1.0f,1.0f),
	 translation(0.0f,0.0f)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("TextureTransformNode::TextureTransformNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("center"))
			{
			parser.getNextToken();
			center=SFVec2f::parse(parser);
			}
		else if(parser.isToken("rotation"))
			{
			parser.getNextToken();
			rotation=SFFloat::parse(parser);
			}
		else if(parser.isToken("scale"))
			{
			parser.getNextToken();
			scale=SFVec2f::parse(parser);
			}
		else if(parser.isToken("translation"))
			{
			parser.getNextToken();
			translation=SFVec2f::parse(parser);
			}
		else
			Misc::throwStdErr("TextureTransformNode::TextureTransformNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}