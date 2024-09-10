Quat Json2Quat(const Json::Value& value)
{
	Quat ret;
	Vector3 v3;
	v3.x = (float)value[(size_t)0].asDouble();
	v3.y = (float)value[1].asDouble();
	v3.z = (float)value[2].asDouble();
	XMVECTOR q = XMQuaternionRotationRollPitchYaw(v3.x * Angle2Radian, v3.y * Angle2Radian, v3.z * Angle2Radian);
	XMStoreFloat4((XMFLOAT4*)&ret, q);
	return ret;
}