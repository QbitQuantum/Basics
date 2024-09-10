// ----------------------------------------------------------------------- //
//
//	ROUTINE:	CTronPlayerObj::GetDefensePercentage()
//
//	PURPOSE:	How much of the attack damage has our defenese prevented
//
//	NOTES:		There are actually 2 defense percentages.  One is based
//				on timing, i.e. player's reation speed, animation speed,
//				etc.  The other is based on the player's orientation to
//				the incoming projectile.  If the vector parameter is
//				specified, BOTH percentages will be computed and the
//				combined result will be returned.  If the vector is NOT
//				specified, only the timing will be computed.
//
// ----------------------------------------------------------------------- //
float CTronPlayerObj::GetDefensePercentage( LTVector const *pIncomingProjectilePosition /*=0*/) const
{
	if ( TRONPLAYEROBJ_NO_DEFEND == m_cDefendType )
	{
		// not blocking
		return 0.0f;
	}

	//
	// Do this in 2 passes.  The first pass willl determine
	// the contribution to the defense percentage due to the
	// timing of the player/animations.  The second pass
	// will add the contribution of the player's orientation.
	//
	float fDefenseTimingPercentage;
	float fDefenseOrientationPercentage;

	// get the weapon
	AMMO const *pAmmoData = g_pWeaponMgr->GetAmmo( m_cDefendAmmoId );
	ASSERT( 0 != pAmmoData );
	ASSERT( 0 != pAmmoData->pProjectileFX );

	// get the ammo specific data
	DISCCLASSDATA *pDiscData =
		dynamic_cast< DISCCLASSDATA* >(
			pAmmoData->pProjectileFX->pClassData
		);
	ASSERT( 0 != pDiscData );


	//
	// Determine Timing Percentage
	//

	switch ( m_cDefendType )
	{
		case MPROJ_START_SWAT_BLOCK:
		case MPROJ_START_ARM_BLOCK:
		{
			// get the current server time
			float fCurrentServerTime = g_pLTServer->GetTime() * 1000.0f;

			// make sure we're within the range of the block
			if ( ( static_cast< int >( fCurrentServerTime ) -
			       m_nDefendServerTimeStarted ) > m_nDefendDuration )
			{
				// nope, the block is over
				return 0.0f;
			}

			// Swat and Arm defenses are similar, so fill out these
			// variables uniquely (depending on which case we are
			// handling), then use the common generic math to figure
			// out the answer.
			float fMidpointTime;
			float fMaxStartTime;
			float fMaxEndTime;
			float fStartDefendPercentage;
			float fMaxDefendPercentage;
			float fEndDefendPercentage;

			if ( MPROJ_START_SWAT_BLOCK == m_cDefendType )
			{
				// determine at exactly what time the midpoint takes place
				// NOTE: this is relative time, not absolute
				fMidpointTime = 
					( pDiscData->fSwatDefendMidpoint * m_nDefendDuration );

				// determine at exactly what time the max starts
				// NOTE: this is relative time, not absolute
				fMaxStartTime =
					fMidpointTime - 
					fMidpointTime * pDiscData->fSwatDefendStartMaxDefendPercentage;

				// determine at exactly what time the max ends
				// NOTE: this is relative time, not absolute
				fMaxEndTime =
					fMidpointTime +
					(
						( m_nDefendDuration - fMidpointTime ) *
						pDiscData->fSwatDefendEndMaxDefendPercentage
					);

				// determine the starting defend percentage
				fStartDefendPercentage = pDiscData->fSwatDefendStartDefendPercentage;

				// detecmine the max defend percentage					
				fMaxDefendPercentage = pDiscData->fSwatDefendMaxDefendPercentage;

				// determine the ending defend percentage
				fEndDefendPercentage = pDiscData->fSwatDefendEndDefendPercentage;
			}
			else if ( MPROJ_START_ARM_BLOCK == m_cDefendType )
			{
				// Not implemented yet.  The main question I haven't figured
				// out yet is where does the information come from?
				fMidpointTime = 0.0f;
				fMaxStartTime = 0.0f;
				fMaxEndTime = 0.0f;
				fStartDefendPercentage = 0.0f;
				fMaxDefendPercentage = 0.0f;
				fEndDefendPercentage = 0.0f;
			}

			// determine at exactly how much time we've been in the block
			// NOTE: this is relative time, not absolute
			float fBlockTime = 
				fCurrentServerTime - m_nDefendServerTimeStarted;

			if ( ( -MATH_EPSILON <= fBlockTime ) && 
			     ( fBlockTime <= fMaxStartTime ) )
			{
				// somewhere on the uprise
				fDefenseTimingPercentage =
					fStartDefendPercentage + 
						(
							(
								( 
									fMaxDefendPercentage -
									fStartDefendPercentage
								) /
								fMaxStartTime 
							) * 
							fBlockTime
						);
			}
			else if ( ( fMaxStartTime < fBlockTime ) &&
			          ( fBlockTime <= fMaxEndTime ) )
			{
				// within the max range
				fDefenseTimingPercentage = fMaxDefendPercentage;
			}
			else if ( ( fMaxEndTime < fBlockTime ) &&
			          ( fBlockTime <= m_nDefendDuration ) )
			{
				// somewhere on the downfall
				fDefenseTimingPercentage =
					fMaxDefendPercentage - 
						(
							(
								( 
									fMaxDefendPercentage -
									fEndDefendPercentage
								) /
								( m_nDefendDuration - fMaxEndTime )
							) * 
							( fBlockTime - fMaxEndTime )
						);
			}
			else
			{
				// math problem, we should be here if we are outside
				// the bounds of the defense
				ASSERT( 0 );
				fDefenseTimingPercentage = 0.0f;
			}
		}
		break;


		case MPROJ_START_HOLD_BLOCK:
		{
			// get the current server time
			float fCurrentServerTime = g_pLTServer->GetTime() * 1000.0f;

			// determine the starting defend percentage
			float fStartDefendPercentage = pDiscData->fHoldDefendStartDefendPercentage;

			// determine the max defend percentage					
			float fMaxDefendPercentage = pDiscData->fHoldDefendMaxDefendPercentage;

			// determine at exactly how much time we've been in the block
			// NOTE: this is relative time, not absolute
			float fBlockTime = 
				fCurrentServerTime - m_nDefendServerTimeStarted;

			if ( ( -MATH_EPSILON <= fBlockTime ) && 
			     ( fBlockTime <= m_nDefendDuration ) )
			{
				// somewhere on the uprise
				fDefenseTimingPercentage =
					fStartDefendPercentage + 
						(
							(
								( 
									fMaxDefendPercentage -
									fStartDefendPercentage
								) /
								static_cast< float >( m_nDefendDuration )
							) * 
							fBlockTime
						);
			}
			else if ( m_nDefendDuration < fBlockTime )
			{
				// within the max range
				fDefenseTimingPercentage = fMaxDefendPercentage;
			}
			else
			{
				// math problem, we should be here if we are outside
				// the bounds of the defense
				ASSERT( 0 );
				fDefenseTimingPercentage = 0.0f;
			}
		}
		break;

		case MPROJ_END_HOLD_BLOCK:
		{
			// get the current server time
			float fCurrentServerTime = g_pLTServer->GetTime() * 1000.0f;

			// make sure we're within the range of the block
			if ( ( static_cast< int >( fCurrentServerTime ) -
			       m_nDefendServerTimeStarted ) > m_nDefendDuration )
			{
				// nope, the block is over
				return 0.0f;
			}

			// detecmine the max defend percentage					
			float fMaxDefendPercentage = pDiscData->fHoldDefendMaxDefendPercentage;

			// determine the ending defend percentage
			float fEndDefendPercentage = pDiscData->fHoldDefendEndDefendPercentage;

			// determine at exactly how much time we've been in the block
			// NOTE: this is relative time, not absolute
			float fBlockTime = 
				fCurrentServerTime - m_nDefendServerTimeStarted;

			// somewhere on the downfall
			fDefenseTimingPercentage =
				fMaxDefendPercentage - 
					(
						(
							( 
								fMaxDefendPercentage -
								fEndDefendPercentage
							) /
							( m_nDefendDuration )
						) * 
						( fBlockTime )
					);
		}
		break;

		default:
		{
			// There is some type of block defined that we
			// are not handling, and we SHOULD be handling it.
			ASSERT( 0 );

			return 0.0f;
		}
		break;
	};


	//TODO: skip this section of the camera position is too old?

	// check if the oriention percentage should be computed
	if ( 0 == pIncomingProjectilePosition )
	{
		// No vector specifed, there is no way
		// to compute orientation defense.
		return fDefenseTimingPercentage;
	}

	//
	// Determine Orientation percentage
	//

	// The 3 cases are the same, but they could have different
	// control values.  Figure out what the specific variables
	// are (depending on the specific type of block), then apply
	// the generic equations.

	float fOrientationMinDefendPercentage;
	float fOrientationMaxDefendPercentage;
	float fOrientationDeadZone;
	float fOrientationMaxZone;

	switch ( m_cDefendType )
	{
		case MPROJ_START_SWAT_BLOCK:
		{
			fOrientationMinDefendPercentage  = pDiscData->fSwatDefendOrientationMinDefendPercentage;
			fOrientationMaxDefendPercentage  = pDiscData->fSwatDefendOrientationMaxDefendPercentage;
			fOrientationDeadZone             = MATH_PI - pDiscData->fSwatDefendOrientationDeadZone;
			fOrientationMaxZone              = pDiscData->fSwatDefendOrientationMaxZone;
		}
		break;

		case MPROJ_START_HOLD_BLOCK:
		case MPROJ_END_HOLD_BLOCK:
		{
			fOrientationMinDefendPercentage  = pDiscData->fHoldDefendOrientationMinDefendPercentage;
			fOrientationMaxDefendPercentage  = pDiscData->fHoldDefendOrientationMaxDefendPercentage;
			fOrientationDeadZone             = MATH_PI - pDiscData->fHoldDefendOrientationDeadZone;
			fOrientationMaxZone              = pDiscData->fHoldDefendOrientationMaxZone;
		}
		break;

		case MPROJ_START_ARM_BLOCK:
		{
			// Not implemented yet.  The main question I haven't figured
			// out yet is where does the information come from?
			fOrientationMinDefendPercentage  = 0.0f;
			fOrientationMaxDefendPercentage  = 0.0f;
			fOrientationDeadZone             = 0.0f;
			fOrientationMaxZone              = 0.0f;
		}
		break;

		default:
		{
			// There is some type of block defined that we
			// are not handling, and we SHOULD be handling it.
			ASSERT( 0 );

			return 0.0f;
		}
		break;
	};

	LTRESULT ltResult;
	LTVector vDefendPos;
	LTVector vDefendPosToProjectile;

	// get the player's position
	ltResult = g_pLTServer->GetObjectPos( m_hObject, &vDefendPos );
	ASSERT( LT_OK == ltResult );

	// REMOVE THIS CODE FOR FINAL RELEASE, BUT LEAVE FOR TESTING MULTIPLAYER
	// print a warning if the time is new enough
	if ( TRONPLAYEROBJ_CLIENT_CAMERA_TIME_OLD_THRESHOLD < ( g_pLTServer->GetTime() - m_nClientCameraOffsetTimeReceivedMS ) )
	{
		g_pLTServer->CPrint( "Client Camera Offset time is low, possible lag\n" );
		g_pLTServer->CPrint( "   condition that will affect defensive accuracy.\n" );
		g_pLTServer->CPrint( "   Currnt value is %5.3f units old.\n", ( g_pLTServer->GetTime() - m_nClientCameraOffsetTimeReceivedMS ) );

	}
	
	// add the camera offset vDefendPos += m_vClientCameraOffset;

	// find a unit vector from us to the projectile
	vDefendPosToProjectile  = *pIncomingProjectilePosition -
	                         ( m_vClientCameraOffset +
	                           vDefendPos );
	vDefendPosToProjectile.y = 0;
	vDefendPosToProjectile.Normalize();

	// determine a forward vector reprensenting the direction the
	// player is facing
	LTRotation vPlayerViewOrientation;
	ltResult = g_pLTServer->GetObjectRotation( m_hObject, &vPlayerViewOrientation );
	ASSERT( LT_OK == ltResult );

	LTVector vPlayerViewForward = vPlayerViewOrientation.Forward();
	vPlayerViewForward.y = 0;
	vPlayerViewForward.Normalize();

	float fDotProd = vPlayerViewForward.Dot( vDefendPosToProjectile );

	// find the angle between the two vectors
	float fDefenseAngle = ltacosf( vPlayerViewForward.Dot( vDefendPosToProjectile ) );

	if ( ( MATH_EPSILON <= fDefenseAngle) && ( fDefenseAngle <= fOrientationMaxZone ) )
	{
		// it's within the max zone
		fDefenseOrientationPercentage = fOrientationMaxDefendPercentage;
	}
	else if ( ( fOrientationMaxZone < fDefenseAngle) && ( fDefenseAngle <= fOrientationDeadZone ) )
	{
		// it's within the dropoff range
		fDefenseOrientationPercentage = 
			fOrientationMaxDefendPercentage +
			( fDefenseAngle - fOrientationMaxZone ) *
				( fOrientationMinDefendPercentage - fOrientationMaxDefendPercentage ) /
				( fOrientationDeadZone - fOrientationMaxZone );
	}
	else if ( fOrientationDeadZone <= fDefenseAngle)
	{
		// it's within the dead zone
		fDefenseOrientationPercentage = 0.0f;
	}

	//
	// Final Defense Result
	//

	float fFinalDefensePercentage = fDefenseTimingPercentage -
	                                fDefenseOrientationPercentage;
	return fFinalDefensePercentage;
}