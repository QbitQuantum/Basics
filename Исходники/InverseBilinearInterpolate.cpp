void InverseBilinearInterpolate::setVertices(const Vector3F & a, const Vector3F & b, const Vector3F & c, const Vector3F & d)
{
	Vector3F side = b - a; side.normalize();
	Vector3F up = c - a;
	Vector3F front = side.cross(up); front.normalize();
	up = front.cross(side); up.normalize();
	
	m_space.setIdentity();
	m_space.setTranslation(a);
	m_space.setOrientations(side, up, front);
	m_space.inverse();
	
	Vector3F A = m_space.transform(a);

	Vector3F B = m_space.transform(b);
	m_E.set(B.x, B.y);

	Vector3F C = m_space.transform(c);
	m_F.set(C.x, C.y);
	
	Vector3F D = m_space.transform(d);
	
	m_G.set(-B.x - C.x + D.x, -B.y - C.y + D.y);
}