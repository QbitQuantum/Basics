static float angle(const MT_Vector3& v1, const MT_Vector3& v2)
{
	return safe_acos(v1.dot(v2));
}