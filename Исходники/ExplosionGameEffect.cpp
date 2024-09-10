//--------------------------------------------------------------------------------------------------
// Name: SpawnScreenExplosionEffect
// Desc: Spawns screen explosion effect
//--------------------------------------------------------------------------------------------------
void CExplosionGameEffect::SpawnScreenExplosionEffect(const SExplosionContainer &explosionContainer)
{
	// Disclaimer: this code was originally from GameRulesClientServer::ProcessClientExplosionScreenFX()

	const ExplosionInfo& explosionInfo = explosionContainer.m_explosionInfo;

	if(explosionInfo.pressure < 1.0f)
		return;

	IActor *pClientActor = g_pGame->GetIGameFramework()->GetClientActor();
	if(pClientActor != NULL && !pClientActor->IsDead())
	{
		CPlayer* pPlayer = static_cast<CPlayer*>(pClientActor);
		bool hasFlashBangEffect = explosionInfo.blindAmount > 0.0f;

		// Flashbang friends and self?...
		if(hasFlashBangEffect)
		{
			bool flashBangSelf = true;
			bool flashBangFriends = false;
#ifndef _RELEASE
			flashBangSelf = g_pGameCVars->g_flashBangSelf != 0;
			flashBangFriends = g_pGameCVars->g_flashBangFriends != 0;
#endif
			bool ownFlashBang = pPlayer->GetEntityId() == explosionInfo.shooterId;
			if((!flashBangSelf && ownFlashBang) || // FlashBang self?
				((g_pGame->GetGameRules()->GetFriendlyFireRatio()<=0.0f) && (!flashBangFriends) && (!ownFlashBang) && pPlayer->IsFriendlyEntity(explosionInfo.shooterId))) // FlashBang friends?
			{
				return;
			}
		}

		// Distance
		float dist = (pClientActor->GetEntity()->GetWorldPos() - explosionInfo.pos).len();

		// Is the explosion in Player's FOV (let's suppose the FOV a bit higher, like 80)
		SMovementState state;
		if(IMovementController *pMV = pClientActor->GetMovementController())
		{
			pMV->GetMovementState(state);
		}

		Vec3 eyeToExplosion = explosionInfo.pos - state.eyePosition;
		Vec3 eyeDir = pClientActor->GetLinkedVehicle() ? pPlayer->GetVehicleViewDir() : state.eyeDirection;
		eyeToExplosion.Normalize();
		float eyeDirectionDP = eyeDir.Dot(eyeToExplosion);
		bool inFOV = (eyeDirectionDP > 0.68f);

		// All explosions have radial blur (default 30m radius)
		const float maxBlurDistance = (explosionInfo.maxblurdistance >0.0f) ? explosionInfo.maxblurdistance : 30.0f;
		if((maxBlurDistance > 0.0f) && (g_pGameCVars->g_radialBlur > 0.0f) && (explosionInfo.radius > 0.5f))
		{		
			if (inFOV && (dist < maxBlurDistance))
			{
				const int intersectionObjTypes = ent_static | ent_terrain;
				const unsigned int intersectionFlags = rwi_stop_at_pierceable|rwi_colltype_any;

				m_deferredScreenEffects.RequestRayCast(CDeferredExplosionEffect::eDET_RadialBlur, 
														explosionInfo.pos, -eyeToExplosion, dist, maxBlurDistance, intersectionObjTypes, intersectionFlags, NULL, 0);
			}
		}

		// Flashbang effect 
		if(hasFlashBangEffect && ((dist < (explosionInfo.radius*g_pGameCVars->g_flashBangNotInFOVRadiusFraction)) 
			|| (inFOV && (dist < explosionInfo.radius))))
		{
			ray_hit hit;
			const int intersectionObjTypes = ent_static | ent_terrain;
			const unsigned int intersectionFlags = rwi_stop_at_pierceable|rwi_colltype_any;
			const int intersectionMaxHits = 1;

			int collision = gEnv->pPhysicalWorld->RayWorldIntersection(	explosionInfo.pos, 
																																	-eyeToExplosion*dist, 
																																	intersectionObjTypes, 
																																	intersectionFlags, 
																																	&hit, 
																																	intersectionMaxHits);

			// If there was no obstacle between flashbang grenade and player
			if(!collision)
			{
				bool enabled = true;
				if(enabled)
				{
					CCCPOINT (FlashBang_Explode_BlindLocalPlayer);
					float timeScale = max(0.0f, 1 - (dist/explosionInfo.radius));
					float lookingAt = max(g_pGameCVars->g_flashBangMinFOVMultiplier, (eyeDirectionDP + 1)*0.5f);

					float time = explosionInfo.flashbangScale * timeScale *lookingAt;	// time is determined by distance to explosion		

					CRY_ASSERT_MESSAGE(pClientActor->IsPlayer(),"Effect shouldn't be spawned if not a player");

					SPlayerStats* pStats = static_cast<SPlayerStats*>(pPlayer->GetActorStats());

					NET_BATTLECHATTER(BC_Blinded, pPlayer);

					if(pClientActor->GetEntityId() == explosionInfo.shooterId)
					{
						g_pGame->GetPersistantStats()->IncrementClientStats(EIPS_BlindSelf);
					}
					else
					{
						g_pGame->GetGameRules()->SuccessfulFlashBang(explosionInfo, time);
					}

					pPlayer->StartFlashbangEffects(time, explosionInfo.shooterId);

					gEnv->p3DEngine->SetPostEffectParam("Flashbang_Time", time);
					gEnv->p3DEngine->SetPostEffectParam("FlashBang_BlindAmount", explosionInfo.blindAmount);
					gEnv->p3DEngine->SetPostEffectParam("Flashbang_DifractionAmount", time);
					gEnv->p3DEngine->SetPostEffectParam("Flashbang_Active", 1.0f);

					CRecordingSystem *pRecordingSystem = g_pGame->GetRecordingSystem();
					if (pRecordingSystem)
					{
						pRecordingSystem->OnPlayerFlashed(time, explosionInfo.blindAmount);
					}
				}
			}
			else
			{
				CCCPOINT (FlashBang_Explode_NearbyButBlockedByGeometry);
			}
		}
		else if(inFOV && (dist < explosionInfo.radius))
		{
			if(explosionInfo.damage>10.0f || explosionInfo.pressure>100.0f)
			{
				// Add some angular impulse to the client actor depending on distance, direction...
				float dt = (1.0f - dist/explosionInfo.radius);
				dt = dt * dt;
				float angleZ = gf_PI*0.15f*dt;
				float angleX = gf_PI*0.15f*dt;

				if (pClientActor)
				{
					static_cast<CActor*>(pClientActor)->AddAngularImpulse(Ang3(cry_random(-angleX*0.5f,angleX),0.0f,cry_random(-angleZ,angleZ)),0.0f,dt*2.0f);
				}
			}
		}
	}
}//-------------------------------------------------------------------------------------------------