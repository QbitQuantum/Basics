/********************************************************************************
LookRight
********************************************************************************/
void Camera3::LookRight(const double dt)
{
	float yaw = yawVelocity;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;

	up = rotation * up;
}