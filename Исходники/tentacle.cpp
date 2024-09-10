//
// TentacleThink
//
void CTentacle :: Cycle( void )
{
	SetNextThink( 0.1 );

	// ALERT( at_console, "%s %d %d %d %f %f\n", STRING( pev->targetname ), pev->sequence, m_iGoalAnim, m_iDir, pev->framerate, pev->health );

	if (m_MonsterState == MONSTERSTATE_SCRIPT || m_IdealMonsterState == MONSTERSTATE_SCRIPT)
	{
		Vector angles = GetAbsAngles();
		angles.y = m_flInitialYaw;
		SetAbsAngles( angles );
		pev->ideal_yaw = m_flInitialYaw;	
		ClearConditions( IgnoreConditions() );
		MonsterThink( );
		m_iGoalAnim = TENTACLE_ANIM_Pit_Idle;
		return;
	}

	DispatchAnimEvents( );
	StudioFrameAdvance( );

	ChangeYaw( pev->yaw_speed );

	CSound *pSound;

	Listen( );

	// Listen will set this if there's something in my sound list
	if ( HasConditions( bits_COND_HEAR_SOUND ) )
		pSound = PBestSound();
	else
		pSound = NULL;

	if ( pSound )
	{
		Vector vecDir;
		if (gpGlobals->time - m_flPrevSoundTime < 0.5)
		{
			float dt = gpGlobals->time - m_flPrevSoundTime;
			vecDir = pSound->m_vecOrigin + (pSound->m_vecOrigin - m_vecPrevSound) / dt - GetAbsOrigin();
		}
		else
		{
			vecDir = pSound->m_vecOrigin - GetAbsOrigin();
		}
		m_flPrevSoundTime = gpGlobals->time;
		m_vecPrevSound = pSound->m_vecOrigin;

		m_flSoundYaw = UTIL_VecToYaw ( vecDir ) - m_flInitialYaw;
		m_iSoundLevel = Level( vecDir.z );

		if (m_flSoundYaw < -180)
			m_flSoundYaw += 360;
		if (m_flSoundYaw > 180)
			m_flSoundYaw -= 360;

		// ALERT( at_console, "sound %d %.0f\n", m_iSoundLevel, m_flSoundYaw );
		if (m_flSoundTime < gpGlobals->time)
		{
			// play "I hear new something" sound
			char *sound;	

			switch( RANDOM_LONG(0,1) )
			{
			case 0: sound = "tentacle/te_alert1.wav"; break;
			case 1: sound = "tentacle/te_alert2.wav"; break;
			}

			// UTIL_EmitAmbientSound(ENT(pev), GetAbsOrigin() + Vector( 0, 0, MyHeight()), sound, 1.0, ATTN_NORM, 0, 100);
		}
		m_flSoundTime = gpGlobals->time + RANDOM_FLOAT( 5.0, 10.0 );
	}

	// clip ideal_yaw
	float dy = m_flSoundYaw;
	switch( pev->sequence )
	{
	case TENTACLE_ANIM_Floor_Rear:
	case TENTACLE_ANIM_Floor_Rear_Idle:
	case TENTACLE_ANIM_Lev1_Rear:
	case TENTACLE_ANIM_Lev1_Rear_Idle:
	case TENTACLE_ANIM_Lev2_Rear:
	case TENTACLE_ANIM_Lev2_Rear_Idle:
	case TENTACLE_ANIM_Lev3_Rear:
	case TENTACLE_ANIM_Lev3_Rear_Idle:
		if (dy < 0 && dy > -m_flMaxYaw)
			dy = -m_flMaxYaw;
		if (dy > 0 && dy < m_flMaxYaw)
			dy = m_flMaxYaw;
		break;
	default:
		if (dy < -m_flMaxYaw)
			dy = -m_flMaxYaw;
		if (dy > m_flMaxYaw)
			dy = m_flMaxYaw;
	}
	pev->ideal_yaw = m_flInitialYaw + dy;

	if (m_fSequenceFinished)
	{
		// ALERT( at_console, "%s done %d %d\n", STRING( pev->targetname ), pev->sequence, m_iGoalAnim );
		if (pev->health <= 1)
		{
			m_iGoalAnim = TENTACLE_ANIM_Pit_Idle;
			if (pev->sequence == TENTACLE_ANIM_Pit_Idle)
			{
				pev->health = 75;
			}
		}
		else if ( m_flSoundTime > gpGlobals->time )
		{
			if (m_flSoundYaw >= -(m_flMaxYaw + 30) && m_flSoundYaw <= (m_flMaxYaw + 30))
			{
				// strike
				m_iGoalAnim = LookupActivity( ACT_T_STRIKE + m_iSoundLevel );
			}
			else if (m_flSoundYaw >= -m_flMaxYaw * 2 && m_flSoundYaw <= m_flMaxYaw * 2) 
			{
				// tap
				m_iGoalAnim = LookupActivity( ACT_T_TAP + m_iSoundLevel );
			}
			else
			{
				// go into rear idle
				m_iGoalAnim = LookupActivity( ACT_T_REARIDLE + m_iSoundLevel );
			}
		}
		else if (pev->sequence == TENTACLE_ANIM_Pit_Idle)
		{
			// stay in pit until hear noise
			m_iGoalAnim = TENTACLE_ANIM_Pit_Idle;
		}
		else if (pev->sequence == m_iGoalAnim)
		{
			if (MyLevel() >= 0 && gpGlobals->time < m_flSoundTime)
			{
				if (RANDOM_LONG(0,9) < m_flSoundTime - gpGlobals->time)
				{
					// continue stike
					m_iGoalAnim = LookupActivity( ACT_T_STRIKE + m_iSoundLevel );
				}
				else
				{
					// tap
					m_iGoalAnim = LookupActivity( ACT_T_TAP + m_iSoundLevel );
				}
			}
			else if (MyLevel( ) < 0)
			{
				m_iGoalAnim = LookupActivity( ACT_T_IDLE + 0 );
			}
			else
			{
				if (m_flNextSong < gpGlobals->time)
				{
					// play "I hear new something" sound
					char *sound;	

					switch( RANDOM_LONG(0,1) )
					{
					case 0: sound = "tentacle/te_sing1.wav"; break;
					case 1: sound = "tentacle/te_sing2.wav"; break;
					}

					EMIT_SOUND(ENT(pev), CHAN_VOICE, sound, 1.0, ATTN_NORM);

					m_flNextSong = gpGlobals->time + RANDOM_FLOAT( 10, 20 );
				}

				if (RANDOM_LONG(0,15) == 0)
				{
					// idle on new level
					m_iGoalAnim = LookupActivity( ACT_T_IDLE + RANDOM_LONG(0,3) );
				}
				else if (RANDOM_LONG(0,3)  == 0)
				{
					// tap
					m_iGoalAnim = LookupActivity( ACT_T_TAP + MyLevel( ) );
				}
				else
				{
					// idle
					m_iGoalAnim = LookupActivity( ACT_T_IDLE + MyLevel( ) );
				}
			}
			if (m_flSoundYaw < 0)
				m_flSoundYaw += RANDOM_FLOAT( 2, 8 );
			else
				m_flSoundYaw -= RANDOM_FLOAT( 2, 8 );
		}

		pev->sequence = FindTransition( pev->sequence, m_iGoalAnim, &m_iDir );

		if (m_iDir > 0)
		{
			pev->frame = 0;
		}
		else
		{
			m_iDir = -1; // just to safe
			pev->frame = 255;
		}
		ResetSequenceInfo( );

		m_flFramerateAdj = RANDOM_FLOAT( -0.2, 0.2 );
		pev->framerate = m_iDir * 1.0 + m_flFramerateAdj;

		switch( pev->sequence)
		{
		case TENTACLE_ANIM_Floor_Tap:
		case TENTACLE_ANIM_Lev1_Tap:
		case TENTACLE_ANIM_Lev2_Tap:
		case TENTACLE_ANIM_Lev3_Tap:
			{
				Vector vecSrc;
				UTIL_MakeVectors( GetAbsAngles() );

				TraceResult tr1, tr2;

				vecSrc = GetAbsOrigin() + Vector( 0, 0, MyHeight() - 4);
				UTIL_TraceLine( vecSrc, vecSrc + gpGlobals->v_forward * 512, ignore_monsters, ENT( pev ), &tr1 );

				vecSrc = GetAbsOrigin() + Vector( 0, 0, MyHeight() + 8);
				UTIL_TraceLine( vecSrc, vecSrc + gpGlobals->v_forward * 512, ignore_monsters, ENT( pev ), &tr2 );

				// ALERT( at_console, "%f %f\n", tr1.flFraction * 512, tr2.flFraction * 512 );

				m_flTapRadius = SetBlending( 0, RANDOM_FLOAT( tr1.flFraction * 512, tr2.flFraction * 512 ) );
			}
			break;
		default:
			m_flTapRadius = 336; // 400 - 64
			break;
		}
		pev->view_ofs.z = MyHeight( );
		// ALERT( at_console, "seq %d\n", pev->sequence );
	}

	if (m_flPrevSoundTime + 2.0 > gpGlobals->time)
	{
		// 1.5 normal speed if hears sounds
		pev->framerate = m_iDir * 1.5 + m_flFramerateAdj;
	}
	else if (m_flPrevSoundTime + 5.0 > gpGlobals->time)
	{
		// slowdown to normal
		pev->framerate = m_iDir + m_iDir * (5 - (gpGlobals->time - m_flPrevSoundTime)) / 2 + m_flFramerateAdj;
	}
}