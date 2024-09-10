Color SFColor::parse(VRMLParser& parser)
	{
	Color result(0,0,0,255);
	
	for(int i=0;i<3;++i)
		{
		/* Parse the current token: */
		double val=atof(parser.getToken());
		if(val<0.0)
			result[i]=GLubyte(0);
		else if(val>1.0)
			result[i]=GLubyte(255);
		else
			result[i]=GLubyte(Math::floor(val*255.0+0.5));
		
		/* Go to the next token: */
		parser.getNextToken();
		}
	
	return result;
	}