Gaffer::Plug *ParameterHandler::setupPlug( const AtParamEntry *parameter, Gaffer::GraphComponent *plugParent, Gaffer::Plug::Direction direction )
{
	std::string name = AiParamGetName( parameter );

	PlugPtr plug = 0;
	switch( AiParamGetType( parameter ) )
	{
		case AI_TYPE_FLOAT :

			plug = new FloatPlug(
				name,
				direction,
				AiParamGetDefault( parameter )->FLT
			);

			break;

		case AI_TYPE_INT :

			plug = new IntPlug(
				name,
				direction,
				AiParamGetDefault( parameter )->INT
			);

			break;

		case AI_TYPE_BOOLEAN :

			plug = new BoolPlug(
				name,
				direction,
				AiParamGetDefault( parameter )->BOOL
			);

			break;

		case AI_TYPE_RGB :

			plug = new Color3fPlug(
				name,
				direction,
				Color3f(
					AiParamGetDefault( parameter )->RGB.r,
					AiParamGetDefault( parameter )->RGB.g,
					AiParamGetDefault( parameter )->RGB.b
				)
			);

			break;

		case AI_TYPE_RGBA :

			plug = new Color4fPlug(
				name,
				direction,
				Color4f(
					AiParamGetDefault( parameter )->RGBA.r,
					AiParamGetDefault( parameter )->RGBA.g,
					AiParamGetDefault( parameter )->RGBA.b,
					AiParamGetDefault( parameter )->RGBA.a
				)
			);

			break;

		case AI_TYPE_POINT2 :

			plug = new V2fPlug(
				name,
				direction,
				V2f(
					AiParamGetDefault( parameter )->PNT2.x,
					AiParamGetDefault( parameter )->PNT2.y
				)
			);

			break;

		case AI_TYPE_POINT :

			plug = new V3fPlug(
				name,
				direction,
				V3f(
					AiParamGetDefault( parameter )->PNT.x,
					AiParamGetDefault( parameter )->PNT.y,
					AiParamGetDefault( parameter )->PNT.z
				)
			);

			break;

		case AI_TYPE_VECTOR :

			plug = new V3fPlug(
				name,
				direction,
				V3f(
					AiParamGetDefault( parameter )->VEC.x,
					AiParamGetDefault( parameter )->VEC.y,
					AiParamGetDefault( parameter )->VEC.z
				)
			);

			break;

		case AI_TYPE_ENUM :

			{
				AtEnum e = AiParamGetEnum( parameter );
				plug = new StringPlug(
					name,
					direction,
					AiEnumGetString( e, AiParamGetDefault( parameter )->INT )
				);

			}
			break;

		case AI_TYPE_STRING :

			{
				plug = new StringPlug(
					name,
					direction,
					AiParamGetDefault( parameter )->STR
				);

			}

	}

	if( plug )
	{
		plug->setFlags( Plug::Dynamic, true );
		plugParent->addChild( plug );
	}
	else
	{
		msg(
			Msg::Warning,
			"GafferArnold::ParameterHandler::setupPlug",
			format( "Unsupported parameter \"%s\" of type \"%s\"" ) %
				AiParamGetName( parameter ) %
				AiParamGetTypeName( AiParamGetType( parameter ) )
		);
	}

	return plug.get();
}