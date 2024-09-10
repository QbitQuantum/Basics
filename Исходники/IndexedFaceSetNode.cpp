IndexedFaceSetNode::IndexedFaceSetNode(VRMLParser& parser)
	:ccw(true),solid(true),convex(true),
	 colorPerVertex(true),
	 normalPerVertex(true),creaseAngle(0.0f)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("IndexedFaceSetNode::IndexedFaceSetNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("ccw"))
			{
			parser.getNextToken();
			ccw=SFBool::parse(parser);
			}
		else if(parser.isToken("solid"))
			{
			parser.getNextToken();
			solid=SFBool::parse(parser);
			}
		else if(parser.isToken("convex"))
			{
			parser.getNextToken();
			convex=SFBool::parse(parser);
			}
		else if(parser.isToken("colorPerVertex"))
			{
			parser.getNextToken();
			colorPerVertex=SFBool::parse(parser);
			}
		else if(parser.isToken("normalPerVertex"))
			{
			parser.getNextToken();
			normalPerVertex=SFBool::parse(parser);
			}
		else if(parser.isToken("creaseAngle"))
			{
			parser.getNextToken();
			creaseAngle=SFFloat::parse(parser);
			}
		else if(parser.isToken("texCoord"))
			{
			/* Parse the texture coordinate node: */
			parser.getNextToken();
			texCoord=parser.getNextNode();
			}
		else if(parser.isToken("color"))
			{
			/* Parse the color node: */
			parser.getNextToken();
			color=parser.getNextNode();
			}
		else if(parser.isToken("normal"))
			{
			/* Parse the normal node: */
			parser.getNextToken();
			normal=parser.getNextNode();
			}
		else if(parser.isToken("coord"))
			{
			/* Parse the coordinate node: */
			parser.getNextToken();
			coord=parser.getNextNode();
			}
		else if(parser.isToken("texCoordIndex"))
			{
			/* Parse the texture coordinate index array: */
			parser.getNextToken();
			texCoordIndices=MFInt32::parse(parser);
			}
		else if(parser.isToken("colorIndex"))
			{
			/* Parse the color index array: */
			parser.getNextToken();
			colorIndices=MFInt32::parse(parser);
			}
		else if(parser.isToken("normalIndex"))
			{
			/* Parse the normal vector index array: */
			parser.getNextToken();
			normalIndices=MFInt32::parse(parser);
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
		else
			Misc::throwStdErr("IndexedFaceSetNode::IndexedFaceSetNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	
	/* Create normal vectors if necessary: */
	CoordinateNode* c=dynamic_cast<CoordinateNode*>(coord.getPointer());
	NormalNode* n=dynamic_cast<NormalNode*>(normal.getPointer());
	if(coord!=0&&n==0)
		{
		/* Create a new normal node and clear the normal index array: */
		n=new NormalNode;
		normal=n;
		normalIndices.clear();
		
		/* Create normal vectors and normal indices: */
		if(normalPerVertex)
			calculateVertexNormals(c,coordIndices,Math::cos(creaseAngle),n,normalIndices);
		else
			calculateFaceNormals(c,coordIndices,n);
		}
	}