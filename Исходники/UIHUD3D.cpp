void CUIHUD3D::UpdateView(const SViewParams &viewParams)
{
	CActor* pLocalPlayer = (CActor*)g_pGame->GetIGameFramework()->GetClientActor();
	
	if (gEnv->IsEditor() && !gEnv->IsEditing() && !m_pHUDRootEntity)
		SpawnHudEntities();

	// When you die we destroy the HUD, so this will make sure it re-spawns when you respawned
	if (!gEnv->IsEditor() && !m_pHUDRootEntity)
		SpawnHudEntities();
	
	const CUICVars* pCVars = g_pGame->GetUI()->GetCVars();
	if (m_pHUDRootEntity && pLocalPlayer)
	{
		if(pCVars->hud_detach)
			return;

		const QuatT& cameraTran = pLocalPlayer->GetCameraTran();
		const QuatT& hudTran = pLocalPlayer->GetHUDTran();

		const Quat& cameraRotation = cameraTran.q;
		const Quat& hudRotation = hudTran.q;
		Quat deltaHudRotation = cameraRotation.GetInverted() * hudRotation;

		if(pCVars->hud_bobHud > 0.0f && !pLocalPlayer->IsDead())
		{
			deltaHudRotation.w *= (float)__fres(pCVars->hud_bobHud);

			// Avoid divide by 0  
			if (!(fabs(deltaHudRotation.w) < FLT_EPSILON)) // IsValid() doesn't catch it
			{
				deltaHudRotation.Normalize();
			}
		}
		else
		{
			deltaHudRotation.SetIdentity();
		}

		// In general use the player position + viewparams override
		Vec3 viewPosition = pLocalPlayer->GetEntity()->GetPos() + viewParams.position;
		Quat clientRotation = viewParams.rotation * deltaHudRotation;
		
		// Override special cases: Third person should use camera-oriented HUD instead of HUD-bone oriented
		// Sliding should use the Bone instead of the viewParams solution
		if(pLocalPlayer->IsThirdPerson() || pLocalPlayer->GetLinkedVehicle() != NULL)
		{
			viewPosition = viewParams.position;
		}
		else
		{
			CPlayer* player = (CPlayer*)pLocalPlayer;
			if(player && player->IsSliding())
			{
				viewPosition = pLocalPlayer->GetEntity()->GetWorldTM().TransformPoint(hudTran.t);
			}
		}
		//

		const Vec3 forward(clientRotation.GetColumn1());
		const Vec3 up(clientRotation.GetColumn2());
		const Vec3 right(-(up % forward));

		const float distance = pCVars->hud_cameraOverride ? pCVars->hud_cameraDistance : m_fHudDist;
		const float offset = pCVars->hud_cameraOverride ? pCVars->hud_cameraOffsetZ  : m_fHudZOffset;

		float offsetScale = 1.0f;
		if(viewParams.fov > 0.0f)
		{
			offsetScale = (pCVars->hud_cgf_positionScaleFOV * __fres(viewParams.fov )) + distance;
		}
		
		// Allow overscanBorders to control safe zones
		Vec2 overscanBorders = ZERO;
		if(gEnv->pRenderer)
		{	
			gEnv->pRenderer->EF_Query(EFQ_OverscanBorders, overscanBorders);
		}
		const float viewDepth = 1.0f + (pCVars->hud_overscanBorder_depthScale * overscanBorders.y);
		viewPosition += forward*viewDepth*offsetScale;

		viewPosition += (up * offset);
		viewPosition += (right * pCVars->hud_cgf_positionRightScale);
		const Vec3 posVec(viewPosition + (forward * 0.001f));

		static const Quat rot90Deg = Quat::CreateRotationXYZ( Ang3(gf_PI * 0.5f, 0, 0) );
		const Quat rotation = clientRotation * rot90Deg; // rotate 90 degrees around X-Axis

		m_pHUDRootEntity->SetPosRotScale(posVec, rotation, m_pHUDRootEntity->GetScale(), ENTITY_XFORM_NO_SEND_TO_ENTITY_SYSTEM);
	}

	if (gEnv->pRenderer && m_pHUDRootEntity && pCVars->hud_debug3dpos > 0)
	{
		gEnv->pRenderer->GetIRenderAuxGeom()->DrawSphere(m_pHUDRootEntity->GetWorldPos(), 0.2f, ColorB(255,0,0));
		const int children = m_pHUDRootEntity->GetChildCount();
		for (int i = 0; i < children && pCVars->hud_debug3dpos > 1; ++i)
		{
			IEntity* pChild = m_pHUDRootEntity->GetChild(i);
			gEnv->pRenderer->GetIRenderAuxGeom()->DrawSphere(pChild->GetWorldPos(), 0.1f, ColorB(255,255,0));
		}
	}
}