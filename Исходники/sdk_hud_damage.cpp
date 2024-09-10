void CHudDamageIndicator::CalcDamageDirection( const Vector &vecFrom )
{
	if ( vecFrom == vec3_origin )
	{
		m_flAttackFront	= 0.0;
		m_flAttackRear	= 0.0;
		m_flAttackRight	= 0.0;
		m_flAttackLeft	= 0.0;

		return;
	}

	C_BasePlayer *pLocalPlayer = C_BasePlayer::GetLocalPlayer();
	if ( !pLocalPlayer )
	{
		return;
	}

	Vector vecDelta = ( vecFrom - pLocalPlayer->GetRenderOrigin() );

	if ( vecDelta.Length() <= 50 )
	{
		m_flAttackFront	= 1.0;
		m_flAttackRear	= 1.0;
		m_flAttackRight	= 1.0;
		m_flAttackLeft	= 1.0;

		return;
	}

	VectorNormalize( vecDelta );

	Vector forward;
	Vector right;
	AngleVectors( MainViewAngles(), &forward, &right, NULL );

	float flFront	= DotProduct( vecDelta, forward );
	float flSide	= DotProduct( vecDelta, right );

	if ( flFront > 0 )
	{
		if ( flFront > 0.3 )
			m_flAttackFront = max( m_flAttackFront, flFront );
	}
	else
	{
		float f = fabs( flFront );
		if ( f > 0.3 )
			m_flAttackRear = max( m_flAttackRear, f );
	}

	if ( flSide > 0 )
	{
		if ( flSide > 0.3 )
			m_flAttackRight = max( m_flAttackRight, flSide );
	}
	else
	{
		float f = fabs( flSide );
		if ( f > 0.3 )
			m_flAttackLeft = max( m_flAttackLeft, f );
	}
}