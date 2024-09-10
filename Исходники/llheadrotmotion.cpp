//-----------------------------------------------------------------------------
// LLHeadRotMotion::onUpdate()
//-----------------------------------------------------------------------------
BOOL LLHeadRotMotion::onUpdate(F32 time, U8* joint_mask)
{
	LLQuaternion	targetHeadRotWorld;
	LLQuaternion	currentRootRotWorld = mRootJoint->getWorldRotation();
	LLQuaternion	currentInvRootRotWorld = ~currentRootRotWorld;

	F32 head_slerp_amt = LLSmoothInterpolation::getInterpolant(HEAD_LOOKAT_LAG_HALF_LIFE);
	F32 torso_slerp_amt = LLSmoothInterpolation::getInterpolant(TORSO_LOOKAT_LAG_HALF_LIFE);

	LLVector3* targetPos = (LLVector3*)mCharacter->getAnimationData("LookAtPoint");

	if (targetPos)
	{
		LLVector3 headLookAt = *targetPos;

//		LL_INFOS() << "Look At: " << headLookAt + mHeadJoint->getWorldPosition() << LL_ENDL;

		F32 lookatDistance = headLookAt.normVec();

		if (lookatDistance < MIN_HEAD_LOOKAT_DISTANCE)
		{
			targetHeadRotWorld = mPelvisJoint->getWorldRotation();
		}
		else
		{
			LLVector3 root_up = LLVector3(0.f, 0.f, 1.f) * currentRootRotWorld;
			LLVector3 left(root_up % headLookAt);
			// if look_at has zero length, fail
			// if look_at and skyward are parallel, fail
			//
			// Test both of these conditions with a cross product.

			if (left.magVecSquared() < 0.15f)
			{
				LLVector3 root_at = LLVector3(1.f, 0.f, 0.f) * currentRootRotWorld;
				root_at.mV[VZ] = 0.f;
				root_at.normVec();

				headLookAt = lerp(headLookAt, root_at, 0.4f);
				headLookAt.normVec();

				left = root_up % headLookAt;
			}
			
			// Make sure look_at and skyward and not parallel
			// and neither are zero length
			LLVector3 up(headLookAt % left);

			targetHeadRotWorld = LLQuaternion(headLookAt, left, up);
		}
	}
	else
	{
		targetHeadRotWorld = currentRootRotWorld;
	}

	LLQuaternion head_rot_local = targetHeadRotWorld * currentInvRootRotWorld;
	head_rot_local.constrain(HEAD_ROTATION_CONSTRAINT);

	// set final torso rotation
	// Set torso target rotation such that it lags behind the head rotation
	// by a fixed amount.
	LLQuaternion torso_rot_local = nlerp(TORSO_LAG, LLQuaternion::DEFAULT, head_rot_local );
	mTorsoState->setRotation( nlerp(torso_slerp_amt, mTorsoState->getRotation(), torso_rot_local) );

	head_rot_local = nlerp(head_slerp_amt, mLastHeadRot, head_rot_local);
	mLastHeadRot = head_rot_local;

	// Set the head rotation.
	if(mNeckState->getJoint() && mNeckState->getJoint()->getParent())
	{
		LLQuaternion torsoRotLocal =  mNeckState->getJoint()->getParent()->getWorldRotation() * currentInvRootRotWorld;
		head_rot_local = head_rot_local * ~torsoRotLocal;
		mNeckState->setRotation( nlerp(NECK_LAG, LLQuaternion::DEFAULT, head_rot_local) );
		mHeadState->setRotation( nlerp(1.f - NECK_LAG, LLQuaternion::DEFAULT, head_rot_local));
	}

	return TRUE;
}