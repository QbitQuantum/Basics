//----------------------------------------------------------------------------
void Camera::LookAt(const Vector3F& rLocation, const Vector3F& rLookAt,
	const Vector3F& rUp)
{
	const Vector3F direction = rLookAt - rLocation;
	SetFrame(rLocation, direction, rUp, direction.Cross(rUp));
}