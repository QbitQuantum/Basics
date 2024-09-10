BOOL LLVOSurfacePatch::lineSegmentIntersect(const LLVector3& start, const LLVector3& end, S32 face, BOOL pick_transparent, S32 *face_hitp,
									  LLVector3* intersection,LLVector2* tex_coord, LLVector3* normal, LLVector3* bi_normal)
	
{

	if (!lineSegmentBoundingBox(start, end))
	{
		return FALSE;
	}

	LLVector3 delta = end-start;
		
	LLVector3 pdelta = delta;
	pdelta.mV[2] = 0;

	F32 plength = pdelta.length();
	
	F32 tdelta = 1.f/plength;

	LLVector3 origin = start - mRegionp->getOriginAgent();

	if (mRegionp->getLandHeightRegion(origin) > origin.mV[2])
	{
		//origin is under ground, treat as no intersection
		return FALSE;
	}

	//step one meter at a time until intersection point found

	//VECTORIZE THIS
	const LLVector4a* exta = mDrawable->getSpatialExtents();

	LLVector3 ext[2];
	ext[0].set(exta[0].getF32ptr());
	ext[1].set(exta[1].getF32ptr());

	F32 rad = (delta*tdelta).magVecSquared();

	F32 t = 0.f;
	while ( t <= 1.f)
	{
		LLVector3 sample = origin + delta*t;
		
		if (AABBSphereIntersectR2(ext[0], ext[1], sample+mRegionp->getOriginAgent(), rad))
		{
			F32 height = mRegionp->getLandHeightRegion(sample);
			if (height > sample.mV[2])
			{ //ray went below ground, positive intersection
				//quick and dirty binary search to get impact point
				tdelta = -tdelta*0.5f;
				F32 err_dist = 0.001f;
				F32 dist = fabsf(sample.mV[2] - height);

				while (dist > err_dist && tdelta*tdelta > 0.0f)
				{
					t += tdelta;
					sample = origin+delta*t;
					height = mRegionp->getLandHeightRegion(sample);
					if ((tdelta < 0 && height < sample.mV[2]) ||
						(height > sample.mV[2] && tdelta > 0))
					{ //jumped over intersection point, go back
						tdelta = -tdelta;
					}
					tdelta *= 0.5f;
					dist = fabsf(sample.mV[2] - height);
				}

				if (intersection)
				{
					F32 height = mRegionp->getLandHeightRegion(sample);
					if (fabsf(sample.mV[2]-height) < delta.length()*tdelta)
					{
						sample.mV[2] = mRegionp->getLandHeightRegion(sample);
					}
					*intersection = sample + mRegionp->getOriginAgent();
				}

				if (normal)
				{
					*normal = mRegionp->getLand().resolveNormalGlobal(mRegionp->getPosGlobalFromRegion(sample));
				}

				return TRUE;
			}
		}

		t += tdelta;
		if (t > 1 && t < 1.f+tdelta*0.99f)
		{ //make sure end point is checked (saves vertical lines coming up negative)
			t = 1.f;
		}
	}


	return FALSE;
}