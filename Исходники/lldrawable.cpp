// Returns "distance" between target destination and resulting xfrom
F32 LLDrawable::updateXform(BOOL undamped)
{
	BOOL damped = !undamped;

	// Position
	LLVector3 old_pos(mXform.getPosition());
	LLVector3 target_pos;
	if (mXform.isRoot())
	{
		// get root position in your agent's region
		target_pos = mVObjp->getPositionAgent();
	}
	else
	{
		// parent-relative position
		target_pos = mVObjp->getPosition();
	}
	
	// Rotation
	LLQuaternion old_rot(mXform.getRotation());
	LLQuaternion target_rot = mVObjp->getRotation();
	//scaling
	LLVector3 target_scale = mVObjp->getScale();
	LLVector3 old_scale = mCurrentScale;
	LLVector3 dest_scale = target_scale;
	
	// Damping
	F32 dist_squared = 0.f;
	F32 camdist2 = (mDistanceWRTCamera * mDistanceWRTCamera);

	if (damped && isVisible())
	{
		F32 lerp_amt = llclamp(LLCriticalDamp::getInterpolant(OBJECT_DAMPING_TIME_CONSTANT), 0.f, 1.f);
		LLVector3 new_pos = lerp(old_pos, target_pos, lerp_amt);
		dist_squared = dist_vec_squared(new_pos, target_pos);

		LLQuaternion new_rot = nlerp(lerp_amt, old_rot, target_rot);
		dist_squared += (1.f - dot(new_rot, target_rot)) * 10.f;

		LLVector3 new_scale = lerp(old_scale, target_scale, lerp_amt);
		dist_squared += dist_vec_squared(new_scale, target_scale);

		if ((dist_squared >= MIN_INTERPOLATE_DISTANCE_SQUARED * camdist2) &&
			(dist_squared <= MAX_INTERPOLATE_DISTANCE_SQUARED))
		{
			// interpolate
			target_pos = new_pos;
			target_rot = new_rot;
			target_scale = new_scale;
		}
		else
		{
			// snap to final position
			dist_squared = 0.0f;
			if (!isRoot())
			{ //child prim snapping to some position, needs a rebuild
				gPipeline.markRebuild(this, LLDrawable::REBUILD_POSITION, TRUE);
			}
		}
	}

	if ((mCurrentScale != target_scale) ||
		(!isRoot() && 
		 (dist_squared >= MIN_INTERPOLATE_DISTANCE_SQUARED || 
		 !mVObjp->getAngularVelocity().isExactlyZero() ||
		 target_pos != mXform.getPosition() ||
		 target_rot != mXform.getRotation())))
	{ //child prim moving or scale change requires immediate rebuild
		gPipeline.markRebuild(this, LLDrawable::REBUILD_POSITION, TRUE);
	}
	else if (!getVOVolume() && !isAvatar())
	{
		movePartition();
	}

	// Update
	mXform.setPosition(target_pos);
	mXform.setRotation(target_rot);
	mXform.setScale(LLVector3(1,1,1)); //no scale in drawable transforms (IT'S A RULE!)
	mXform.updateMatrix();
	
	mCurrentScale = target_scale;
	
	if (mSpatialBridge)
	{
		gPipeline.markMoved(mSpatialBridge, FALSE);
	}
	return dist_squared;
}