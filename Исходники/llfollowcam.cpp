//-------------------------------------------------------------------------------------
BOOL LLFollowCam::updateBehindnessConstraint(LLVector3 focus, LLVector3& cam_position)
{
	BOOL constraint_active = FALSE;
	// only apply this stuff if the behindness angle is something other than opened up all the way
	if ( mBehindnessMaxAngle < FOLLOW_CAM_MAX_BEHINDNESS_ANGLE - FOLLOW_CAM_BEHINDNESS_EPSILON )
	{
		//--------------------------------------------------------------
		// horizontalized vector from focus to camera 
		//--------------------------------------------------------------
		LLVector3 horizontalVectorFromFocusToCamera;
		horizontalVectorFromFocusToCamera.setVec(cam_position - focus);
		horizontalVectorFromFocusToCamera.mV[ VZ ] = 0.0f; 
		F32 cameraZ = cam_position.mV[ VZ ];

		//--------------------------------------------------------------
		// distance of horizontalized vector
		//--------------------------------------------------------------
		F32 horizontalDistance = horizontalVectorFromFocusToCamera.magVec();

		//--------------------------------------------------------------------------------------------------
		// calculate horizontalized back vector of the subject and scale by horizontalDistance
		//--------------------------------------------------------------------------------------------------
		LLVector3 horizontalSubjectBack( -1.0f, 0.0f, 0.0f );
		horizontalSubjectBack *= mSubjectRotation;
		horizontalSubjectBack.mV[ VZ ] = 0.0f; 
		horizontalSubjectBack.normVec(); // because horizontalizing might make it shorter than 1
		horizontalSubjectBack *= horizontalDistance;

		//--------------------------------------------------------------------------------------------------
		// find the angle (in degrees) between these vectors
		//--------------------------------------------------------------------------------------------------
		F32 cameraOffsetAngle = 0.f;
		LLVector3 cameraOffsetRotationAxis;
		LLQuaternion camera_offset_rotation;
		camera_offset_rotation.shortestArc(horizontalSubjectBack, horizontalVectorFromFocusToCamera);
		camera_offset_rotation.getAngleAxis(&cameraOffsetAngle, cameraOffsetRotationAxis);
		cameraOffsetAngle *= RAD_TO_DEG;

		if ( cameraOffsetAngle > mBehindnessMaxAngle )
		{
			F32 fraction = ((cameraOffsetAngle - mBehindnessMaxAngle) / cameraOffsetAngle) * LLCriticalDamp::getInterpolant(mBehindnessLag);
			cam_position = focus + horizontalSubjectBack * (slerp(fraction, camera_offset_rotation, LLQuaternion::DEFAULT));
			cam_position.mV[VZ] = cameraZ; // clamp z value back to what it was before we started messing with it
			constraint_active = TRUE;
		}
	}
	return constraint_active;
}