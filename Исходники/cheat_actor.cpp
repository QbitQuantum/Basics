void cheat_handle_actor_fly ( struct actor_info *ainfo, double time_diff )
{
	traceLastFunc( "cheat_handle_actor_fly()" );

	// toggle
	if ( KEY_PRESSED(set.key_fly_player) )
	{
		if ( !cheat_state->actor.fly_on )
		{
			cheat_state->actor.fly_on = 1;
		}
		else 
		{
			cheat_state->actor.fly_on = 0;
		}
	}

	if ( cheat_state->actor.fly_on )
	{

		// set fly status
		cheat_state->actor.fly_enabled = true;

		// get ground Z height
		float groundZHeight = pGame->GetWorld()->FindGroundZFor3DPosition(pPedSelf->GetPosition());
		float playerZHeight = pPedSelf->GetPosition()->fZ;
		float playerFrontZOffset = abs(pPedSelfSA->Placeable.matrix->vFront.fZ);
		float playerRightZOffset = abs(pPedSelfSA->Placeable.matrix->vRight.fZ);

		// standing detection
		if ( cheat_state->actor.fly_active
				&& ainfo->pedFlags.bIsStanding
			|| !KEY_DOWN(set.key_fly_player_strafeUp)
				&& cheat_state->actor.fly_active
				&& groundZHeight + 1.4f > playerZHeight
				&& groundZHeight - 1.4f < playerZHeight)
		{
			cheat_state->actor.fly_active = false;
			playerFly_lastKeySpeedState = speed_none;

			// remove up speed hard limiter patch
			if (patch_RemoveFlyUpSpeedLimit.installed)
			{
				patcher_remove(&patch_RemoveFlyUpSpeedLimit);
			}
			// remove fly soft limiters patch
			if (patch_RemoveFlyWindSpeedLimit.installed)
			{
				patcher_remove(&patch_RemoveFlyWindSpeedLimit);
			}

			// set gravity down
			pPedSelf->SetGravity( &-g_vecUpNormal );

			// copy camera rotation to player
			ainfo->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
			ainfo->fTargetRotation = ainfo->fCurrentRotation;
			// play landing animation
			playerFly_lastAnimationStates = SHP_Jump_Land;
			GTAfunc_PerformAnimation("SHOP", "SHP_Jump_Land ", -1, 0, 1, 0, 0, 0, 0, 0);

			// correct for angle after landing if needed
			if (playerFrontZOffset > 0.4f
				|| playerRightZOffset > 0.3f)
			{
				// get player matrix
				CMatrix matPed;
				pPedSelf->GetMatrix(&matPed);

				// tilt player upright
				CVector rotationAxis = g_vecUpNormal;
				rotationAxis.CrossProduct( &matPed.vUp );
				float theta = ( matPed.vUp.DotProduct( &g_vecUpNormal ) );
				if ( !near_zero(theta) )
				{
					matPed = matPed.Rotate( &rotationAxis, cos(theta) );
					// normalize everything
					matPed.vFront.Normalize();
					matPed.vRight.Normalize();
					matPed.vUp.Normalize();
					// zero near zero
					matPed.vFront.ZeroNearZero();
					matPed.vRight.ZeroNearZero();
					matPed.vUp.ZeroNearZero();
					// set player matrix
					pPedSelf->SetMatrix(&matPed);
				}
			}
		}
		else if ( ainfo->pedFlags.bIsStanding
			|| !KEY_DOWN(set.key_fly_player_strafeUp)
				&& groundZHeight + 1.6f > playerZHeight
				&& groundZHeight - 1.6f < playerZHeight )
		{
			// still standing

			// update the last matrix
			pPedSelf->GetMatrix(&playerFly_lastPedRotation);
		}
		else if ( time_diff < 1.0f ) // I believe I can fly...
		{

// keys/buttons input

			playerFly_keySpeedStates keySpeedState;
			if ( KEY_DOWN(set.key_fly_player_accelerate) )
			{
				keySpeedState = speed_accelerate;
			}
			else if ( KEY_DOWN(set.key_fly_player_decelerate) )
			{
				keySpeedState = speed_decelerate;
			}
			else
			{
				keySpeedState = speed_none;
			}
			playerFly_keyStrafeStates keyStrafeState;
			if ( KEY_DOWN(set.key_fly_player_strafeLeft) && !KEY_DOWN(set.key_fly_player_strafeRight) )
			{
				keyStrafeState = strafe_left;
				playerFly_animationStrafeStateTimer = GetTickCount();
			}
			else if ( KEY_DOWN(set.key_fly_player_strafeRight) && !KEY_DOWN(set.key_fly_player_strafeLeft) )
			{
				keyStrafeState = strafe_right;
				playerFly_animationStrafeStateTimer = GetTickCount();
			}
			else if ( KEY_DOWN(set.key_fly_player_strafeUp) )
			{
				keyStrafeState = strafe_up;
				playerFly_animationStrafeStateTimer = GetTickCount();
			}
			else
			{
				keyStrafeState = strafe_none;
			}

			// activate fly mode
			if ( !cheat_state->actor.fly_active )
			{
				cheat_state->actor.fly_active = true;
				// install up speed hard limiter patch
				if (!patch_RemoveFlyUpSpeedLimit.installed)
				{
					patcher_install(&patch_RemoveFlyUpSpeedLimit);
				}
				// install fly soft limiters patch
				if (!patch_RemoveFlyWindSpeedLimit.installed)
				{
					patcher_install(&patch_RemoveFlyWindSpeedLimit);
				}
				if ( keySpeedState == speed_none )
				{
					// start fly animation
					GTAfunc_PerformAnimation("SWIM", "Swim_Tread", -1, 1, 1, 0, 0, 0, 1, 0);
					playerFly_lastAnimationStates = anim_Swim_Tread;
				}
			}

// init variables

			// setup variables used through this function
			CVector vecSpeed, rotationAxis;
			float theta, thetaBase, rotationMultiplier;
			pPedSelf->GetMoveSpeed(&vecSpeed);
			float speed = vecSpeed.Length();

			// copy camera rotation to player
			// this doesn't seem to be needed anymore
			//ainfo->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();

			// get camera matrix
			CMatrix matCamera;
			pGame->GetCamera()->GetMatrix(&matCamera);
			matCamera.vRight = -matCamera.vRight; // for some reason this is inverted
			// normalize camera
			matCamera.vFront.Normalize();
			matCamera.vRight.Normalize();
			matCamera.vUp.Normalize();

// change animation

			if ( playerFly_lastKeyStrafeStates != keyStrafeState
				|| playerFly_lastKeySpeedState != keySpeedState )
			{
				playerFly_lastKeyStrafeStates = keyStrafeState;
				playerFly_lastKeySpeedState = keySpeedState;
				playerFly_animationDeceleration = false;
				switch ( keySpeedState )
				{
				case speed_none:
					{
						if (playerFly_lastAnimationStates != anim_Swim_Breast)
						{
							playerFly_lastAnimationStates = anim_Swim_Breast;
							GTAfunc_PerformAnimation("SWIM", "Swim_Breast", -1, 1, 1, 0, 0, 0, 1, 0);
						}
						break;
					}
				case speed_accelerate:
					{
						if (playerFly_lastAnimationStates != anim_FALL_skyDive_accel)
						{
							playerFly_lastAnimationStates = anim_FALL_skyDive_accel;
							GTAfunc_PerformAnimation("PARACHUTE", "FALL_skyDive_accel", -1, 1, 1, 0, 0, 0, 1, 0);
						}
						break;
					}
				case speed_decelerate:
					{
						switch ( keyStrafeState )
						{
						case strafe_none:
						case strafe_up:
						case strafe_left:
						case strafe_right:
							{
								if ( speed > 0.45f )
								{
									if (playerFly_lastAnimationStates != anim_FALL_skyDive)
									{
										playerFly_lastAnimationStates = anim_FALL_skyDive;
										GTAfunc_PerformAnimation("PARACHUTE", "FALL_skyDive", -1, 1, 1, 0, 0, 0, 1, 0);
									}
									playerFly_animationDeceleration = true;
								}
								else if (playerFly_lastAnimationStates != anim_Swim_Tread)
								{
									playerFly_lastAnimationStates = anim_Swim_Tread;
									GTAfunc_PerformAnimation("SWIM", "Swim_Tread", -1, 1, 1, 0, 0, 0, 1, 0);
								}
							}
							break;
						default:
							{
								if (playerFly_lastAnimationStates != anim_Swim_Tread)
								{
									playerFly_lastAnimationStates = anim_Swim_Tread;
									GTAfunc_PerformAnimation("SWIM", "Swim_Tread", -1, 1, 1, 0, 0, 0, 1, 0);
								}
								break;
							}
						}
						break;
					}
				}
				playerFly_animationKeyStateSpeedDownChanged = false;
			}
			else if (!playerFly_animationKeyStateSpeedDownChanged)
			{
				switch ( keySpeedState )
				{
				case speed_decelerate:
					{
						if ( speed < 0.45f )
						{
							if (playerFly_lastAnimationStates != anim_Swim_Tread)
							{
								playerFly_lastAnimationStates = anim_Swim_Tread;
								GTAfunc_PerformAnimation("SWIM", "Swim_Tread", -1, 1, 1, 0, 0, 0, 1, 0);
							}
							playerFly_animationDeceleration = false;
							playerFly_animationKeyStateSpeedDownChanged = true;
						}
						break;
					}
				default:
					break;
				}
			}

// acceleration/deceleration

			// acceleration
			float fly_speed_max;
			float fly_acceleration;
			float fly_speed = set.fly_player_speed;
			float fly_acceleration_multiplier = set.fly_player_accel_multiplier;
			float fly_deceleration_multiplier = set.fly_player_decel_multiplier;
			switch ( keySpeedState )
			{
			case speed_accelerate:
				{
					if (fly_speed >= 1.0f)
					{
						fly_speed_max = 1.333f * (1.0f + (0.5f / fly_speed)) * fly_speed;
						fly_acceleration = time_diff * ((0.5f + (0.25f / (fly_speed / 4.0f))) * fly_speed) * fly_acceleration_multiplier;
					}
					else
					{
						fly_speed_max = 1.333f * (1.0f + (0.5f * fly_speed)) * fly_speed;
						fly_acceleration = time_diff * ((0.5f + fly_speed) * fly_speed) * fly_acceleration_multiplier;
					}

					if ( vecSpeed.Length() < fly_speed_max )
					{
						vecSpeed += matCamera.vFront * fly_acceleration;
					}

					// don't have NearZero speeds
					if ( !vecSpeed.IsNearZero() )
					{
						// set speed vector
						ainfo->m_SpeedVec = vecSpeed;
					}

				}
				break;
			case speed_none:
				{
					if (fly_speed >= 1.0f)
					{
						fly_speed_max = 0.1f;
						fly_acceleration = time_diff * 0.3f;
					}
					else
					{
						fly_speed_max = 0.1f * fly_speed;
						fly_acceleration = time_diff * (0.3f * fly_speed);
					}

					if ( vecSpeed.Length() < fly_speed_max )
					{
						vecSpeed += matCamera.vFront * fly_acceleration;
					}

					// calculate wind resistance
					float windResistance;
					float windSpeedDivisor = 1.5f;
					if (fly_speed >= windSpeedDivisor)
					{
						windResistance = time_diff * ( ( (fly_speed * 0.023f) + (speed * (fly_speed / (fly_speed / windSpeedDivisor)) * 0.38f) ) / (fly_speed / windSpeedDivisor) );
					}
					else if (fly_speed >= 1.0f)
					{
						windResistance = time_diff * ( ( (fly_speed * 0.023f) + (speed * (fly_speed / (fly_speed / windSpeedDivisor)) * 0.38f) ) * (fly_speed / windSpeedDivisor) );
					}
					else
					{
						windResistance = time_diff * ( ( (fly_speed * 0.023f) + (speed * 0.38f) ) * fly_speed );
					}
					vecSpeed -= vecSpeed * windResistance;

					// don't have NearZero speeds
					if ( !vecSpeed.IsNearZero() )
					{
						// set speed vector
						ainfo->m_SpeedVec = vecSpeed;
					}
				}
				break;
			case speed_decelerate:
				{
					// this bit should be converted to mta-style code
					vect3_normalize( ainfo->speed, ainfo->speed );

					speed -= time_diff * ((0.1f + speed) * (0.45f / (fly_speed / 2.0f)) * fly_speed) * fly_deceleration_multiplier;

					if ( speed < 0.0f )
						speed = 0.0f;

					if ( vect3_near_zero(ainfo->speed) )
					{
						vect3_zero( ainfo->speed );
					}
					else
					{
						vect3_mult( ainfo->speed, speed, ainfo->speed );
					}
				}
				break;
			}

// set speed target

			// calculate the desired speed target
			CVector vecSpeedRotate = matCamera.vFront;

			switch ( keyStrafeState )
			{
			case strafe_up:
				{
					vecSpeedRotate = matCamera.vUp;
				}
				break;
			case strafe_left:
				{
					CMatrix matTargetRotate;
					// rotate sideways
					matTargetRotate.vFront = vecSpeedRotate;
					rotationAxis = matCamera.vUp;
					theta = -1.57;
					matTargetRotate = matTargetRotate.Rotate( &rotationAxis, theta );
					// rotate upward
					rotationAxis = matCamera.vFront;
					if (KEY_DOWN(set.key_fly_player_strafeUp))
					{
						theta = -0.785;
					}
					else
					{
						theta = -0.05;
					}
					matTargetRotate = matTargetRotate.Rotate( &rotationAxis, theta );
					// set the rotation target
					vecSpeedRotate = matTargetRotate.vFront;
					vecSpeedRotate.Normalize();
				}
				break;
			case strafe_right:
				{
					CMatrix matTargetRotate;
					// rotate sideways
					matTargetRotate.vFront = vecSpeedRotate;
					rotationAxis = matCamera.vUp;
					theta = 1.57;
					matTargetRotate = matTargetRotate.Rotate( &rotationAxis, theta );
					// rotate upward
					rotationAxis = matCamera.vFront;
					if (KEY_DOWN(set.key_fly_player_strafeUp))
					{
						theta = 0.785;
					}
					else
					{
						theta = 0.05;
					}
					matTargetRotate = matTargetRotate.Rotate( &rotationAxis, theta );
					// set the rotation target
					vecSpeedRotate = matTargetRotate.vFront;
					vecSpeedRotate.Normalize();
				}
				break;
			case strafe_none:
				break;
			}

// rotate the speed

			CVector frontCamOffsetTarget;

			// rotate the speed vector slowly to face the desired target
			CMatrix matSpeedVecRotate;
			matSpeedVecRotate.vFront = vecSpeed;
			matSpeedVecRotate.vFront.Normalize();
			// calculate rotation multiplier, time_diff * 69.0 is ideal for calculations, always time for 69
			rotationMultiplier = (time_diff * 69.0f) / ( 32.0f + (vecSpeed.Length() * 5.0f) );
			// calculate rotation
			rotationAxis = vecSpeedRotate;// + gravCamPed_vecCameraPanOffset;
			rotationAxis.Normalize();
			// magic
			rotationAxis.CrossProduct( &matSpeedVecRotate.vFront );
			// control
			thetaBase = abs(sinh(vecSpeedRotate.DotProduct(&matSpeedVecRotate.vFront)) - 1.175f) / 2.35f + 1.0f;
			theta = thetaBase * rotationMultiplier;
			if ( !near_zero(theta) )
			{
				// rotate
				matSpeedVecRotate = matSpeedVecRotate.Rotate( &rotationAxis, theta );

				// calculate new speed
				float speedReduction = time_diff * (vecSpeed.Length() * (thetaBase - 1.0f));

				// set new speed vector
				matSpeedVecRotate.vFront.Normalize();
				ainfo->m_SpeedVec = matSpeedVecRotate.vFront * ( ainfo->m_SpeedVec.Length() - speedReduction );
			}

			// change animation when we're turning hard & not accelerating
			if (speed > 0.45f
				&& keySpeedState == speed_none
				&& !playerFly_animationDeceleration
				&& ( keyStrafeState == strafe_none || keyStrafeState == strafe_up )
				)
			{
				if ( (GetTickCount() - 500) > playerFly_animationStrafeStateTimer )
				{
					if (playerFly_lastAnimationStates != anim_FALL_skyDive)
					{
						playerFly_lastAnimationStates = anim_FALL_skyDive;
						GTAfunc_PerformAnimation("PARACHUTE", "FALL_skyDive", -1, 1, 1, 0, 0, 0, 1, 0);
					}
					playerFly_animationDeceleration = true;
					playerFly_animationDirectionSpeedDownChanged = false;
				}
				else if ( keyStrafeState == strafe_up )
				{
					if (playerFly_lastAnimationStates != anim_FALL_skyDive)
					{
						playerFly_lastAnimationStates = anim_FALL_skyDive;
						GTAfunc_PerformAnimation("PARACHUTE", "FALL_skyDive", -1, 1, 1, 0, 0, 0, 1, 0);
					}
					playerFly_animationDeceleration = true;
					playerFly_animationDirectionSpeedDownChanged = false;
				}
			}
			else if ( !playerFly_animationDirectionSpeedDownChanged
				&& ( speed < 0.45f )
				)
			{
				if ( keySpeedState == speed_none )
				{
					if (playerFly_lastAnimationStates != anim_Swim_Tread)
					{
						playerFly_lastAnimationStates = anim_Swim_Tread;
						GTAfunc_PerformAnimation("SWIM", "Swim_Tread", -1, 1, 1, 0, 0, 0, 1, 0);
					}
					playerFly_animationDeceleration = false;
				}
				playerFly_animationDirectionSpeedDownChanged = true;
			}

// set the ped rotation target

			// copy speed and normalize, for initial direction
			CVector vecPedRotate = matSpeedVecRotate.vFront; // should use the rotated speed, not original speed
			vecPedRotate.Normalize();

			CMatrix matPedTarget;
			matPedTarget.vFront = matCamera.vFront;
			matPedTarget.vRight = matCamera.vRight + (playerFly_lastPedRotation.vRight * 0.2f);
			matPedTarget.vRight.Normalize();
			matPedTarget.vUp = matCamera.vUp;

			// rotate the ped rotation target to direction of speed
			if (!near_zero(vecSpeed.Length()))
			{
				// rotate target
				rotationAxis = g_vecUpNormal;
				rotationAxis.CrossProduct( &vecPedRotate );
				thetaBase = vecSpeedRotate.DotProduct(&vecPedRotate);
				// drifting
				rotationMultiplier = (time_diff * 69.0f) / ( 18.0f + (vecSpeed.Length() * 1.75f) );
				theta = cos(thetaBase * rotationMultiplier);
				if ( !near_zero(theta) )
				{
					matPedTarget = matPedTarget.Rotate( &rotationAxis, theta );
				}
				// recopy original front
				matPedTarget.vFront = vecPedRotate;

				// rotate the ped rotation target upward during deceleration
				// animation so that the animation is at the correct angle
				if (playerFly_animationDeceleration)
				{
					CVector upStrafeAxis = vecPedRotate;
					upStrafeAxis.CrossProduct(&matPedTarget.vUp);
					rotationMultiplier = (time_diff * 69.0f) / ( 1.0f + (vecSpeed.Length() * 0.25f) );
					thetaBase = -1.5;// * rotationMultiplier; // 1.57 = 90 degrees
					theta = cos(thetaBase * rotationMultiplier);

					// rotate the ped rotation target to direction of speed
					if (!near_zero(vecSpeed.Length()))
					{
						matPedTarget = matPedTarget.Rotate( &upStrafeAxis, theta );
					}
					//upStrafeAxis = upStrafeAxisBuffer;
				}
			}

			// invert right z during strafing
			if ( keyStrafeState == strafe_left
				|| keyStrafeState == strafe_right )
			{
				matPedTarget.vRight.fZ = -matPedTarget.vRight.fZ / 2.0f;
			}

			// normalize everything
			matPedTarget.Normalize(false); // sure, why not

// rotate the ped

			// actual rotation of the ped to smooth movements
			rotationMultiplier = (time_diff * 69.0f) / ( 12.0f + (vecSpeed.Length() * 1.5f) );

			// front camera offset
			rotationAxis = playerFly_lastPedRotation.vFront;
			frontCamOffsetTarget = playerFly_lastPedRotation.vFront;
			frontCamOffsetTarget.Normalize();
			rotationAxis.CrossProduct( &frontCamOffsetTarget );
			thetaBase = playerFly_lastPedRotation.vFront.DotProduct(&frontCamOffsetTarget);
			theta = -cos(thetaBase) * ((time_diff * 69.0f) / 4.5f);
			if ( !near_zero(theta) )
			{
				playerFly_lastPedRotation = playerFly_lastPedRotation.Rotate( &rotationAxis, theta );
				matPedTarget = matPedTarget.Rotate( &rotationAxis, -theta );
			}

			// front
			rotationAxis = playerFly_lastPedRotation.vFront;
			rotationAxis.CrossProduct( &matPedTarget.vFront );
			thetaBase = playerFly_lastPedRotation.vFront.DotProduct(&matPedTarget.vFront);
			theta = -cos(thetaBase) * rotationMultiplier;
			if ( !near_zero(theta) )
			{
				playerFly_lastPedRotation = playerFly_lastPedRotation.Rotate( &rotationAxis, theta );
				matPedTarget = matPedTarget.Rotate( &rotationAxis, theta );
			}

			// right
			rotationAxis = playerFly_lastPedRotation.vRight;
			rotationAxis.CrossProduct( &matPedTarget.vRight );
			thetaBase = playerFly_lastPedRotation.vRight.DotProduct(&matPedTarget.vRight);
			theta = -cos(thetaBase) * (rotationMultiplier * 0.825f);
			if ( !near_zero(theta) )
			{
				playerFly_lastPedRotation = playerFly_lastPedRotation.Rotate( &rotationAxis, theta );
				matPedTarget = matPedTarget.Rotate( &rotationAxis, theta );
			}

			// up
			rotationAxis = playerFly_lastPedRotation.vUp + (g_vecUpNormal / 1.4f);
			rotationAxis.Normalize();
			rotationAxis.CrossProduct( &matPedTarget.vUp );
			thetaBase = playerFly_lastPedRotation.vUp.DotProduct(&matPedTarget.vUp);
			theta = -cos(thetaBase) * (rotationMultiplier / 8.0f);
			if ( !near_zero(theta) )
			{
				playerFly_lastPedRotation = playerFly_lastPedRotation.Rotate( &rotationAxis, theta );
				//matPedTarget = matPedTarget.Rotate( &rotationAxis, theta );
			}

			// normalize everything
			playerFly_lastPedRotation.vFront.Normalize();
			playerFly_lastPedRotation.vRight.Normalize();
			playerFly_lastPedRotation.vUp.Normalize();

			// zero near zero
			playerFly_lastPedRotation.vFront.ZeroNearZero();
			playerFly_lastPedRotation.vRight.ZeroNearZero();
			playerFly_lastPedRotation.vUp.ZeroNearZero();

			// set the position
			playerFly_lastPedRotation.vPos = pPedSelfSA->Placeable.matrix->vPos;

			// set player matrix
			pPedSelf->SetMatrix(&playerFly_lastPedRotation);

// set the camera (our CPed gravity gets ignored while flying)

			// we should be setting it like this
			//CVector smoothedGrav = -playerFly_lastPedRotation.vUp + (g_vecUpNormal * 2.0f);
			//smoothedGrav.Normalize();
			//pPedSelf->SetGravity( &smoothedGrav );
			// -nf

			// but the function is hacked to hell to make it work, so since we're the only
			// thing using it so far, we'll just do this, and fudge the camera in the hook
			// -nf
			pPedSelf->SetGravity( &-playerFly_lastPedRotation.vUp );

			// actually... the camera is doing quite a lot now which is flying specific, with some
			// logic to run when actually flying, so...  just doing literal set gravity is appropriate for now.
			// -nf

		}
	}
	else if ( cheat_state->actor.fly_enabled )
	{
		// set fly disabled
		cheat_state->actor.fly_enabled = false;
		if (cheat_state->actor.fly_active)
		{
			cheat_state->actor.fly_active = false;
			// set gravity down
			pPedSelf->SetGravity( &-g_vecUpNormal );
			// remove up speed hard limiter patch
			if (patch_RemoveFlyUpSpeedLimit.installed)
			{
				patcher_remove(&patch_RemoveFlyUpSpeedLimit);
			}
			// remove fly soft limiters patch
			if (patch_RemoveFlyWindSpeedLimit.installed)
			{
				patcher_remove(&patch_RemoveFlyWindSpeedLimit);
			}
			// copy camera rotation to player
			ainfo->fCurrentRotation = -pGame->GetCamera()->GetCameraRotation();
			ainfo->fTargetRotation = ainfo->fCurrentRotation;
			// stop animation
			playerFly_lastAnimationStates = SHP_Jump_Land;
			GTAfunc_PerformAnimation("SHOP", "SHP_Jump_Land ", -1, 0, 1, 0, 0, 0, 0, 0);
		}
		playerFly_lastKeySpeedState = speed_none;
	}
}