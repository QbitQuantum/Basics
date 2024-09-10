	void get_plane_equation_transformed(const btTransform& trans, btVector4& equation) const
	{
		const btVector3 normal = trans.getBasis() * m_planeNormal;
		equation[0] = normal[0];
		equation[1] = normal[1];
		equation[2] = normal[2];
		equation[3] = normal.dot(trans * (m_planeConstant * m_planeNormal));
	}