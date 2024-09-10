IndexedLineSetNode::IndexedLineSetNode(VRMLParser& parser)
	:colorPerVertex(true)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("IndexedLineSetNode::IndexedLineSetNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("colorPerVertex"))
			{
			parser.getNextToken();
			colorPerVertex=SFBool::parse(parser);
			}
		else if(parser.isToken("color"))
			{
			/* Parse the color node: */
			parser.getNextToken();
			color=parser.getNextNode();
			}
		else if(parser.isToken("coord"))
			{
			/* Parse the coordinate node: */
			parser.getNextToken();
			coord=parser.getNextNode();
			}
		else if(parser.isToken("colorIndex"))
			{
			/* Parse the color index array: */
			parser.getNextToken();
			colorIndices=MFInt32::parse(parser);
			}
		else if(parser.isToken("coordIndex"))
			{
			/* Parse the coordinate index array: */
			parser.getNextToken();
			coordIndices=MFInt32::parse(parser);
			
			/* Terminate the coordinate index array: */
			if(coordIndices.back()>=0)
				coordIndices.push_back(-1);
			}
		else if(parser.isToken("indexedLineSetReader"))
			{
			/* Parse the indexed line set reader node: */
			parser.getNextToken();
			VRMLNodePointer indexedLineSetReader=parser.getNextNode();
			IndexedLineSetReaderNode* ilsrn=dynamic_cast<IndexedLineSetReaderNode*>(indexedLineSetReader.getPointer());
			if(ilsrn!=0)
				{
				coord=new CoordinateNode;
				coordIndices.clear();
				if(ilsrn->hasColors())
					color=new ColorNode;
				colorIndices.clear();
				ilsrn->readIndexedLines(dynamic_cast<CoordinateNode*>(coord.getPointer()),coordIndices,dynamic_cast<ColorNode*>(color.getPointer()),colorIndices);
				}
			}
		else
			Misc::throwStdErr("IndexedLineSetNode::IndexedLineSetNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}