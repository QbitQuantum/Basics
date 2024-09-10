BOOL LLHUDNameTag::lineSegmentIntersect(const LLVector4a& start, const LLVector4a& end, LLVector4a& intersection, BOOL debug_render)
{
	if (!mVisible || mHidden)
	{
		return FALSE;
	}

	// don't pick text that isn't bound to a viewerobject
	if (!mSourceObject || mSourceObject->mDrawable.isNull())
	{
		return FALSE;
	}
	
	F32 alpha_factor = 1.f;
	LLColor4 text_color = mColor;
	if (mDoFade)
	{
		if (mLastDistance > mFadeDistance)
		{
			alpha_factor = llmax(0.f, 1.f - (mLastDistance - mFadeDistance)/mFadeRange);
			text_color.mV[3] = text_color.mV[3]*alpha_factor;
		}
	}
	if (text_color.mV[3] < 0.01f)
	{
		return FALSE;
	}

	mOffsetY = lltrunc(mHeight * ((mVertAlignment == ALIGN_VERT_CENTER) ? 0.5f : 1.f));

	LLVector3 position = mPositionAgent;

	if (mSourceObject)
	{ //get intersection of eye through mPositionAgent to plane of source object
		//using this position keeps the camera from focusing on some seemingly random 
		//point several meters in front of the nametag
		const LLVector3& p = mSourceObject->getPositionAgent();
		const LLVector3& n = LLViewerCamera::getInstance()->getAtAxis();
		const LLVector3& eye = LLViewerCamera::getInstance()->getOrigin();

		LLVector3 ray = position-eye;
		ray.normalize();

		LLVector3 delta = p-position;
		F32 dist = delta*n;
		F32 dt =  dist/(ray*n);
		position += ray*dt;
	}

	// scale screen size of borders down

	LLVector3 x_pixel_vec;
	LLVector3 y_pixel_vec;
	
	LLViewerCamera::getInstance()->getPixelVectors(position, y_pixel_vec, x_pixel_vec);

	LLVector3 width_vec = mWidth * x_pixel_vec;
	LLVector3 height_vec = mHeight * y_pixel_vec;
	
	LLCoordGL screen_pos;
	LLViewerCamera::getInstance()->projectPosAgentToScreen(position, screen_pos, FALSE);

	LLVector2 screen_offset;
	screen_offset = updateScreenPos(mPositionOffset);
	
	LLVector3 render_position = position  
			+ (x_pixel_vec * screen_offset.mV[VX])
			+ (y_pixel_vec * screen_offset.mV[VY]);


	LLVector3 bg_pos = render_position
		+ (F32)mOffsetY * y_pixel_vec
		- (width_vec / 2.f)
		- (height_vec);

	LLVector3 v[] = 
	{
		bg_pos,
		bg_pos + width_vec,
		bg_pos + width_vec + height_vec,
		bg_pos + height_vec,
	};

	LLVector4a dir;
	dir.setSub(end,start);
	F32 a, b, t;

	LLVector4a v0,v1,v2,v3;
	v0.load3(v[0].mV);
	v1.load3(v[1].mV);
	v2.load3(v[2].mV);
	v3.load3(v[3].mV);

	if (LLTriangleRayIntersect(v0, v1, v2, start, dir, a, b, t) ||
		LLTriangleRayIntersect(v2, v3, v0, start, dir, a, b, t) )
	{
		if (t <= 1.f)
		{
			dir.mul(t);
			intersection.setAdd(start, dir);
			return TRUE;
		}
	}

	return FALSE;
}