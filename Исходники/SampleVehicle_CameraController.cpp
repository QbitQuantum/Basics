void SampleVehicle_CameraController::update(const PxReal dtime, const PxRigidDynamic* actor, PxScene& scene)
{
	PxTransform carChassisTransfm;
	if(mLockOnFocusVehTransform)
	{
		carChassisTransfm = actor->getGlobalPose();
		mLastFocusVehTransform = carChassisTransfm;
	}
	else
	{
		carChassisTransfm = mLastFocusVehTransform;
	}

	PxF32 camDist = 15.0f;
	PxF32 cameraYRotExtra = 0.0f;

	PxVec3 velocity = mLastCarPos-carChassisTransfm.p;

	if (mCameraInit)
	{
		//Work out the forward and sideways directions.
		PxVec3 unitZ(0,0,1);
		PxVec3 carDirection = carChassisTransfm.q.rotate(unitZ);
		PxVec3 unitX(1,0,0);
		PxVec3 carSideDirection = carChassisTransfm.q.rotate(unitX);

		//Acceleration (note that is not scaled by time).
		PxVec3 acclVec = mLastCarVelocity-velocity;

		//Higher forward accelerations allow the car to speed away from the camera.
		PxF32 acclZ = carDirection.dot(acclVec);
		camDist = PxMax(camDist+acclZ*400.0f, 5.0f);

		//Higher sideways accelerations allow the car's rotation to speed away from the camera's rotation.
		PxF32 acclX = carSideDirection.dot(acclVec);
		cameraYRotExtra = -acclX*10.0f;
		//At very small sideways speeds the camera greatly amplifies any numeric error in the body and leads to a slight jitter.
		//Scale cameraYRotExtra by a value in range (0,1) for side speeds in range (0.1,1.0) and by zero for side speeds less than 0.1.
		PxFixedSizeLookupTable<4> table;
		table.addPair(0.0f, 0.0f);
		table.addPair(0.1f*dtime, 0);
		table.addPair(1.0f*dtime, 1);
		PxF32 velX = carSideDirection.dot(velocity);
		cameraYRotExtra *= table.getYVal(PxAbs(velX));
	}

	mCameraRotateAngleY+=mRotateInputY*mMaxCameraRotateSpeed*dtime;
	mCameraRotateAngleY=physx::intrinsics::fsel(mCameraRotateAngleY-10*PxPi, mCameraRotateAngleY-10*PxPi, physx::intrinsics::fsel(-mCameraRotateAngleY-10*PxPi, mCameraRotateAngleY + 10*PxPi, mCameraRotateAngleY));
	mCameraRotateAngleZ+=mRotateInputZ*mMaxCameraRotateSpeed*dtime;
	mCameraRotateAngleZ=PxClamp(mCameraRotateAngleZ,-PxPi*0.05f,PxPi*0.45f);

	PxVec3 cameraDir=PxVec3(0,0,1)*PxCos(mCameraRotateAngleY+cameraYRotExtra) + PxVec3(1,0,0)*PxSin(mCameraRotateAngleY+cameraYRotExtra);

	cameraDir=cameraDir*PxCos(mCameraRotateAngleZ)-PxVec3(0,1,0)*PxSin(mCameraRotateAngleZ);

	const PxVec3 direction = carChassisTransfm.q.rotate(cameraDir);
	PxVec3 target = carChassisTransfm.p;
	target.y+=0.5f;

	PxRaycastHit hit;
	PxSceneQueryFilterData filterData(PxSceneQueryFilterFlag::eSTATIC);
	scene.raycastSingle(target, -direction, camDist, PxSceneQueryFlag::eDISTANCE, hit, filterData, NULL, NULL);
	if (hit.shape != NULL)
	{
		camDist = hit.distance-0.25f;
	}

	camDist = PxMax(5.0f, PxMin(camDist, 50.0f));

	PxVec3 position = target-direction*camDist;

	if (mCameraInit)
	{
		dampVec3(mCameraPos, position, dtime);
		dampVec3(mCameraTargetPos, target, dtime);
	}

	mCameraPos = position;
	mCameraTargetPos = target;
	mCameraInit = true;

	mLastCarVelocity = velocity;
	mLastCarPos = carChassisTransfm.p;
}