void SampleNorthPoleCameraController::update(Camera& camera, PxReal dtime)
{
	// Update CCT
	if(!mBase.isPaused())
	{
		PxVec3 targetKeyDisplacement(0);
		PxVec3 targetPadDisplacement(0);

		PxVec3 forward = camera.getViewDir();
		forward.y = 0;
		forward.normalize();
		PxVec3 up = PxVec3(0,1,0);
		PxVec3 right = forward.cross(up);

		if(mFwd)	targetKeyDisplacement += forward;
		if(mBwd)	targetKeyDisplacement -= forward;

		if(mRight)	targetKeyDisplacement += right;
		if(mLeft)	targetKeyDisplacement -= right;

		targetKeyDisplacement *= mKeyShiftDown ? mRunningSpeed : mWalkingSpeed;
		targetKeyDisplacement += PxVec3(0,-9.81,0);
		targetKeyDisplacement *= dtime;

		targetPadDisplacement += forward * mGamepadForwardInc * mRunningSpeed;
		targetPadDisplacement += right * mGamepadLateralInc * mRunningSpeed;
		targetPadDisplacement += PxVec3(0,-9.81,0);
		targetPadDisplacement *= dtime;

		PxU32 flags = mCCT.move(targetKeyDisplacement + targetPadDisplacement, 0.001f, dtime, PxControllerFilters(0));
		PX_UNUSED(flags);
	}
	// Update camera
	{
		mTargetYaw		+= mGamepadYawInc * dtime;
		mTargetPitch	+= mGamepadPitchInc * dtime;
		
		// Clamp pitch
		if(mTargetPitch<mPitchMin)	mTargetPitch = mPitchMin;
		if(mTargetPitch>mPitchMax)	mTargetPitch = mPitchMax;
		
		camera.setRot(PxVec3(-mTargetPitch,-mTargetYaw,0));

		PxExtendedVec3 camTarget = computeCameraTarget();
		const float filteredHeight = feedbackFilter((float)camTarget.y, mFilterMemory, dtime*6.0f);
		camTarget.y = filteredHeight;

		const PxF32 distanceToTarget = 0.0f;
		const PxVec3 target = toVec3(camTarget) - camera.getViewDir()*distanceToTarget;
		camera.setPos(target);
	}
}