//=========================================================
// HandleAnimEvent - catches the monster-specific messages
// that occur when tagged animation frames are played.
//=========================================================
void CNPC_Houndeye::HandleAnimEvent( animevent_t *pEvent )
{
	switch ( pEvent->event )
	{
		case HOUND_AE_WARN:
			// do stuff for this event.
			WarnSound();
			break;

		case HOUND_AE_STARTATTACK:
			WarmUpSound();
			break;

		case HOUND_AE_HOPBACK:
			{
				float flGravity = sv_gravity.GetFloat();

				SetGroundEntity( NULL );

				Vector forward;
				AngleVectors( GetLocalAngles(), &forward );
				Vector vecNewVelocity = forward * -200;
				//jump up 36 inches
				vecNewVelocity.z += sqrt( 2 * flGravity * 36 );
				SetAbsVelocity( vecNewVelocity );
				break;
			}

		case HOUND_AE_THUMP:
			// emit the shockwaves
			SonicAttack();
			m_flNextAttack = gpGlobals->curtime + random->RandomFloat( 5.0, 8.0 );
			break;

		case HOUND_AE_ANGERSOUND1:
			{
				EmitSound( "NPC_Houndeye.Anger1" );
			}
			break;

		case HOUND_AE_ANGERSOUND2:
			{
			EmitSound( "NPC_Houndeye.Anger2" );
			}
			break;

		case HOUND_AE_CLOSE_EYE:
			if ( !m_fDontBlink )
			{
			//<<TEMP>>	pev->skin = HOUNDEYE_EYE_FRAMES - 1;
			}
			break;

		case HOUND_AE_LEAP_HIT:
			{
				//<<TEMP>>return;//<<TEMP>>
				SetGroundEntity( NULL );

				//
				// Take him off ground so engine doesn't instantly reset FL_ONGROUND.
				//
				UTIL_SetOrigin( this, GetLocalOrigin() + Vector( 0 , 0 , 1 ));
				Vector vecJumpDir;
				if ( GetEnemy() != NULL )
				{
					Vector vecEnemyEyePos = GetEnemy()->EyePosition();

					float gravity = sv_gravity.GetFloat();
					if ( gravity <= 1 )
					{
						gravity = 1;
					}

					//
					// How fast does the houndeye need to travel to reach my enemy's eyes given gravity?
					//
					float height = ( vecEnemyEyePos.z - GetAbsOrigin().z );
					if ( height < 16 )
					{
						height = 16;
					}
					else if ( height > 120 )
					{
						height = 120;
					}
					float speed = sqrt( 2 * gravity * height );
					float time = speed / gravity;

					//
					// Scale the sideways velocity to get there at the right time
					//
					vecJumpDir = vecEnemyEyePos - GetAbsOrigin();
					vecJumpDir = vecJumpDir / time;

					//
					// Speed to offset gravity at the desired height.
					//
					vecJumpDir.z = speed;

					//
					// Don't jump too far/fast.
					//
					float distance = vecJumpDir.Length();
					if ( distance > 650 )
					{
						vecJumpDir = vecJumpDir * ( 650.0 / distance );
					}
				}
				else
				{
					Vector forward, up;
					AngleVectors( GetLocalAngles(), &forward, NULL, &up );
					//
					// Jump hop, don't care where.
					//
					vecJumpDir = Vector( forward.x, forward.y, up.z ) * 350;
				}

				SetAbsVelocity( vecJumpDir );
				m_flNextAttack = gpGlobals->curtime + 2;
				break;
			}
		default:
			BaseClass::HandleAnimEvent( pEvent );
			break;
	}
}