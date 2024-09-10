Quaternion Quaternion::FromAngleAxis(float theta, Vector3f axis)
{
	Vector3f axisn = axis.Normalize();
	float a = theta * (float)DEGREES_TO_RADIANS;
	float scalar = sin(a / 2.0f);

	Quaternion qtrn = Quaternion(cos(a / 2.0f), axisn.x * scalar, axisn.y * scalar, axisn.z * scalar);

	qtrn.Clean();

	return qtrn.Normalize();
}