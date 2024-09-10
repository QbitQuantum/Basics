void OVRRenderer::update(float delta)
{
	if (!_instance) return;
	const dpnHmdParms headModelParms = dpnutilDefaultHmdParms();
	//dpnnSensorData tracking;
	//dpnnGetSensorData(OVRHelper::dpInstance, &tracking);

	//CCLOG("dpnnSensorData: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)", tracking.angular_velocity.x, tracking.angular_velocity.y, tracking.angular_velocity.z
	//	, tracking.linear_acceleration.x, tracking.linear_acceleration.y, tracking.linear_acceleration.z
	//	, tracking.magnetometer.x, tracking.magnetometer.y, tracking.magnetometer.z);

	//const dpnMatrix4 centerEyeViewMatrix = dpnutilGetCenterEyeViewMatrix(&headModelParms, tracking, NULL);

	const dpnnQuarterion pose = dpnnGetPose(_instance);
	const dpnnVector3 position = dpnnGetPosition(_instance);

	for (int eye = 0; eye < EYE_NUM; eye++) {
		//const dpnMatrix4 eyeViewMatrix = dpnutilGetEyeViewMatrix(&headModelParms, &centerEyeViewMatrix, eye);
		//Mat4 viewMat;
		//viewMat.set((const GLfloat *)(dpnutilMatrix4_Transpose(&eyeViewMatrix).M[0]));
		//viewMat.inverse();

		float eyeOffset = (eye ? -0.5f : 0.5f) * headModelParms.ipd;
		Mat4 posMat, rotMat, offsetMat;
		Mat4::createRotation(Quaternion(pose.i, pose.j, pose.k, pose.s), &rotMat);
		Mat4::createTranslation(Vec3(position.x, position.y, position.z), &posMat);
		Mat4::createTranslation(Vec3(eyeOffset, 0.0f, 0.0f), &offsetMat);
		Mat4 viewMat = offsetMat * posMat * rotMat;

		Quaternion quat;
		Vec3 pos;
		viewMat.decompose(nullptr, &quat, &pos);
		quat = _offsetRot * quat;
		Vec3 up = quat * Vec3::UNIT_Y;
		Vec3 forword = quat * -Vec3::UNIT_Z;
		Vec3 shiftedEyePos = _offsetPos + _offsetRot * pos;
		_eyeCamera[eye]->setPosition3D(shiftedEyePos);
		_eyeCamera[eye]->lookAt(shiftedEyePos + forword, up);
		CCLOG("OVRRenderer::camera[%d]-ROT(%f, %f, %f, %f) -POS(%f, %f, %f)", eye, quat.w, quat.x, quat.y, quat.z, pos.x, pos.y, pos.z);
	}

	CCLOG("OVRRenderer::update");
}