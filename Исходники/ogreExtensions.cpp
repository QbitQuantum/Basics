	Quaternion toOgreQuaternion(const btQuaternion& quat)
	{
		return Quaternion(quat.getW(), quat.getX(), quat.getY(), quat.getZ());
	}