glm::quat toQuat(const btQuaternion& q)
{
	return glm::quat(q.getW(), q.getX(), q.getY(), q.getZ());
}