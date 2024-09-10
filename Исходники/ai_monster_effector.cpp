BOOL CMonsterEffector::Process(SPPInfo& pp)
{
	inherited::Process(pp);

	// amount of time passed in percents
	float time_past_perc = (m_total - fLifeTime) / m_total;

	float factor;
	if (time_past_perc < m_attack) 
		factor = time_past_perc / m_attack;
	else if ((time_past_perc >= m_attack) && (time_past_perc <= m_release)) 
		factor = 1.0f;
	else 
		factor = (1.0f - time_past_perc) / (1.0f - m_release);

	clamp(factor,0.01f,1.0f);

	pp.lerp				(pp_identity, state, factor * m_spec_factor);
	return TRUE;
}