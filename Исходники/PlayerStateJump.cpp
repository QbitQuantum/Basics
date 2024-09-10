void CPlayerStateJump::Landed(CPlayer& player, const bool isHeavyWeapon, float fallSpeed)
{
#ifdef STATE_DEBUG
	bool remoteControlled = false;
	IVehicle* pVehicle = player.GetLinkedVehicle();
	if(pVehicle)
	{
		IVehicleSeat* pVehicleSeat = pVehicle->GetSeatForPassenger(player.GetEntityId());
		if(pVehicleSeat && pVehicleSeat->IsRemoteControlled())
		{
			remoteControlled = true;
		}
	}
	CRY_ASSERT_MESSAGE( player.GetLinkedEntity()==NULL || remoteControlled, "Cannot 'land' when you're linked to another entity!" );
#endif

	const SPlayerStats& stats = player.m_stats;

	Vec3 playerPosition = player.GetEntity()->GetWorldPos();
	IPhysicalEntity *phys = player.GetEntity()->GetPhysics();
	IMaterialEffects *mfx = gEnv->pGame->GetIGameFramework()->GetIMaterialEffects();

	const SActorPhysics& actorPhysics = player.GetActorPhysics();
	int matID = actorPhysics.groundMaterialIdx != -1 ? actorPhysics.groundMaterialIdx : mfx->GetDefaultSurfaceIndex();

	const float fHeightofEntity = playerPosition.z;
	const float worldWaterLevel = player.m_playerStateSwim_WaterTestProxy.GetWaterLevel();
	
	TMFXEffectId effectId = mfx->GetEffectId("bodyfall", matID);
	if (effectId != InvalidEffectId)
	{
		SMFXRunTimeEffectParams params;
		Vec3 direction = Vec3(0,0,0);
		if (IMovementController *pMV = player.GetMovementController())
		{
			SMovementState state;
			pMV->GetMovementState(state);
			direction = state.aimDirection;
		}
		params.pos = playerPosition + direction;
		//params.soundSemantic = eSoundSemantic_Player_Foley;

		float landFallParamVal = (float)__fsel( -(fallSpeed - 7.5f), 0.25f, 0.75f);
		params.AddAudioRtpc("landfall", landFallParamVal);

		const float speedParamVal = min(fabsf((actorPhysics.velocity.z * 0.1f)), 1.0f);
		params.AddAudioRtpc("speed", speedParamVal);

		mfx->ExecuteEffect(effectId, params);
	}

	bool heavyLanded = false;

	IItem* pCurrentItem = player.GetCurrentItem();
	CWeapon* pCurrentWeapon = pCurrentItem ? static_cast<CWeapon*>(pCurrentItem->GetIWeapon()) : NULL;

	if (fallSpeed > 0.0f && player.IsPlayer())
	{
		if(!gEnv->bMultiplayer)
		{
			const float verticalSpeed = fabs(fallSpeed);
			const float speedForHeavyLand = g_pGameCVars->pl_health.fallSpeed_HeavyLand;
			if ((verticalSpeed >= speedForHeavyLand) && (player.GetPickAndThrowEntity() == 0) && !player.IsDead())
			{
				if ( !isHeavyWeapon )
				{
					if (pCurrentWeapon)
					{
						pCurrentWeapon->FumbleGrenade();
						pCurrentWeapon->CancelCharge();
					}

					player.StartInteractiveActionByName("HeavyLand", false);
				}
				heavyLanded = true;
			}
		}
	}

	if(player.m_isClient)
	{
		if (fallSpeed > 0.0f)
		{
			const float fallIntensityMultiplier = stats.wasHit ? g_pGameCVars->pl_fall_intensity_hit_multiplier : g_pGameCVars->pl_fall_intensity_multiplier;
			const float fallIntensityMax = g_pGameCVars->pl_fall_intensity_max;
			const float fallTimeMultiplier = g_pGameCVars->pl_fall_time_multiplier;
			const float fallTimeMax = g_pGameCVars->pl_fall_time_max;
			const float zoomMultiplayer = (pCurrentWeapon && pCurrentWeapon->IsZoomed()) ? 0.2f : 1.0f;
			const float direction = ((cry_rand()%2)==0) ? -1.0f : 1.0f;
			const float intensity = clamp_tpl(fallIntensityMultiplier*fallSpeed*zoomMultiplayer, 0.0f, fallIntensityMax);
			const float shakeTime = clamp_tpl(fallTimeMultiplier*fallSpeed*zoomMultiplayer, 0.0f, fallTimeMax);
			const Vec3 rotation = Vec3(-0.5f, 0.15f*direction, 0.05f*direction);

			if (CScreenEffects* pGameScreenEffects = g_pGame->GetScreenEffects())
			{
				pGameScreenEffects->CamShake(rotation*intensity, Vec3(0, 0, 0), shakeTime, shakeTime, 0.05f, CScreenEffects::eCS_GID_Player);
			}

			IForceFeedbackSystem* pForceFeedback = g_pGame->GetIGameFramework()->GetIForceFeedbackSystem();
			assert(pForceFeedback);

			ForceFeedbackFxId fxId = pForceFeedback->GetEffectIdByName("landFF");
			pForceFeedback->PlayForceFeedbackEffect(fxId, SForceFeedbackRuntimeParams(intensity, 0.0f));

			if(fallSpeed > 7.0f)
			{
				player.PlaySound(CPlayer::ESound_Fall_Drop);
			}

			CPlayer::EPlayerSounds playerSound = heavyLanded ? CPlayer::ESound_Gear_HeavyLand : CPlayer::ESound_Gear_Land;
			player.PlaySound(playerSound, true);
		}
		CCCPOINT(PlayerMovement_LocalPlayerLanded);
	}
	
	if( gEnv->pAISystem )
	{
		// Notify AI
		//If silent feet active, ignore here
		const float noiseSupression = 0.0f;
		const float fAISoundRadius = (g_pGameCVars->ai_perception.landed_baseRadius + (g_pGameCVars->ai_perception.landed_speedMultiplier * fallSpeed)) * (1.0f - noiseSupression);
		SAIStimulus stim(AISTIM_SOUND, AISOUND_MOVEMENT_LOUD, player.GetEntityId(), 0,
			player.GetEntity()->GetWorldPos() + player.GetEyeOffset(), ZERO, fAISoundRadius);
		gEnv->pAISystem->RegisterStimulus(stim);
	}

	// Record 'Land' telemetry stats.

	CStatsRecordingMgr::TryTrackEvent(&player, eGSE_Land, fallSpeed);

	if (fallSpeed > 0.0f)
	{
		player.CreateScriptEvent( heavyLanded ? "heavylanded" : "landed",stats.fallSpeed);
	}
}