void Camera::lookAt(const PxVec3& position, const PxVec3& target)
{
	PxVec3 dir = target - position;
	dir.normalize();

	PxVec3 right, up;
	computeBasis(dir, right, up);

	PxTransform view;
	view.p	= position;
	view.q	= PxQuat(PxMat33(-right, up, -dir));
	setView(view);
}