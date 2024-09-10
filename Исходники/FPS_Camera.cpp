void FPS_Cam::LookYaw(float yawValue, double dt)
{
	float mspeed = mouse_speed * yawValue;

	FaceDirection = (target - position).Normalized();
	Vector3 right = FaceDirection.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(FaceDirection).Normalized();
	rotation22.SetToRotation(mspeed * dt, 0, 1, 0);
	FaceDirection = rotation22 * FaceDirection;
	target = position + FaceDirection;

	up = rotation22 * up;
}