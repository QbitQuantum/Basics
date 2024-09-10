Fvector CDetailPathManager::direction() const
{
	if ((m_path.size() < 2) || (m_path.size() <= m_current_travel_point + 1))
		return				(Fvector().set(0,0,1));
	
	Fvector					direction;
	direction.sub			(m_path[m_current_travel_point + 1].position, m_path[m_current_travel_point].position);

	if (direction.square_magnitude() < EPS_L)
		direction.set		(0.f,0.f,1.f);
	else
		direction.normalize	();

	return					(direction);
}