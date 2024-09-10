FormattedPointSetReaderNode::FormattedPointSetReaderNode(VRMLParser& parser)
	:numHeaderLines(0)
	{
	for(int i=0;i<4;++i)
		columnIndices[i]=-1;
	
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("FormattedPointSetReaderNode::FormattedPointSetReaderNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("url"))
			{
			/* Read the external point file's URL: */
			parser.getNextToken();
			url=SFString::parse(parser);
			}
		else if(parser.isToken("columnStarts"))
			{
			/* Read the array of column starts: */
			parser.getNextToken();
			columnStarts=MFInt32::parse(parser);
			}
		else if(parser.isToken("columnWidths"))
			{
			/* Read the array of column widths: */
			parser.getNextToken();
			columnWidths=MFInt32::parse(parser);
			}
		else if(parser.isToken("ellipsoid"))
			{
			/* Read the ellipsoid node: */
			parser.getNextToken();
			ellipsoid=parser.getNextNode();
			}
		else if(parser.isToken("colorMap"))
			{
			/* Read the color map node: */
			parser.getNextToken();
			colorMap=parser.getNextNode();
			}
		else if(parser.isToken("coordColumnIndices"))
			{
			/* Read the array of coordinate column indices: */
			parser.getNextToken();
			for(int i=0;i<3;++i)
				columnIndices[i]=SFInt32::parse(parser);
			}
		else if(parser.isToken("valueColumnIndex"))
			{
			/* Read the value column index: */
			parser.getNextToken();
			columnIndices[3]=SFInt32::parse(parser);
			}
		else if(parser.isToken("numHeaderLines"))
			{
			/* Read the number of header lines to skip: */
			parser.getNextToken();
			numHeaderLines=SFInt32::parse(parser);
			}
		else
			Misc::throwStdErr("FormattedPointSetReaderNode::FormattedPointSetReaderNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	
	/* Compute required information: */
	if(columnStarts.empty())
		{
		int start=0;
		for(std::vector<Int32>::const_iterator cwIt=columnWidths.begin();cwIt!=columnWidths.end();++cwIt)
			{
			columnStarts.push_back(start);
			start+=*cwIt;
			}
		}
	}