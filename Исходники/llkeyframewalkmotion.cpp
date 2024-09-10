//-----------------------------------------------------------------------------
// LLWalkAdjustMotion::onUpdate()
//-----------------------------------------------------------------------------
BOOL LLWalkAdjustMotion::onUpdate(F32 time, U8* joint_mask)
{
	// delta_time is guaranteed to be non zero
	F32 delta_time = llclamp(time - mLastTime, TIME_EPSILON, MAX_TIME_DELTA);
	mLastTime = time;

	// find the avatar motion vector in the XY plane
	LLVector3 avatar_velocity = mCharacter->getCharacterVelocity() * mCharacter->getTimeDilation();
	avatar_velocity.mV[VZ] = 0.f;

	F32 speed = llclamp(avatar_velocity.magVec(), 0.f, MAX_WALK_PLAYBACK_SPEED);

	// grab avatar->world transforms
	LLQuaternion avatar_to_world_rot = mCharacter->getRootJoint()->getWorldRotation();

	LLQuaternion world_to_avatar_rot(avatar_to_world_rot);
	world_to_avatar_rot.conjugate();

	LLVector3 foot_slip_vector;

	// find foot drift along velocity vector
	if (speed > MIN_WALK_SPEED)
	{	// walking/running

		// calculate world-space foot drift
		// use global coordinates to seamlessly handle region crossings
		LLVector3d leftFootGlobalPosition = mCharacter->getPosGlobalFromAgent(mLeftAnkleJoint->getWorldPosition());
		leftFootGlobalPosition.mdV[VZ] = 0.0;
		LLVector3 leftFootDelta(leftFootGlobalPosition - mLastLeftFootGlobalPos);
		mLastLeftFootGlobalPos = leftFootGlobalPosition;

		LLVector3d rightFootGlobalPosition = mCharacter->getPosGlobalFromAgent(mRightAnkleJoint->getWorldPosition());
		rightFootGlobalPosition.mdV[VZ] = 0.0;
		LLVector3 rightFootDelta(rightFootGlobalPosition - mLastRightFootGlobalPos);
		mLastRightFootGlobalPos = rightFootGlobalPosition;

		// get foot drift along avatar direction of motion
		F32 left_foot_slip_amt = leftFootDelta * avatar_velocity;
		F32 right_foot_slip_amt = rightFootDelta * avatar_velocity;

		// if right foot is pushing back faster than left foot...
		if (right_foot_slip_amt < left_foot_slip_amt)
		{	//...use it to calculate optimal animation speed
			foot_slip_vector = rightFootDelta;
		} 
		else
		{	// otherwise use the left foot
			foot_slip_vector = leftFootDelta;
		}

		// calculate ideal pelvis offset so that foot is glued to ground and damp towards it
		// this will soak up transient slippage
		//
		// FIXME: this interacts poorly with speed adjustment
		// mPelvisOffset compensates for foot drift by moving the avatar pelvis in the opposite
		// direction of the drift, up to a certain limited distance
		// but this will cause the animation playback rate calculation below to 
		// kick in too slowly and sometimes start playing the animation in reverse.

		//mPelvisOffset -= PELVIS_COMPENSATION_WIEGHT * (foot_slip_vector * world_to_avatar_rot);//lerp(LLVector3::zero, -1.f * (foot_slip_vector * world_to_avatar_rot), LLCriticalDamp::getInterpolant(0.1f));

		////F32 drift_comp_max = DRIFT_COMP_MAX_TOTAL * (llclamp(speed, 0.f, DRIFT_COMP_MAX_SPEED) / DRIFT_COMP_MAX_SPEED);
		//F32 drift_comp_max = DRIFT_COMP_MAX_TOTAL;

		//// clamp pelvis offset to a 90 degree arc behind the nominal position
		//// NB: this is an ADDITIVE amount that is accumulated every frame, so clamping it alone won't do the trick
		//// must clamp with absolute position of pelvis in mind
		//LLVector3 currentPelvisPos = mPelvisState->getJoint()->getPosition();
		//mPelvisOffset.mV[VX] = llclamp( mPelvisOffset.mV[VX], -drift_comp_max, drift_comp_max );
		//mPelvisOffset.mV[VY] = llclamp( mPelvisOffset.mV[VY], -drift_comp_max, drift_comp_max );
		//mPelvisOffset.mV[VZ] = 0.f;
		//
		//mLastRightFootGlobalPos += LLVector3d(mPelvisOffset * avatar_to_world_rot);
		//mLastLeftFootGlobalPos += LLVector3d(mPelvisOffset * avatar_to_world_rot);

		//foot_slip_vector -= mPelvisOffset;

		LLVector3 avatar_movement_dir = avatar_velocity;
		avatar_movement_dir.normalize();

		// planted foot speed is avatar velocity - foot slip amount along avatar movement direction
		F32 foot_speed = speed - ((foot_slip_vector * avatar_movement_dir) / delta_time);

		// multiply animation playback rate so that foot speed matches avatar speed
		F32 min_speed_multiplier = clamp_rescale(speed, 0.f, 1.f, 0.f, 0.1f);
		F32 desired_speed_multiplier = llclamp(speed / foot_speed, min_speed_multiplier, ANIM_SPEED_MAX);

		// blend towards new speed adjustment value
		F32 new_speed_adjust = lerp(mAdjustedSpeed, desired_speed_multiplier, LLCriticalDamp::getInterpolant(SPEED_ADJUST_TIME_CONSTANT));

		// limit that rate at which the speed adjustment changes
		F32 speedDelta = llclamp(new_speed_adjust - mAdjustedSpeed, -SPEED_ADJUST_MAX_SEC * delta_time, SPEED_ADJUST_MAX_SEC * delta_time);
		mAdjustedSpeed += speedDelta;

		// modulate speed by dot products of facing and velocity
		// so that if we are moving sideways, we slow down the animation
		// and if we're moving backward, we walk backward
		// do this at the end to be more responsive to direction changes instead of in the above speed calculations
		F32 directional_factor = (avatar_movement_dir * world_to_avatar_rot).mV[VX];

		mAnimSpeed = mAdjustedSpeed * directional_factor;
	}
	else
	{	// standing/turning

		// damp out speed adjustment to 0
		mAnimSpeed = lerp(mAnimSpeed, 1.f, LLCriticalDamp::getInterpolant(0.2f));
		//mPelvisOffset = lerp(mPelvisOffset, LLVector3::zero, LLCriticalDamp::getInterpolant(0.2f));
	}

	// broadcast walk speed change
 	mCharacter->setAnimationData("Walk Speed", &mAnimSpeed);

	// set position
	// need to update *some* joint to keep this animation active
	mPelvisState->setPosition(mPelvisOffset);

	return TRUE;
}