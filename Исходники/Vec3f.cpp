float Vec3f::getAngle(Vec3f v1, Vec3f v2) const //!< Returns angle between two vectors. Added by N. Van Rossum
{
	return acos( v1.dot(v2) / (v1.magnitude() * v2.magnitude()));
}