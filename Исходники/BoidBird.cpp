void CBoidBird::ClampSpeed(SBoidContext& bc,float dt)
{
	if(m_status == Bird::ON_GROUND)
	{
		if(m_onGroundStatus == Bird::OGS_WALKING)
		{
			m_speed = m_walkSpeed;
		}
		else if(m_onGroundStatus == Bird::OGS_SLOWINGDOWN)
		{
			float elapsedTimeNormalized = clamp_tpl(m_elapsedSlowdownTime / bc.fWalkToIdleDuration, 0.0f, 1.0f);
			m_speed = LERP(m_walkSpeed, 0.0f, elapsedTimeNormalized);
		}
		else if(m_onGroundStatus == Bird::OGS_IDLE)
		{
			m_speed = 0.0f;
		}
	}
	else
	{
		if (m_speed > bc.MaxSpeed)
			m_speed = bc.MaxSpeed;
		if (m_speed < bc.MinSpeed)
			m_speed = bc.MinSpeed;
	}
}