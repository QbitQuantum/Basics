CameraClass::CameraClass()
{
	mPosition = XMFLOAT3(0.0f, 0.0f, -10.0f);
	mRotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	mLookAt = XMFLOAT3(0.0f, 0.0f, 1.0f);
	mUp = XMFLOAT3(0.0f, 1.0f, 0.0f);

	XMStoreFloat4x4(&mViewMatrix, XMMatrixLookAtLH(XMLoadFloat3(&mPosition), XMLoadFloat3(&mLookAt), XMLoadFloat3(&mUp)));

	mFrameTime = 0.0f;

	mForwardSpeed = 0.0f;
	mBackwardSpeed = 0.0f;
	mLeftSpeed = 0.0f;
	mRightSpeed = 0.0f;
	mUpwardSpeed = 0.0f;
	mDownwardSpeed = 0.0f;
	mLeftTurnSpeed = 0.0f;
	mRightTurnSpeed = 0.0f;
	mLookUpSpeed = 0.0f;
	mLookDownSpeed = 0.0f;

	mLastMousePosition.x = 400;
	mLastMousePosition.y = 300;

	ClientToScreen(GetActiveWindow(), &mLastMousePosition);
}