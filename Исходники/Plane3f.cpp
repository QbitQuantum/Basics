//--------------------------------------------------------------------------------
Plane3f::Plane3f(const Vector3f& normal, const Vector3f& v)
{
	auto d = -normal.Dot(v);
	m_fComponents[0] = normal.x;
	m_fComponents[1] = normal.y;
	m_fComponents[2] = normal.z;
	m_fComponents[3] = d;
}