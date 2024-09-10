void SampleCustomGravityCameraController::update(Camera& camera, PxReal dtime)
{
	const PxExtendedVec3& currentPos = mCCT.getPosition();
	const PxVec3 curPos = toVec3(currentPos);

	// Compute up vector for current CCT position
	PxVec3 upVector;
	mBase.mPlanet.getUpVector(upVector, curPos);
	PX_ASSERT(upVector.isFinite());

	// Update CCT
	if(!mBase.isPaused())
	{
		if(1)
		{
			bool recordPos = true;
			const PxU32 currentSize = mNbRecords;
			if(currentSize)
			{
				const PxVec3 lastPos = mHistory[currentSize-1];
//				const float limit = 0.1f;
				const float limit = 0.5f;
				if((curPos - lastPos).magnitude()<limit)
					recordPos = false;
			}
			if(recordPos)
			{
				if(mNbRecords==POS_HISTORY_LIMIT)
				{
					for(PxU32 i=1;i<mNbRecords;i++)
						mHistory[i-1] = mHistory[i];
					mNbRecords--;
				}
				mHistory[mNbRecords++] = curPos;
			}
		}

		// Subtract off the 'up' component of the view direction to get our forward motion vector.
		PxVec3 viewDir = camera.getViewDir();
		PxVec3 forward = (viewDir - upVector * upVector.dot(viewDir)).getNormalized();
	
//		PxVec3 forward = mForward;

		// Compute "right" vector
		PxVec3 right = forward.cross(upVector);
		right.normalize();
//		PxVec3 right = mRightV;

		PxVec3 targetKeyDisplacement(0);
		if(mFwd)	targetKeyDisplacement += forward;
		if(mBwd)	targetKeyDisplacement -= forward;

		if(mRight)	targetKeyDisplacement += right;
		if(mLeft)	targetKeyDisplacement -= right;

		targetKeyDisplacement *= mKeyShiftDown ? mRunningSpeed : mWalkingSpeed;
//		targetKeyDisplacement += PxVec3(0,-9.81,0);
		targetKeyDisplacement *= dtime;

		PxVec3 targetPadDisplacement(0);
		targetPadDisplacement += forward * mGamepadForwardInc * mRunningSpeed;
		targetPadDisplacement += right * mGamepadLateralInc * mRunningSpeed;
//		targetPadDisplacement += PxVec3(0,-9.81,0);
		targetPadDisplacement *= dtime;


		const PxF32 heightDelta = gJump.getHeight(dtime);
//		printf("%f\n", heightDelta);
		PxVec3 upDisp = upVector;
		if(heightDelta!=0.0f)
			upDisp *= heightDelta;
		else
			upDisp *= -9.81f * dtime;
		const PxVec3 disp = targetKeyDisplacement + targetPadDisplacement + upDisp;

//upDisp.normalize();
//printf("%f | %f | %f\n", upDisp.x, upDisp.y, upDisp.z);
//		printf("%f | %f | %f\n", targetKeyDisplacement.x, targetKeyDisplacement.y, targetKeyDisplacement.z);
//		printf("%f | %f | %f\n\n", targetPadDisplacement.x, targetPadDisplacement.y, targetPadDisplacement.z);

		mCCT.setUpDirection(upVector);
		const PxU32 flags = mCCT.move(disp, 0.001f, dtime, PxControllerFilters());
		if(flags & PxControllerFlag::eCOLLISION_DOWN)
		{
			gJump.stopJump();
//			printf("Stop jump\n");
		}
	}

	// Update camera
	if(1)
	{
		mTargetYaw		+= mGamepadYawInc * dtime;
		mTargetPitch	+= mGamepadPitchInc * dtime;

		// Clamp pitch
//		if(mTargetPitch<mPitchMin)	mTargetPitch = mPitchMin;
//		if(mTargetPitch>mPitchMax)	mTargetPitch = mPitchMax;
	}

	if(1)
	{
		PxVec3 up = upVector;

		PxQuat localPitchQ(mTargetPitch, PxVec3(1.0f, 0.0f, 0.0f));
		PX_ASSERT(localPitchQ.isSane());
		PxMat33 localPitchM(localPitchQ);

		const PxVec3 upRef(0.0f, 1.0f, 0.0f);

		PxQuat localYawQ(mTargetYaw, upRef);
		PX_ASSERT(localYawQ.isSane());
		PxMat33 localYawM(localYawQ);

			bool res;
			PxQuat localToWorldQ = rotationArc(upRef, up, res);
			static PxQuat memory(0,0,0,1);
			if(!res)
			{
				localToWorldQ = memory;
			}
			else
			{
				memory = localToWorldQ;
			}
			PX_ASSERT(localToWorldQ.isSane());
			PxMat33 localToWorld(localToWorldQ);
		

			static PxVec3 previousUp(0.0f, 1.0f, 0.0f);
			static PxQuat incLocalToWorldQ(0.0f, 0.0f, 0.0f, 1.0f);
			PxQuat incQ = rotationArc(previousUp, up, res);
			PX_ASSERT(incQ.isSane());
//			incLocalToWorldQ = incLocalToWorldQ * incQ;
			incLocalToWorldQ = incQ * incLocalToWorldQ;
			PX_ASSERT(incLocalToWorldQ.isSane());
			incLocalToWorldQ.normalize();
			PxMat33 incLocalToWorldM(incLocalToWorldQ);
			localToWorld = incLocalToWorldM;
			previousUp = up;

mTest = localToWorld;
//mTest = localToWorld * localYawM;

//		PxMat33 rot = localYawM * localToWorld;
		PxMat33 rot = localToWorld * localYawM * localPitchM;
//		PxMat33 rot = localToWorld * localYawM;
		PX_ASSERT(rot.column0.isFinite());
		PX_ASSERT(rot.column1.isFinite());
		PX_ASSERT(rot.column2.isFinite());

		////

		PxMat44 view(rot.column0, rot.column1, rot.column2, PxVec3(0));

		mForward = -rot.column2;
		mRightV = rot.column0;

		camera.setView(PxTransform(view));
		PxVec3 viewDir = camera.getViewDir();
		PX_ASSERT(viewDir.isFinite());

		////

		PxRigidActor* characterActor = mCCT.getActor();
		
		PxShape* shape;
		characterActor->getShapes(&shape,1);

		PxCapsuleGeometry geom;
		shape->getCapsuleGeometry(geom);

		up *= geom.halfHeight+geom.radius;

		const PxVec3 headPos = curPos + up;
		const float distanceToTarget = 10.0f;
//		const float distanceToTarget = 20.0f;
//		const float distanceToTarget = 5.0f;
//		const PxVec3 camPos = headPos - viewDir*distanceToTarget;
		const PxVec3 camPos = headPos - mForward*distanceToTarget;// + up * 20.0f;
//		view.t = camPos;
		view.column3 = PxVec4(camPos,0);
//		camera.setView(view);
		camera.setView(PxTransform(view));
		mTarget = headPos;
	}

	if(0)
	{
		PxControllerState cctState;
		mCCT.getState(cctState);
		printf("\nCCT state:\n");
		printf("delta:             %.02f | %.02f | %.02f\n", cctState.deltaXP.x, cctState.deltaXP.y, cctState.deltaXP.z);
		printf("touchedShape:      %p\n", cctState.touchedShape);
		printf("touchedObstacle:   %p\n", cctState.touchedObstacle);
		printf("standOnAnotherCCT: %d\n", cctState.standOnAnotherCCT);
		printf("standOnObstacle:   %d\n", cctState.standOnObstacle);
		printf("isMovingUp:        %d\n", cctState.isMovingUp);
		printf("collisionFlags:    %d\n", cctState.collisionFlags);
	}

}