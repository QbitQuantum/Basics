void game_physics_engine::CParticalBungee::UpdateForce( CPartical* pPartical, const real duration )
{
	assert(pPartical != nullptr);
	if (pPartical == NULL)
	{
		return;
	}

	CVector3 force = pPartical->GetPosition();
	force -= m_pOther->GetPosition();
	real magnitude = force.Magnitude();
	if (magnitude <= m_fRestLength)
	{
		return;
	}

	magnitude -= m_fRestLength;
	magnitude *= m_fSpringConstant;
	force.Normalize();
	force *= -magnitude;
	pPartical->AddForce(force);
}