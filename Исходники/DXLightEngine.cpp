// This function switch on the nearest lights to an object of a certain radius
void	CDXLight::UpdateDynamicLights(DWORD ID, D3DVECTOR *pos, float Radius)
{
	_MM_ALIGN16	XMMVector	Pos, Acc, Square;
	DWORD					idx,ldx, LightsInList=0;
	float					Dist, MaxDist=0.0f;

	// setup the position for XMM use
	*(D3DVECTOR*)&Pos.d3d=*pos;

	// if 1st call in this rendering
	if(!LightsLoaded){
		// Enable the lights + 1 ( light #0 is the Sun )
		idx=0;
//		while(idx<MAX_DYNAMIC_LIGHTS && LightList[idx].CameraDistance<=DYNAMIC_LIGHT_INSIDE_RANGE){
		while(idx<DynamicLights){
			m_pD3DD->SetLight(idx+1, &LightList[idx++].Light);
		}
		LightsLoaded=true;
	}
	
	//reset object own light list
	for(idx=0; idx<MAX_SAMETIME_LIGHTS; idx++){
		SwitchedList[idx].Distance=DYNAMIC_LIGHT_INSIDE_RANGE+1.0f;
		SwitchedList[idx].Index=0;
	}

	//for each light in list setup a distance list
	idx=0;
	//while(idx<MAX_DYNAMIC_LIGHTS && LightList[idx].CameraDistance<=DYNAMIC_LIGHT_INSIDE_RANGE){
	while(idx<DynamicLights){
		
		// Light defaults to OFF
		LightsToOn[idx]=false;

		// if this is a light illuminating ONLY THE OWNER, and we r not the owners, skip
		if(LightList[idx].Flags.OwnLight && LightList[idx].LightID!=ID){
			idx++;
			continue;
		}

		// if this is a light illuminating NOT THE OWNER, and we r the owners, skip
		if(LightList[idx].Flags.NotSelfLight && LightList[idx].LightID==ID){
			idx++;
			continue;
		}

		// get Vectors distance on X/Y/Z Axis and Square it for incoming use
		Acc.Xmm=_mm_sub_ps(Pos.Xmm, LightList[idx].Pos.Xmm);
		Square.Xmm=_mm_mul_ps(Acc.Xmm, Acc.Xmm);
		// Get the Distance
		Dist=sqrtf(Square.d3d.x+Square.d3d.y+Square.d3d.z);

		// If Object out of the Light range
		if((Dist-Radius)>LightList[idx].Light.dvRange)
		{idx++; continue; }
		
		// Calculation for SPOT LIGHTs cone
		if(LightList[idx].Light.dltType==D3DLIGHT_SPOT){

			// Get the Distance btw Light & Object
			//float	dx=Pos.d3d.x-LightList[idx].Light.dvPosition.x;
			//float	dy=Pos.d3d.y-LightList[idx].Light.dvPosition.y;
			//float	dz=Pos.d3d.z-LightList[idx].Light.dvPosition.z;
			// Calculate Horizontal and Vertical Angle btw Light & Object
			float	ax=atan2(Acc.d3d.x, Acc.d3d.y);
			float	ay=atan2(Acc.d3d.z,sqrtf(Square.d3d.x+Square.d3d.y));
			// transform the angles in same Sign Domain of the light angles X/Y
			if(fabs(ax-LightList[idx].alphaX)>PI) ax+=ax>LightList[idx].alphaX ? -2*PI : 2*PI;
			if(fabs(ay-LightList[idx].alphaY)>PI) ay+=ax>LightList[idx].alphaY ? -2*PI : 2*PI;
			float lPhy=LightList[idx].phi;
			float laX=LightList[idx].alphaX;
			float laY=LightList[idx].alphaY;
			// Calculate the Angular Delta given by Object Radius
			float	dPhi=atanf(Radius/Dist);

#ifdef	LIGHT_ENGINE_DEBUG
			REPORT_VALUE("Max :",(int)(LightList[idx].alphaX*180/PI));
			REPORT_VALUE("Min :",(int)(LightList[idx].alphaY*180/PI));
#ifdef DEBUG_LOD_ID
			sprintf(TheLODNames[gDebugLodID], "%3.1f %3.1f", ax*180/PI, dPhi*180/PI);
#endif
#endif
			if(ax-dPhi>(laX+lPhy) || ax+dPhi<(laX-lPhy) || ay-dPhi>(laY+lPhy) || ay+dPhi<(laY-lPhy))
			{ idx++; continue; }


		}
		Dist-=Radius;

		// if List still has a slot, add immediatly the light
		if(LightsInList<MAX_SAMETIME_LIGHTS){
			// setup new distance and index in the list
			SwitchedList[LightsInList].Distance=Dist;
			SwitchedList[LightsInList++].Index=idx;
			// flag the light as going to be switched on
			LightsToOn[idx]=true;
			// and update the longest in list
			if(Dist>MaxDist) MaxDist=Dist;
		} else {
			// else only if more near than any light in list
			if(Dist<MaxDist){
				// setup a temporary for the new Max Distance 
				float	TempDist=0.0f;
				// check if lower distance than any in the object lites list
				for(ldx=0; ldx<MAX_SAMETIME_LIGHTS; ldx++){
					// if distance is less
					if(SwitchedList[ldx].Distance==MaxDist){
						// disable the previous light
						LightsToOn[SwitchedList[ldx].Index]=false;
						// setup new distance and index in the list
						SwitchedList[ldx].Distance=Dist;
						SwitchedList[ldx].Index=idx;
						// enable the new light
						LightsToOn[idx]=true;
					}
					// check if new longest distance
					if(SwitchedList[ldx].Distance>TempDist) TempDist=SwitchedList[ldx].Distance;
				}
				// update new Max Distance
				MaxDist=TempDist;
			}
		}
		idx++;
	}

	EnableMappedLights();
}