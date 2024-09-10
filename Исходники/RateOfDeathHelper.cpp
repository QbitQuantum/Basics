float CRateOfDeathHelper_Target::CalculateStayAliveTime_Direction( const CRateOfDeathHelper_AttackerInfo& attacker ) const
{
	CRY_ASSERT( m_pTarget );

	const float directionInc = RateOfDeath::GetDirectionInc();

	const Vec3& attackerPosition = attacker.GetPosition();
	const Vec3& targetPosition = m_pTarget->GetPos();
	Vec3 targetDirection = targetPosition - attackerPosition;
	const float targetDistance = targetDirection.NormalizeSafe();

	const float thr1 = cosf( DEG2RAD( 30.0f ) );
	const float thr2 = cosf( DEG2RAD( 95.0f ) );

	const Vec3& targetViewDirection = m_pTarget->GetViewDir();
	const float dot = -targetDirection.Dot( targetViewDirection );
	if ( dot < thr2 )
	{
		return directionInc * 2.0f;
	}
	else if ( dot < thr1 )
	{
		return directionInc;
	}

	return 0;
}