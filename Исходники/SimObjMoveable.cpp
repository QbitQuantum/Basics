void CSimObjMoveable::Calc(float total, float dt)
{
	Vector3d v = (m_dir-m_pos);
	v.Normalize();
	m_pos.x += v.x * m_speed * dt;
	m_pos.y += v.y * m_speed * dt;
	m_pos.z += v.z * m_speed * dt;

	if (Reached(m_dir, m_pos))
	{
		m_pos = m_dir;
		if (m_path.Count() > 1)
		{ 
			m_next_node = (m_next_node + 1) % m_path.Count();
			m_dir = m_path.GetNode(m_next_node);
		}
	}
	//m_pos += v * m_speed * dt;
}