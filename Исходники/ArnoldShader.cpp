void ArnoldShader::loadShader( const std::string &shaderName )
{
	IECoreArnold::UniverseBlock arnoldUniverse;
	
	const AtNodeEntry *shader = AiNodeEntryLookUp( shaderName.c_str() );
	if( !shader )
	{
		throw Exception( str( format( "Shader \"%s\" not found" ) % shaderName ) );
	}

	namePlug()->setValue( AiNodeEntryGetName( shader ) );
	typePlug()->setValue( "ai:surface" );
		
	ParameterHandler::setupPlugs( shader, parametersPlug() );
			
	PlugPtr outPlug = 0;
	const int outputType = AiNodeEntryGetOutputType( shader );
	switch( outputType )
	{
		case AI_TYPE_RGB :
			
			outPlug = new Color3fPlug(
				"out",
				Plug::Out
			);
		
			break;
			
		case AI_TYPE_RGBA :
			
			outPlug = new Color4fPlug(
				"out",
				Plug::Out
			);
		
			break;	
		
		case AI_TYPE_FLOAT :
			
			outPlug = new FloatPlug(
				"out",
				Plug::Out
			);
		
			break;
			
		case AI_TYPE_INT :
			
			outPlug = new IntPlug(
				"out",
				Plug::Out
			);
		
			break;	
	
	}
	
	if( outPlug )
	{
		outPlug->setFlags( Plug::Dynamic, true );
		addChild( outPlug );
	}
	else
	{
		if( outputType != AI_TYPE_NONE )
		{
			msg(
				Msg::Warning,
				"ArnoldShader::loadShader",
				format( "Unsupported output parameter of type \"%s\"" ) %
					AiParamGetTypeName( AiNodeEntryGetOutputType( shader ) )
			);
		}
	}
	
}