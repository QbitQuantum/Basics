// Build a CLight
bool CExportNel::buildLight (GenLight &maxLight, NL3D::CLight& nelLight, INode& node, TimeValue time)
{
	// Eval the light state fot this time
	Interval valid=NEVER;
	LightState ls;
	if (maxLight.EvalLightState(time, valid, &ls)==REF_SUCCEED)
	{
		// Set the light mode
		switch (maxLight.Type())
		{
		case OMNI_LIGHT:
			nelLight.setMode (CLight::PointLight);
			break;
		case TSPOT_LIGHT:
		case FSPOT_LIGHT:
			nelLight.setMode (CLight::SpotLight);
			break;
		case DIR_LIGHT:
		case TDIR_LIGHT:
			nelLight.setMode (CLight::DirectionalLight);
			break;
		default:
			// Not initialized
			return false;
		}

		// *** Set the light color

		// Get the color
		CRGBA nelColor;
		Point3 maxColor=maxLight.GetRGBColor(time);

		// Mul by multiply
		CRGBAF nelFColor;
		nelFColor.R=maxColor.x;
		nelFColor.G=maxColor.y;
		nelFColor.B=maxColor.z;
		nelFColor.A=1.f;
		nelFColor*=maxLight.GetIntensity(time);
		nelColor=nelFColor;

		// Affect the ambiant color ?
		if (maxLight.GetAmbientOnly())
		{
			nelLight.setAmbiant (nelColor);
			nelLight.setDiffuse (CRGBA (0,0,0));
			nelLight.setSpecular (CRGBA (0,0,0));
		}
		else
		{
			nelLight.setAmbiant (CRGBA (0,0,0));

			// Affect the diffuse color ?
			if (maxLight.GetAffectDiffuse())
				nelLight.setDiffuse (nelColor);
			else
				nelLight.setDiffuse (CRGBA (0,0,0));

			// Affect the specular color ?
			if (maxLight.GetAffectSpecular())
				nelLight.setSpecular (nelColor);
			else
				nelLight.setSpecular (CRGBA (0,0,0));
		}

		// Set the light position
		Point3 pos=node.GetNodeTM(time).GetTrans ();
		CVector position;
		position.x=pos.x;
		position.y=pos.y;
		position.z=pos.z;

		// Set the position
		nelLight.setPosition (position);

		// Set the light direction
		CVector direction;
		INode* target=node.GetTarget ();
		if (target)
		{
			// Get the position of the target
			Point3 posTarget=target->GetNodeTM (time).GetTrans ();
			CVector positionTarget;
			positionTarget.x=posTarget.x;
			positionTarget.y=posTarget.y;
			positionTarget.z=posTarget.z;

			// Direction
			direction=positionTarget-position;
			direction.normalize ();
		}
		else	// No target
		{
			// Get orientation of the source as direction
			CMatrix nelMatrix;
			convertMatrix (nelMatrix, node.GetNodeTM(time));

			// Direction is -Z
			direction=-nelMatrix.getK();
			direction.normalize ();
		}

		// Set the direction
		nelLight.setDirection (direction);

		// Set spot light information
		nelLight.setCutoff ((float)(NLMISC::Pi*maxLight.GetFallsize(time)/180.f/2.f));

		// Compute the exponent value
		float angle=(float)(NLMISC::Pi*maxLight.GetHotspot(time)/(2.0*180.0));
		nelLight.setupSpotExponent (angle);

		// *** Set attenuation

		if (maxLight.GetUseAtten())
		{
			float nearAtten = maxLight.GetAtten (time, ATTEN_START);
			if (nearAtten == 0)
				nearAtten = 0.1f;
			nelLight.setupAttenuation (nearAtten, maxLight.GetAtten (time, ATTEN_END));
		}
		else
			nelLight.setNoAttenuation ();

		// Initialized
		return true;
	}

	// Not initialized
	return false;
}