void rotate_degrees(QuaternionTransform &qt, float amt)
{
	XMVECTOR quat = XMLoadFloat4(&qt.quat);

	XMVECTOR axis;
	float angle;
	XMQuaternionToAxisAngle(&axis, &angle, quat);

	angle = XMConvertToDegrees(angle);
	angle += amt;
	angle = XMConvertToRadians(angle);

	quat = XMQuaternionRotationAxis(axis, angle);

	XMStoreFloat4(&qt.quat, quat);
}