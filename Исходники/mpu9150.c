int data_fusion(mpudata_t *mpu)
{
	quaternion_t dmpQuat;
	vector3d_t dmpEuler;
	quaternion_t magQuat;
	quaternion_t unfusedQuat;
	float deltaDMPYaw;
	float deltaMagYaw;
	float newMagYaw;
	float newYaw;
	
	dmpQuat[QUAT_W] = (float)mpu->rawQuat[QUAT_W];
	dmpQuat[QUAT_X] = (float)mpu->rawQuat[QUAT_X];
	dmpQuat[QUAT_Y] = (float)mpu->rawQuat[QUAT_Y];
	dmpQuat[QUAT_Z] = (float)mpu->rawQuat[QUAT_Z];

	quaternionNormalize(dmpQuat);	
	quaternionToEuler(dmpQuat, dmpEuler);

	mpu->fusedEuler[VEC3_X] = dmpEuler[VEC3_X];
	mpu->fusedEuler[VEC3_Y] = -dmpEuler[VEC3_Y];
	mpu->fusedEuler[VEC3_Z] = 0;

	eulerToQuaternion(mpu->fusedEuler, unfusedQuat);

	deltaDMPYaw = -dmpEuler[VEC3_Z] + mpu->lastDMPYaw;
	mpu->lastDMPYaw = dmpEuler[VEC3_Z];

	magQuat[QUAT_W] = 0;
	magQuat[QUAT_X] = mpu->calibratedMag[VEC3_X];
  	magQuat[QUAT_Y] = mpu->calibratedMag[VEC3_Y];
  	magQuat[QUAT_Z] = mpu->calibratedMag[VEC3_Z];

	tilt_compensate(magQuat, unfusedQuat);

	newMagYaw = -atan2f(magQuat[QUAT_Y], magQuat[QUAT_X]);

	if (newMagYaw != newMagYaw) {
		printf("newMagYaw NAN\n");
		return -1;
	}

	if (newMagYaw < 0.0f)
		newMagYaw = TWO_PI + newMagYaw;

	newYaw = mpu->lastYaw + deltaDMPYaw;

	if (newYaw > TWO_PI)
		newYaw -= TWO_PI;
	else if (newYaw < 0.0f)
		newYaw += TWO_PI;
	 
	deltaMagYaw = newMagYaw - newYaw;
	
	if (deltaMagYaw >= (float)M_PI)
		deltaMagYaw -= TWO_PI;
	else if (deltaMagYaw < -(float)M_PI)
		deltaMagYaw += TWO_PI;

	if (yaw_mixing_factor > 0)
		newYaw += deltaMagYaw / yaw_mixing_factor;

	if (newYaw > TWO_PI)
		newYaw -= TWO_PI;
	else if (newYaw < 0.0f)
		newYaw += TWO_PI;

	mpu->lastYaw = newYaw;

	if (newYaw > (float)M_PI)
		newYaw -= TWO_PI;

	mpu->fusedEuler[VEC3_Z] = newYaw;

	eulerToQuaternion(mpu->fusedEuler, mpu->fusedQuat);

	return 0;
}