void PlayerCameraOgre::onRightButtonPressed()
{
	if (!mRightButtonPressedLastFrame)
		mMousePosLastFrame = mMouse->getPosition();

	mp::Vector2i diff = mMouse->getPosition() - mMousePosLastFrame;
	const mp::Vector3f &playerPos = mPlayer->model()->getPosition();
	Ogre::Vector3 pivotPoint(playerPos.getX(), playerPos.getY() + mPivotHeight, playerPos.getZ());
	float yaw = (float)diff.getX() * CAMERA_SPEED;
	float pitch = (float)-diff.getY() * CAMERA_SPEED;

	Ogre::Quaternion yawQuat;
	yawQuat.FromAngleAxis(Ogre::Radian(yaw), Ogre::Vector3::UNIT_Y);
	Ogre::Matrix3 yawMat;
	yawQuat.ToRotationMatrix(yawMat);

	Ogre::Vector3 pivotToPos = Ogre::Vector3(mRealPosition.getX(), mRealPosition.getY(), mRealPosition.getZ()) - pivotPoint;
	Ogre::Matrix4 pos(1, 0, 0, pivotToPos.x,
		0, 1, 0, pivotToPos.y,
		0, 0, 1, pivotToPos.z,
		0, 0, 0, 1);

	Ogre::Vector3 xz(pivotToPos.x, 0, pivotToPos.z);
	Ogre::Vector3 norm(-xz.z, 0, xz.x);
	Ogre::Quaternion pitchQuat;
	pitchQuat.FromAngleAxis(Ogre::Radian(pitch), norm);
	Ogre::Matrix3 pitchMat;
	pitchQuat.ToRotationMatrix(pitchMat);

	Ogre::Matrix4 toPivot(1, 0, 0, pivotPoint.x,
		0, 1, 0, pivotPoint.y,
		0, 0, 1, pivotPoint.z,
		0, 0, 0, 1);

	Ogre::Matrix4 newPosMat = pos * pitchMat * yawMat * toPivot;
	newPosMat = newPosMat.inverse();
	Ogre::Vector3 newPos = newPosMat.getTrans();
	mRealPosition.set(-newPos.x, -newPos.y, -newPos.z);
	setPosition(mRealPosition);
	lookAt(pivotPoint.x, pivotPoint.y, pivotPoint.z);

	adjustDistance();

	mMousePosLastFrame = mMouse->getPosition();
	mRightButtonPressedLastFrame = true;
}