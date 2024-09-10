	geometry::GRay GCamera::GetRayForPosition(unsigned int x, unsigned int y) const
	{
		Vector3f direction = m_frustum[0] + m_horizontal_step * x + m_vertical_step * y;
		direction.normalize();
		geometry::GRay res(m_position, direction);
		return res;
	}