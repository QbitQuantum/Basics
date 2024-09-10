std::vector<Rotation> MFRotation::parse(VRMLParser& parser)
	{
	std::vector<Rotation> result;
	
	/* Check for the opening bracket: */
	if(parser.isToken("["))
		{
		/* Skip the opening bracket: */
		parser.getNextToken();
		
		/* Parse orientations until closing bracket: */
		while(!parser.isToken("]"))
			{
			/* Parse the next rotation axis: */
			Rotation::Vector axis;
			for(int i=0;i<3;++i)
				{
				/* Parse the current token: */
				axis[i]=Rotation::Scalar(atof(parser.getToken()));
				
				/* Go to the next token: */
				parser.getNextToken();
				}
			
			/* Parse the next rotation angle: */
			Rotation::Scalar angle=Rotation::Scalar(atof(parser.getToken()));
			
			/* Go to the next token: */
			parser.getNextToken();
			
			/* Store the orientation: */
			result.push_back(Rotation(axis,angle));
			}
		
		/* Skip the closing bracket: */
		parser.getNextToken();
		}
	else
		{
		/* Parse the rotation axis: */
		Rotation::Vector axis;
		for(int i=0;i<3;++i)
			{
			/* Parse the current token: */
			axis[i]=Rotation::Scalar(atof(parser.getToken()));
			
			/* Go to the next token: */
			parser.getNextToken();
			}
		
		/* Parse the rotation angle: */
		Rotation::Scalar angle=Rotation::Scalar(atof(parser.getToken()));
		
		/* Go to the next token: */
		parser.getNextToken();
		
		/* Store the orientation: */
		result.push_back(Rotation(axis,angle));
		}
	
	return result;
	}