void CRMLandScape::Sprinkle(CCMPatch *patch, CCGHeightDetails *hd, int level)
{
	int				i, count, px, py;
	float			density;
	vec3_t			origin, scale, angles, bounds[2];
	refEntity_t		refEnt;
	CRandomModel	*rm;
	CArea			area;
//	int				areaTypes[] = { AT_BSP, AT_OBJECTIVE };
	TCGMiscEnt		*data = (TCGMiscEnt *)cl.mSharedMemory;
	TCGTrace		*td = (TCGTrace *)cl.mSharedMemory;

//	memset(&refEnt, 0, sizeof(refEntity_t));

	px = patch->GetHeightMapX() / common->GetTerxels();
	py = patch->GetHeightMapY() / common->GetTerxels();
	// Get a number -5.3f to 5.3f
	density = (mDensityMap[px + (common->GetBlockWidth() * py)] - 128) / 24.0f;
	// ..and multiply that into the count
	count = Round(common->GetPatchScalarSize() * hd->GetAverageFrequency() * powf(2.0f, density) * 0.001);

	for(i = 0; i < count; i++)
	{
		if(!common->irand(0, 10))
		{
			vec3_t temp;
			float  average;

			rm = hd->GetRandomModel(common);

			refEnt.hModel = re.RegisterModel(rm->GetModelName());
			refEnt.frame = 0;
			re.ModelBoundsRef(&refEnt, bounds[0], bounds[1]);

			// Calculate the scale using some magic to help ensure that the
			// scales are never too different from eachother.  Otherwise you
			// could get an entity that is really small on one axis but huge 
			// on another.
			temp[0] = common->flrand(rm->GetMinScale(), rm->GetMaxScale());
			temp[1] = common->flrand(rm->GetMinScale(), rm->GetMaxScale());
			temp[2] = common->flrand(rm->GetMinScale(), rm->GetMaxScale());

			// Average of the three random numbers and divide that by two
			average = ( ( temp[0] + temp[1] + temp[2] ) / 3) / 2;

			// Add in half of the other two numbers and then subtract half the average to prevent.
			// any number from going beyond the range. If all three numbers were the same then
			// they would remain unchanged after this calculation.
			scale[0] = temp[0] + (temp[1]+temp[2]) / 2 - average;
			scale[1] = temp[1] + (temp[0]+temp[2]) / 2 - average;
			scale[2] = temp[2] + (temp[0]+temp[1]) / 2 - average;

			angles[0] = 0.0f;
			angles[1] = common->flrand(-M_PI, M_PI);
			angles[2] = 0.0f;

			VectorCopy(patch->GetMins(), origin);
			origin[0] += common->flrand(0.0f, common->GetPatchWidth());
			origin[1] += common->flrand(0.0f, common->GetPatchHeight());
			// Get above world height
			float slope = common->GetWorldHeight(origin, bounds, true);

			if (slope > 1.33)
			{	// spot has too steep of a slope
				continue;
			}
			if(origin[2] < common->GetWaterHeight())
			{
				continue;
			}
			// very that we aren't dropped too low
			if (origin[2] < common->CalcWorldHeight(level))
			{
				continue;
			}

			// Hack-ariffic, don't allow them to drop below the big player clip brush.
			if (origin[2] < 1280 )
			{
				continue;
			}
			// FIXME: shouldn't be using a hard-coded 1280 number, only allow to spawn if inside player clip brush? 
	//		if( !(CONTENTS_PLAYERCLIP & VM_Call( cgvm, CG_POINT_CONTENTS )) )
	//		{
	//			continue;
	//		}
			// Simple radius check for buildings
/*			area.Init(origin, VectorLength(bounds[0]));
			if(common->AreaCollision(&area, areaTypes, sizeof(areaTypes) / sizeof(int)))
			{
				continue;
			}*/
			// Make sure there is no architecture around - doesn't work for ents though =(

			memset(td, sizeof(*td), 0);
			VectorCopy(origin, td->mStart);
			VectorCopy(bounds[0], td->mMins);
			VectorCopy(bounds[1], td->mMaxs);
			VectorCopy(origin, td->mEnd);
			td->mSkipNumber = -1;
			td->mMask = MASK_PLAYERSOLID;

			VM_Call( cgvm, CG_TRACE );
			if(td->mResult.surfaceFlags & SURF_NOMISCENTS)
			{
				continue;
			}
			if(td->mResult.startsolid)
			{
//				continue;
			}
			// Get minimum height of area
			common->GetWorldHeight(origin, bounds, false);
			// Account for relative origin
			origin[2] -= bounds[0][2] * scale[2];
			origin[2] -= common->flrand(2.0, (bounds[1][2] - bounds[0][2]) / 4);
			
			// Spawn the client model
			strcpy(data->mModel, rm->GetModelName());
			VectorCopy(origin, data->mOrigin);
			VectorCopy(angles, data->mAngles);
			VectorCopy(scale, data->mScale);
			VM_Call( cgvm, CG_MISC_ENT);
			mModelCount++;
		}
	}
}