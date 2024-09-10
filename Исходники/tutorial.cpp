	b3Vector3 getVelocity(const b3Vector3& relPos) const
	{
		return m_linearVelocity + m_angularVelocity.cross(relPos);
	}