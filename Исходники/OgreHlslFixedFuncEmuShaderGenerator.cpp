	//---------------------------------------------------------------------
	void HlslFixedFuncEmuShaderGenerator::HlslFixedFuncPrograms::setFixedFuncProgramsParameters( const FixedFuncProgramsParameters & params )
	{
		_setProgramMatrix4Parameter(GPT_VERTEX_PROGRAM, "World", params.getWorldMat());
		_setProgramMatrix4Parameter(GPT_VERTEX_PROGRAM, "View", params.getViewMat());
		_setProgramMatrix4Parameter(GPT_VERTEX_PROGRAM, "Projection", params.getProjectionMat());

		_setProgramMatrix4Parameter(GPT_VERTEX_PROGRAM, "ViewIT", params.getViewMat().inverse().transpose());


		Matrix4 WorldViewIT = params.getViewMat() * params.getWorldMat();
		WorldViewIT = WorldViewIT.inverse().transpose();
		_setProgramMatrix4Parameter(GPT_VERTEX_PROGRAM, "WorldViewIT", WorldViewIT);


		_setProgramColorParameter(GPT_VERTEX_PROGRAM, "BaseLightAmbient", params.getLightAmbient());
		if (params.getLightingEnabled() && params.getLights().size() > 0)
		{
		
			uint pointLightCount = 0;
			uint directionalLightCount = 0;
			uint spotLightCount = 0;
			for(size_t i = 0 ; i < params.getLights().size() ; i++)
			{
				Light * curLight = params.getLights()[i];
				String prefix;

				switch (curLight->getType())
				{
				case Light::LT_POINT:
					prefix = "PointLight" + StringConverter::toString(pointLightCount) + "_";
					pointLightCount++;
					break;
				case Light::LT_DIRECTIONAL:
					prefix = "DirectionalLight" + StringConverter::toString(directionalLightCount) + "_";
					directionalLightCount++;
					break;
				case Light::LT_SPOTLIGHT:
					prefix = "SpotLight" + StringConverter::toString(spotLightCount) + "_";
					spotLightCount++;
					break;
				} 

				_setProgramColorParameter(GPT_VERTEX_PROGRAM, prefix + "Ambient", ColourValue::Black);
				_setProgramColorParameter(GPT_VERTEX_PROGRAM, prefix + "Diffuse", curLight->getDiffuseColour());
				_setProgramColorParameter(GPT_VERTEX_PROGRAM, prefix + "Specular", curLight->getSpecularColour());		

				switch (curLight->getType())
				{
				case Light::LT_POINT:
					{
						_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Position", curLight->getPosition());
						_setProgramFloatParameter(GPT_VERTEX_PROGRAM, prefix + "Range", curLight->getAttenuationRange());

						Vector3 attenuation;
						attenuation[0] = curLight->getAttenuationConstant();
						attenuation[1] = curLight->getAttenuationLinear();
						attenuation[2] = curLight->getAttenuationQuadric();
						_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Attenuation", attenuation);
					}
					break;
				case Light::LT_DIRECTIONAL:
					_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Direction", curLight->getDirection());

					break;
				case Light::LT_SPOTLIGHT:
					{

						_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Direction", curLight->getDirection());
						_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Position", curLight->getPosition());

						Vector3 attenuation;
						attenuation[0] = curLight->getAttenuationConstant();
						attenuation[1] = curLight->getAttenuationLinear();
						attenuation[2] = curLight->getAttenuationQuadric();
						_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Attenuation", attenuation);

						Vector3 spot;
						spot[0] = curLight->getSpotlightInnerAngle().valueRadians() ;
						spot[1] = curLight->getSpotlightOuterAngle().valueRadians();
						spot[2] = curLight->getSpotlightFalloff();
						_setProgramVector3Parameter(GPT_VERTEX_PROGRAM, prefix + "Spot", spot);					
					}
					break;
				} // end of - switch (curLight->getType())
			} // end of - for(size_t i = 0 ; i < params.getLights().size() ; i++) 
		} // end of -  if (params.getLightingEnabled())





		switch (params.getFogMode())
		{
		case FOG_NONE:
			break;
		case FOG_EXP:
		case FOG_EXP2:
			_setProgramFloatParameter(GPT_VERTEX_PROGRAM, "FogDensity", params.getFogDensitiy());
			break;
		case FOG_LINEAR:
			_setProgramFloatParameter(GPT_VERTEX_PROGRAM, "FogStart", params.getFogStart());
			_setProgramFloatParameter(GPT_VERTEX_PROGRAM, "FogEnd", params.getFogEnd());
			break;
		}

		if (params.getFogMode() != FOG_NONE)
		{
			_setProgramColorParameter(GPT_FRAGMENT_PROGRAM, "FogColor", params.getFogColour());
		}


		for(size_t i = 0 ; i < params.getTextureMatrices().size() && i < mFixedFuncState.getTextureLayerStateList().size(); i++)
		{
			if (params.isTextureStageEnabled(i))
			{
				if (params.isTextureStageEnabled(i))
				{
					_setProgramMatrix4Parameter(GPT_VERTEX_PROGRAM, "TextureMatrix" + StringConverter::toString(i), params.getTextureMatrices()[i]);
				}
			}
		}



	}