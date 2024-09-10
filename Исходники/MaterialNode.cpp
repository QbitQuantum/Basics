MaterialNode::MaterialNode(VRMLParser& parser)
	:AttributeNode(parser)
	{
	/* Check for the opening brace: */
	if(!parser.isToken("{"))
		Misc::throwStdErr("MaterialNode::MaterialNode: Missing opening brace in node definition");
	parser.getNextToken();
	
	/* Process attributes until closing brace: */
	while(!parser.isToken("}"))
		{
		if(parser.isToken("diffuseColor"))
			{
			/* Parse the diffuse color: */
			parser.getNextToken();
			for(int i=0;i<3;++i)
				{
				material.diffuse[i]=GLMaterial::Scalar(atof(parser.getToken()));
				parser.getNextToken();
				}
			}
		else if(parser.isToken("ambientIntensity"))
			{
			/* Parse the ambient intensity: */
			parser.getNextToken();
			GLMaterial::Scalar ambientIntensity=GLMaterial::Scalar(atof(parser.getToken()));
			parser.getNextToken();
			for(int i=0;i<3;++i)
				material.ambient[i]=material.diffuse[i]*ambientIntensity;
			}
		else if(parser.isToken("specularColor"))
			{
			/* Parse the specular color: */
			parser.getNextToken();
			for(int i=0;i<3;++i)
				{
				material.specular[i]=GLMaterial::Scalar(atof(parser.getToken()));
				parser.getNextToken();
				}
			}
		else if(parser.isToken("shininess"))
			{
			/* Parse the shininess: */
			parser.getNextToken();
			material.shininess=GLMaterial::Scalar(atof(parser.getToken()))*GLMaterial::Scalar(128);
			parser.getNextToken();
			}
		else if(parser.isToken("transparency"))
			{
			/* Parse the transparency: */
			parser.getNextToken();
			material.diffuse[3]=GLMaterial::Scalar(1)-GLMaterial::Scalar(atof(parser.getToken()));
			parser.getNextToken();
			}
		else if(parser.isToken("emissiveColor"))
			{
			/* Parse the emissive color: */
			parser.getNextToken();
			for(int i=0;i<3;++i)
				{
				material.emission[i]=GLMaterial::Scalar(atof(parser.getToken()));
				parser.getNextToken();
				}
			}
		else
			Misc::throwStdErr("MaterialNode::MaterialNode: unknown attribute \"%s\" in node definition",parser.getToken());
		}
	
	/* Skip the closing brace: */
	parser.getNextToken();
	}