void CameraComponent::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	Vector3 ideal = ComputeIdealPosition();
	Vector3 displace = mCameraPos - ideal;
	Vector3 accel = (-mSpringConstant * displace) - (mDampConstant * mCameraVelocity);
	mCameraVelocity += accel * deltaTime;
	mCameraPos += mCameraVelocity * deltaTime;

	Vector3 shipPos = mOwner.GetWorldTransform().GetTranslation() +
		Vector3::UnitX * mTargetOffset;
	Vector3 forward = shipPos - mCameraPos;
	forward.Normalize();
	Vector3 left = Cross(Vector3::UnitZ, forward);
	left.Normalize();
	Vector3 up = Cross(forward, left);
	up.Normalize();

	mCameraMat = Matrix4::CreateLookAt(mCameraPos, shipPos, up);
	
	// Tell the renderer
	mOwner.GetGame().GetRenderer().UpdateViewMatrix(mCameraMat);
}