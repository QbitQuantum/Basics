//-------------------------------------------
void CGameRules::ProcessClientExplosionScreenFX(const ExplosionInfo &explosionInfo)
{
	IActor *pClientActor = g_pGame->GetIGameFramework()->GetClientActor();
	if (pClientActor)
	{
		//Distance
		float dist = (pClientActor->GetEntity()->GetWorldPos() - explosionInfo.pos).len();

		//Is the explosion in Player's FOV (let's suppose the FOV a bit higher, like 80)
		CActor *pActor = (CActor *)pClientActor;
		SMovementState state;
		if (IMovementController *pMV = pActor->GetMovementController())
		{
			pMV->GetMovementState(state);
		}

		Vec3 eyeToExplosion = explosionInfo.pos - state.eyePosition;
		eyeToExplosion.Normalize();
		bool inFOV = (state.eyeDirection.Dot(eyeToExplosion) > 0.68f);
		
		// if in a vehicle eyeDirection is wrong
		if(pActor && pActor->GetLinkedVehicle())
		{
			Vec3 eyeDir = static_cast<CPlayer*>(pActor)->GetVehicleViewDir();
			inFOV = (eyeDir.Dot(eyeToExplosion) > 0.68f);
		}

		//All explosions have radial blur (default 30m radius, to make Sean happy =))
		float maxBlurDistance = (explosionInfo.maxblurdistance>0.0f)?explosionInfo.maxblurdistance:30.0f;
		if (maxBlurDistance>0.0f && g_pGameCVars->g_radialBlur>0.0f && m_explosionScreenFX && explosionInfo.radius>0.5f)
		{		
			if (inFOV && dist < maxBlurDistance)
			{
				ray_hit hit;
				int col = gEnv->pPhysicalWorld->RayWorldIntersection(explosionInfo.pos , -eyeToExplosion*dist, ent_static | ent_terrain, rwi_stop_at_pierceable|rwi_colltype_any, &hit, 1);

				//If there was no obstacle between flashbang grenade and player
				if(!col)
				{
					if (CScreenEffects* pSE = pActor->GetScreenEffects())
					{
						float blurRadius = (-1.0f/maxBlurDistance)*dist + 1.0f;

						gEnv->p3DEngine->SetPostEffectParam("FilterRadialBlurring_Radius", blurRadius);
						gEnv->p3DEngine->SetPostEffectParam("FilterRadialBlurring_Amount", 1.0f);

						IBlendedEffect *pBlur	= CBlendedEffect<CPostProcessEffect>::Create(CPostProcessEffect(pClientActor->GetEntityId(),"FilterRadialBlurring_Amount", 0.0f));
						IBlendType   *pLinear = CBlendType<CLinearBlend>::Create(CLinearBlend(1.0f));
						pSE->StartBlend(pBlur, pLinear, 1.0f, CScreenEffects::eSFX_GID_RBlur);
						pSE->SetUpdateCoords("FilterRadialBlurring_ScreenPosX","FilterRadialBlurring_ScreenPosY", explosionInfo.pos);
					}

					float distAmp = 1.0f - (dist / maxBlurDistance);
					if (gEnv->pInput) 
						gEnv->pInput->ForceFeedbackEvent( SFFOutputEvent(eDI_XI, eFF_Rumble_Basic, 0.5f, distAmp*3.0f, 0.0f));
				}
			}
		}

		//Flashbang effect 
		if(dist<explosionInfo.radius && inFOV &&
			(!strcmp(explosionInfo.effect_class,"flashbang") || !strcmp(explosionInfo.effect_class,"FlashbangAI")))
		{
			ray_hit hit;
			int col = gEnv->pPhysicalWorld->RayWorldIntersection(explosionInfo.pos , -eyeToExplosion*dist, ent_static | ent_terrain, rwi_stop_at_pierceable|rwi_colltype_any, &hit, 1);

			//If there was no obstacle between flashbang grenade and player
			if(!col)
			{
				float power = explosionInfo.flashbangScale;
				power *= max(0.0f, 1 - (dist/explosionInfo.radius));
				float lookingAt = (eyeToExplosion.Dot(state.eyeDirection.normalize()) + 1)*0.5f;
				power *= lookingAt;

				SAFE_GAMEAUDIO_SOUNDMOODS_FUNC(AddSoundMood(SOUNDMOOD_EXPLOSION,MIN(power*40.0f,100.0f)));

				gEnv->p3DEngine->SetPostEffectParam("Flashbang_Time", 1.0f + (power * 4));
				gEnv->p3DEngine->SetPostEffectParam("FlashBang_BlindAmount",explosionInfo.blindAmount);
				gEnv->p3DEngine->SetPostEffectParam("Flashbang_DifractionAmount", (power * 2));
				gEnv->p3DEngine->SetPostEffectParam("Flashbang_Active", 1);
			}
		}
		else if(inFOV && (dist < explosionInfo.radius))
		{
			if (explosionInfo.damage>10.0f || explosionInfo.pressure>100.0f)
			{
				//Add some angular impulse to the client actor depending on distance, direction...
				float dt = (1.0f - dist/explosionInfo.radius);
				dt = dt * dt;
				float angleZ = gf_PI*0.15f*dt;
				float angleX = gf_PI*0.15f*dt;

				pActor->AddAngularImpulse(Ang3(Random(-angleX*0.5f,angleX),0.0f,Random(-angleZ,angleZ)),0.0f,dt*2.0f);
			}
		}


		float fDist2=(pClientActor->GetEntity()->GetWorldPos()-explosionInfo.pos).len2();
		if (fDist2<250.0f*250.0f)
		{		
			if (fDist2<sqr(SAFE_GAMEAUDIO_BATTLESTATUS_FUNC_RET(GetBattleRange())))
				SAFE_GAMEAUDIO_BATTLESTATUS_FUNC(TickBattleStatus(1.0f));
		}
	}

}