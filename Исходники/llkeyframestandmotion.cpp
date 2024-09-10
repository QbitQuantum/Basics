//-----------------------------------------------------------------------------
// LLKeyframeStandMotion::onUpdate()
//-----------------------------------------------------------------------------
BOOL LLKeyframeStandMotion::onUpdate(F32 time, U8* joint_mask)
{
	//-------------------------------------------------------------------------
	// let the base class update the cycle
	//-------------------------------------------------------------------------
	BOOL status = LLKeyframeMotion::onUpdate(time, joint_mask);
	if (!status)
	{
		return FALSE;
	}

	LLVector3 root_world_pos = mPelvisState->getJoint()->getParent()->getWorldPosition();

	// have we received a valid world position for this avatar?
	if (root_world_pos.isExactlyZero())
	{
		return TRUE;
	}

	//-------------------------------------------------------------------------
	// Stop tracking (start locking) ankles once ease in is done.
	// Setting this here ensures we track until we get valid foot position.
	//-------------------------------------------------------------------------
	if (dot(mPelvisState->getJoint()->getWorldRotation(), mLastGoodPelvisRotation) < ROTATION_THRESHOLD)
	{
		mLastGoodPelvisRotation = mPelvisState->getJoint()->getWorldRotation();
		mLastGoodPelvisRotation.normalize();
		mTrackAnkles = TRUE;
	}
	else if ((mCharacter->getCharacterPosition() - mLastGoodPosition).magVecSquared() > POSITION_THRESHOLD)
	{
		mLastGoodPosition = mCharacter->getCharacterPosition();
		mTrackAnkles = TRUE;
	}
	else if (mPose.getWeight() < 1.f)
	{
		mTrackAnkles = TRUE;
	}


	//-------------------------------------------------------------------------
	// propagate joint positions to internal versions
	//-------------------------------------------------------------------------
	mPelvisJoint.setPosition(
			root_world_pos +
			mPelvisState->getPosition() );

	mHipLeftJoint.setPosition( mHipLeftState->getJoint()->getPosition() );
	mKneeLeftJoint.setPosition( mKneeLeftState->getJoint()->getPosition() );
	mAnkleLeftJoint.setPosition( mAnkleLeftState->getJoint()->getPosition() );

	mHipLeftJoint.setScale( mHipLeftState->getJoint()->getScale() );
	mKneeLeftJoint.setScale( mKneeLeftState->getJoint()->getScale() );
	mAnkleLeftJoint.setScale( mAnkleLeftState->getJoint()->getScale() );

	mHipRightJoint.setPosition( mHipRightState->getJoint()->getPosition() );
	mKneeRightJoint.setPosition( mKneeRightState->getJoint()->getPosition() );
	mAnkleRightJoint.setPosition( mAnkleRightState->getJoint()->getPosition() );

	mHipRightJoint.setScale( mHipRightState->getJoint()->getScale() );
	mKneeRightJoint.setScale( mKneeRightState->getJoint()->getScale() );
	mAnkleRightJoint.setScale( mAnkleRightState->getJoint()->getScale() );
	//-------------------------------------------------------------------------
	// propagate joint rotations to internal versions
	//-------------------------------------------------------------------------
	mPelvisJoint.setRotation( mPelvisState->getJoint()->getWorldRotation() );

#if GO_TO_KEY_POSE
	mHipLeftJoint.setRotation( mHipLeftState->getRotation() );
	mKneeLeftJoint.setRotation( mKneeLeftState->getRotation() );
	mAnkleLeftJoint.setRotation( mAnkleLeftState->getRotation() );

	mHipRightJoint.setRotation( mHipRightState->getRotation() );
	mKneeRightJoint.setRotation( mKneeRightState->getRotation() );
	mAnkleRightJoint.setRotation( mAnkleRightState->getRotation() );
#else
	mHipLeftJoint.setRotation( mHipLeftState->getJoint()->getRotation() );
	mKneeLeftJoint.setRotation( mKneeLeftState->getJoint()->getRotation() );
	mAnkleLeftJoint.setRotation( mAnkleLeftState->getJoint()->getRotation() );

	mHipRightJoint.setRotation( mHipRightState->getJoint()->getRotation() );
	mKneeRightJoint.setRotation( mKneeRightState->getJoint()->getRotation() );
	mAnkleRightJoint.setRotation( mAnkleRightState->getJoint()->getRotation() );
#endif

	// need to wait for underlying keyframe motion to affect the skeleton
	if (mFrameNum == 2)
	{
		mIKLeft.setupJoints( &mHipLeftJoint, &mKneeLeftJoint, &mAnkleLeftJoint, &mTargetLeft );
		mIKRight.setupJoints( &mHipRightJoint, &mKneeRightJoint, &mAnkleRightJoint, &mTargetRight );
	}
	else if (mFrameNum < 2)
	{
		mFrameNum++;
		return TRUE;
	}

	mFrameNum++;

	//-------------------------------------------------------------------------
	// compute target position by projecting ankles to the ground
	//-------------------------------------------------------------------------
	if ( mTrackAnkles )
	{
		mCharacter->getGround( mAnkleLeftJoint.getWorldPosition(), mPositionLeft, mNormalLeft);
		mCharacter->getGround( mAnkleRightJoint.getWorldPosition(), mPositionRight, mNormalRight);

		mTargetLeft.setPosition( mPositionLeft );
		mTargetRight.setPosition( mPositionRight );
	}

	//-------------------------------------------------------------------------
	// update solvers
	//-------------------------------------------------------------------------
	mIKLeft.solve();
	mIKRight.solve();

	//-------------------------------------------------------------------------
	// make ankle rotation conform to the ground
	//-------------------------------------------------------------------------
	if ( mTrackAnkles )
	{
		LLVector4 dirLeft4 = mAnkleLeftJoint.getWorldMatrix().getFwdRow4();
		LLVector4 dirRight4 = mAnkleRightJoint.getWorldMatrix().getFwdRow4();
		LLVector3 dirLeft = vec4to3( dirLeft4 );
		LLVector3 dirRight = vec4to3( dirRight4 );

		LLVector3 up;
		LLVector3 dir;
		LLVector3 left;

		up = mNormalLeft;
		up.normVec();
		if (mFlipFeet)
		{
			up *= -1.0f;
		}
		dir = dirLeft;
		dir.normVec();
		left = up % dir;
		left.normVec();
		dir = left % up;
		mRotationLeft = LLQuaternion( dir, left, up );

		up = mNormalRight;
		up.normVec();
		if (mFlipFeet)
		{
			up *= -1.0f;
		}
		dir = dirRight;
		dir.normVec();
		left = up % dir;
		left.normVec();
		dir = left % up;
		mRotationRight = LLQuaternion( dir, left, up );
	}
	mAnkleLeftJoint.setWorldRotation( mRotationLeft );
	mAnkleRightJoint.setWorldRotation( mRotationRight );

	//-------------------------------------------------------------------------
	// propagate joint rotations to joint states
	//-------------------------------------------------------------------------
	mHipLeftState->setRotation( mHipLeftJoint.getRotation() );
	mKneeLeftState->setRotation( mKneeLeftJoint.getRotation() );
	mAnkleLeftState->setRotation( mAnkleLeftJoint.getRotation() );

	mHipRightState->setRotation( mHipRightJoint.getRotation() );
	mKneeRightState->setRotation( mKneeRightJoint.getRotation() );
	mAnkleRightState->setRotation( mAnkleRightJoint.getRotation() );

	//llinfos << "Stand drift amount " << (mCharacter->getCharacterPosition() - mLastGoodPosition).magVec() << llendl;

//	llinfos << "DEBUG: " << speed << " : " << mTrackAnkles << llendl;
	return TRUE;
}