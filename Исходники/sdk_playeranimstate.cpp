void CSDKPlayerAnimState::ComputePoseParam_AimYaw( CStudioHdr *pStudioHdr )
{
	if (m_pSDKPlayer->m_Shared.IsSliding() && !m_pSDKPlayer->m_Shared.IsDiveSliding())
	{
		Vector vecVelocity;
		GetOuterAbsVelocity( vecVelocity );

		QAngle angDir;
		VectorAngles(vecVelocity, angDir);

		//if (m_bFacingForward)
		m_flGoalFeetYaw = angDir[YAW];
		//else
		//	m_flGoalFeetYaw = AngleNormalize(angDir[YAW] + 180);

		m_flGoalFeetYaw = AngleNormalize( m_flGoalFeetYaw );
		if ( m_flGoalFeetYaw != m_flCurrentFeetYaw )
		{
			ConvergeYawAngles( m_flGoalFeetYaw, 720.0f, gpGlobals->frametime * m_pSDKPlayer->GetSlowMoMultiplier(), m_flCurrentFeetYaw );
			m_flLastAimTurnTime = m_pSDKPlayer->GetCurrentTime();
		}

		QAngle angSlide;
		VectorAngles(m_pSDKPlayer->m_Shared.GetSlideDirection(), angSlide);
		m_angRender[YAW] = angSlide.y;

		// Get the view yaw.
		float flAngle = AngleNormalize( m_flEyeYaw );

		// Calc side to side turning - the view vs. movement yaw.
		float flAimYaw = angSlide.y - flAngle;
		flAimYaw = AngleNormalize( flAimYaw );

		// Set the aim yaw and save.
		GetBasePlayer()->SetPoseParameter( pStudioHdr, m_PoseParameterData.m_iAimYaw, flAimYaw );
		m_DebugAnimData.m_flAimYaw	= flAimYaw;

		// Turn off a force aim yaw - either we have already updated or we don't need to.
		m_bForceAimYaw = false;

#ifndef CLIENT_DLL
		QAngle angle = GetBasePlayer()->GetAbsAngles();
		angle[YAW] = m_flCurrentFeetYaw;

		GetBasePlayer()->SetAbsAngles( angle );
#endif

		return;
	}
	if (m_bFlipping)
	{
		m_angRender[YAW] = m_flEyeYaw;
#ifndef CLIENT_DLL
		QAngle angle = GetBasePlayer()->GetAbsAngles();
		angle[YAW] = m_flCurrentFeetYaw;

		GetBasePlayer()->SetAbsAngles( angle );
#endif
		return;
	}
	// Get the movement velocity.
	Vector vecVelocity;
	GetOuterAbsVelocity( vecVelocity );

	// Check to see if we are moving.
	bool bMoving = ( vecVelocity.Length() > 1.0f ) ? true : false;

	if ( m_pSDKPlayer->m_Shared.IsProne() )
	{
		m_flGoalFeetYaw = m_flCurrentFeetYaw = m_flEyeYaw;
	}
	else if ( bMoving || m_bForceAimYaw )
	{
		if (m_pSDKPlayer->m_Shared.IsAimedIn() || m_pSDKPlayer->m_Shared.IsDiving() || m_pSDKPlayer->m_Shared.IsRolling() || m_pSDKPlayer->m_Shared.IsSliding())
		{
			// The feet match the eye direction when moving - the move yaw takes care of the rest.
			m_flGoalFeetYaw = m_flEyeYaw;
		}
		else
		{
			QAngle angDir;
			VectorAngles(vecVelocity, angDir);

			if (m_bFacingForward)
			{
				m_flGoalFeetYaw = angDir[YAW];
			}
			else
			{
				m_flGoalFeetYaw = AngleNormalize(angDir[YAW] + 180);
			}
		}
	}
	// Else if we are not moving.
	else
	{
		// Initialize the feet.
		if ( m_PoseParameterData.m_flLastAimTurnTime <= 0.0f )
		{
			m_flGoalFeetYaw	= m_flEyeYaw;
			m_flCurrentFeetYaw = m_flEyeYaw;
			m_PoseParameterData.m_flLastAimTurnTime = m_pSDKPlayer->GetCurrentTime();
		}
		// Make sure the feet yaw isn't too far out of sync with the eye yaw.
		// TODO: Do something better here!
		else
		{
			float flYawDelta = AngleNormalize(  m_flGoalFeetYaw - m_flEyeYaw );

			if ( fabs( flYawDelta ) > 75.0f )
			{
				float flSide = ( flYawDelta > 0.0f ) ? -1.0f : 1.0f;
				m_flGoalFeetYaw += ( 75.0f * flSide );
			}
		}
	}

	// Fix up the feet yaw.
	m_flGoalFeetYaw = AngleNormalize( m_flGoalFeetYaw );
	if ( m_flGoalFeetYaw != m_flCurrentFeetYaw )
	{
		if ( m_bForceAimYaw )
		{
			m_flCurrentFeetYaw = m_flGoalFeetYaw;
		}
		else
		{
			ConvergeYawAnglesThroughZero( m_flGoalFeetYaw, 720.0f, gpGlobals->frametime * m_pSDKPlayer->GetSlowMoMultiplier(), m_flCurrentFeetYaw );
			m_flLastAimTurnTime = m_pSDKPlayer->GetCurrentTime();
		}
	}

	if (m_pSDKPlayer->m_Shared.IsDiving())
		m_flCurrentFeetYaw = m_flGoalFeetYaw;

	// Rotate the body into position.
	m_angRender[YAW] = m_flCurrentFeetYaw;

	// Find the aim(torso) yaw base on the eye and feet yaws.
	float flAimYaw = m_flEyeYaw - m_flCurrentFeetYaw;

	if (m_pSDKPlayer->IsInThirdPerson())
		flAimYaw = m_flCharacterEyeYaw - m_flCurrentFeetYaw;

	flAimYaw = AngleNormalize( flAimYaw );

	// Set the aim yaw and save.
	GetBasePlayer()->SetPoseParameter( pStudioHdr, m_PoseParameterData.m_iAimYaw, -flAimYaw );
	m_DebugAnimData.m_flAimYaw	= flAimYaw;

	// Turn off a force aim yaw - either we have already updated or we don't need to.
	m_bForceAimYaw = false;

#ifndef CLIENT_DLL
	QAngle angle = GetBasePlayer()->GetAbsAngles();
	angle[YAW] = m_flCurrentFeetYaw;

	GetBasePlayer()->SetAbsAngles( angle );
#endif
}