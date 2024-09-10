void LLVOPartGroup::getGeometry(S32 idx,
								LLStrider<LLVector3>& verticesp,
								LLStrider<LLVector3>& normalsp, 
								LLStrider<LLVector2>& texcoordsp,
								LLStrider<LLColor4U>& colorsp, 
								LLStrider<U16>& indicesp)
{
	if (idx >= (S32) mViewerPartGroupp->mParticles.size())
	{
		return;
	}

	const LLViewerPart &part = *((LLViewerPart*) (mViewerPartGroupp->mParticles[idx]));

	U32 vert_offset = mDrawable->getFace(idx)->getGeomIndex();

	
	LLVector3 part_pos_agent(part.mPosAgent);
	LLVector3 camera_agent = getCameraPosition(); 
	LLVector3 at = part_pos_agent - camera_agent;
	LLVector3 up;
	LLVector3 right;

	right = at % LLVector3(0.f, 0.f, 1.f);
	right.normalize();
	up = right % at;
	up.normalize();

	if (part.mFlags & LLPartData::LL_PART_FOLLOW_VELOCITY_MASK)
	{
		LLVector3 normvel = part.mVelocity;
		normvel.normalize();
		LLVector2 up_fracs;
		up_fracs.mV[0] = normvel*right;
		up_fracs.mV[1] = normvel*up;
		up_fracs.normalize();
		LLVector3 new_up;
		LLVector3 new_right;
		new_up = up_fracs.mV[0] * right + up_fracs.mV[1]*up;
		new_right = up_fracs.mV[1] * right - up_fracs.mV[0]*up;
		up = new_up;
		right = new_right;
		up.normalize();
		right.normalize();
	}

	right *= 0.5f*part.mScale.mV[0];
	up *= 0.5f*part.mScale.mV[1];


	LLVector3 normal = -LLViewerCamera::getInstance()->getXAxis();
		
	*verticesp++ = part_pos_agent + up - right;
	*verticesp++ = part_pos_agent - up - right;
	*verticesp++ = part_pos_agent + up + right;
	*verticesp++ = part_pos_agent - up + right;

	*colorsp++ = part.mColor;
	*colorsp++ = part.mColor;
	*colorsp++ = part.mColor;
	*colorsp++ = part.mColor;

	*texcoordsp++ = LLVector2(0.f, 1.f);
	*texcoordsp++ = LLVector2(0.f, 0.f);
	*texcoordsp++ = LLVector2(1.f, 1.f);
	*texcoordsp++ = LLVector2(1.f, 0.f);

	*normalsp++   = normal;
	*normalsp++   = normal;
	*normalsp++   = normal;
	*normalsp++   = normal;

	*indicesp++ = vert_offset + 0;
	*indicesp++ = vert_offset + 1;
	*indicesp++ = vert_offset + 2;

	*indicesp++ = vert_offset + 1;
	*indicesp++ = vert_offset + 3;
	*indicesp++ = vert_offset + 2;
}