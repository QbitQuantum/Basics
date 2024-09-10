void CFuncTank::TrackTarget( void )
{
	trace_t tr;
	bool updateTime = FALSE, lineOfSight;
	QAngle angles;
	Vector barrelEnd;
	CBaseEntity *pTarget = NULL;

	barrelEnd.Init();

	// Get a position to aim for
	if (m_pController)
	{
		// Tanks attempt to mirror the player's angles
		angles = m_pController->EyeAngles();
		SetNextThink( gpGlobals->curtime + 0.05 );
	}
	else
	{
		if ( IsActive() )
		{
			SetNextThink( gpGlobals->curtime + 0.1f );
		}
		else
		{
			return;
		}

		// -----------------------------------
		//  Get world target position
		// -----------------------------------
		barrelEnd = WorldBarrelPosition();
		Vector worldTargetPosition;
		if (m_spawnflags & SF_TANK_AIM_AT_POS)
		{
			worldTargetPosition = m_vTargetPosition;
		}
		else
		{
			CBaseEntity *pEntity = (CBaseEntity *)m_hTarget;
			if ( !pEntity || ( pEntity->GetFlags() & FL_NOTARGET ) )
			{
				if ( m_targetEntityName != NULL_STRING )	// New HL2 behavior
				{
					m_hTarget = FindTarget( m_targetEntityName, NULL );
				}
				else	// HL1 style
				{
					m_hTarget = ToBasePlayer( GetContainingEntity( UTIL_FindClientInPVS( edict() ) ) );
				}

				if ( m_hTarget != NULL )
				{
					SetNextThink( gpGlobals->curtime );	// Think again immediately
				}
				else
				{
					if ( IsActive() )
					{
						SetNextThink( gpGlobals->curtime + 2 );	// Wait 2 secs
					}

					if ( m_fireLast !=0 )
					{
						m_OnLoseTarget.FireOutput(this, this);
						m_fireLast = 0;
					}
				}

				return;
			}
			pTarget = pEntity;

			// Calculate angle needed to aim at target
			worldTargetPosition = pEntity->EyePosition();
		}

		float range = (worldTargetPosition - barrelEnd).Length();
		
		if ( !InRange( range ) )
		{
			m_fireLast = 0;
			return;
		}

		UTIL_TraceLine( barrelEnd, worldTargetPosition, MASK_SHOT, this, COLLISION_GROUP_NONE, &tr );

		if (m_spawnflags & SF_TANK_AIM_AT_POS)
		{
			updateTime		= TRUE;
			m_sightOrigin	= m_vTargetPosition;
		}
		else
		{
			lineOfSight = FALSE;
			// No line of sight, don't track
			if ( tr.fraction == 1.0 || tr.m_pEnt == pTarget )
			{
				lineOfSight = TRUE;

				CBaseEntity *pInstance = pTarget;
				if ( InRange( range ) && pInstance && pInstance->IsAlive() )
				{
					updateTime = TRUE;

					// Sight position is BodyTarget with no noise (so gun doesn't bob up and down)
					m_sightOrigin = pInstance->BodyTarget( GetLocalOrigin(), false );
				}
			}
		}

		// Convert targetPosition to parent
		angles = AimBarrelAt( m_parentMatrix.WorldToLocal( m_sightOrigin ) );
	}

	// Force the angles to be relative to the center position
	float offsetY = UTIL_AngleDistance( angles.y, m_yawCenter );
	float offsetX = UTIL_AngleDistance( angles.x, m_pitchCenter );
	angles.y = m_yawCenter + offsetY;
	angles.x = m_pitchCenter + offsetX;

	// Limit against range in y

	// MDB - don't check pitch! If two func_tanks are meant to align,
	// and one can pitch and the other cannot, this can lead to them getting 
	// different values for angles.y. Nothing is lost by not updating yaw
	// because the target is not in pitch range.

	bool bOutsideYawRange = ( fabs( offsetY ) > m_yawRange + m_yawTolerance );
	bool bOutsidePitchRange = ( fabs( offsetX ) > m_pitchRange + m_pitchTolerance );

	Vector vecToTarget = m_sightOrigin - GetLocalOrigin();

	// if target is outside yaw range
	if ( bOutsideYawRange )
	{
		if ( angles.y > m_yawCenter + m_yawRange )
		{
			angles.y = m_yawCenter + m_yawRange;
		}
		else if ( angles.y < (m_yawCenter - m_yawRange) )
		{
			angles.y = (m_yawCenter - m_yawRange);
		}
	}

	if ( bOutsidePitchRange || bOutsideYawRange || ( vecToTarget.Length() < ( barrelEnd - GetAbsOrigin() ).Length() ) )
	{
		// Don't update if you saw the player, but out of range
		updateTime = false;
	}

	if ( updateTime )
	{
		m_lastSightTime = gpGlobals->curtime;
		m_persist2burst = 0;
	}

	// Move toward target at rate or less
	float distY = UTIL_AngleDistance( angles.y, GetLocalAngles().y );

	QAngle vecAngVel = GetLocalAngularVelocity();
	vecAngVel.y = distY * 10;
	vecAngVel.y = clamp( vecAngVel.y, -m_yawRate, m_yawRate );

	// Limit against range in x
	angles.x = clamp( angles.x, m_pitchCenter - m_pitchRange, m_pitchCenter + m_pitchRange );

	// Move toward target at rate or less
	float distX = UTIL_AngleDistance( angles.x, GetLocalAngles().x );
	vecAngVel.x = distX  * 10;
	vecAngVel.x = clamp( vecAngVel.x, -m_pitchRate, m_pitchRate );
	SetLocalAngularVelocity( vecAngVel );

	SetMoveDoneTime( 0.1 );
	if ( m_pController )
		return;

	if ( CanFire() && ( (fabs(distX) < m_pitchTolerance && fabs(distY) < m_yawTolerance) || (m_spawnflags & SF_TANK_LINEOFSIGHT) ) )
	{
		bool fire = FALSE;
		Vector forward;
		AngleVectors( GetLocalAngles(), &forward );
		forward = m_parentMatrix.ApplyRotation( forward );


		if ( m_spawnflags & SF_TANK_LINEOFSIGHT )
		{
			float length = (m_maxRange > 0) ? m_maxRange : MAX_TRACE_LENGTH;
			UTIL_TraceLine( barrelEnd, barrelEnd + forward * length, MASK_SHOT, this, COLLISION_GROUP_NONE, &tr );

			if ( tr.m_pEnt == pTarget )
				fire = TRUE;
		}
		else
			fire = TRUE;

		if ( fire )
		{
			if (m_fireLast == 0)
			{
				m_OnAquireTarget.FireOutput(this, this);
			}
			FiringSequence( barrelEnd, forward, this );
		}
		else 
		{
			if (m_fireLast !=0)
			{
				m_OnLoseTarget.FireOutput(this, this);
			}
			m_fireLast = 0;
		}
	}
	else 
	{
		if (m_fireLast !=0)
		{
			m_OnLoseTarget.FireOutput(this, this);
		}
		m_fireLast = 0;
	}
}