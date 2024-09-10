void CHUD::IndicateDamage(EntityId weaponId, Vec3 direction, bool onVehicle)
{
	Vec3 vlookingDirection = FORWARD_DIRECTION;
	CGameFlashAnimation* pAnim = NULL;

	CActor *pPlayerActor = static_cast<CActor *>(gEnv->pGame->GetIGameFramework()->GetClientActor());
	if(!pPlayerActor)
		return;

	if(IEntity *pEntity = gEnv->pEntitySystem->GetEntity(weaponId))
	{
		if(pEntity->GetClass() == CItem::sGaussRifleClass)
		{
			m_animRadarCompassStealth.Invoke("GaussHit");
			m_animPlayerStats.Invoke("GaussHit");
		}
	}

	IMovementController *pMovementController = NULL;

	float fFront = 0.0f;
	float fRight = 0.0f;

	if(!onVehicle)
	{
		if(!g_pGameCVars->hud_chDamageIndicator)
			return;
		pMovementController = pPlayerActor->GetMovementController();
		pAnim = m_pHUDCrosshair->GetFlashAnim();
	}
	else if(IVehicle *pVehicle = pPlayerActor->GetLinkedVehicle())
	{
		pMovementController = pVehicle->GetMovementController();
		pAnim = &(m_pHUDVehicleInterface->m_animStats);
	}

	if(pMovementController && pAnim)
	{
		SMovementState sMovementState;
		pMovementController->GetMovementState(sMovementState);
		vlookingDirection = sMovementState.eyeDirection;
	}
	else
		return;

	if(!onVehicle)
	{
		//we use a static/world damage indicator and add the view rotation to the indicator animation now
		fFront = -(Vec3(0,-1,0).Dot(direction));
		fRight = -(Vec3(-1, 0, 0).Dot(direction));
	}
	else
	{
		Vec3 vRightDir = vlookingDirection.Cross(Vec3(0,0,1));
		fFront = -vlookingDirection.Dot(direction);
		fRight = -vRightDir.Dot(direction);
	}

	if(fabsf(fFront) > 0.35f)
	{
		if(fFront > 0)
			pAnim->Invoke("setDamageDirection", 1);
		else
			pAnim->Invoke("setDamageDirection", 3);
	}
	if(fabsf(fRight) > 0.35f)
	{
		if(fRight > 0)
			pAnim->Invoke("setDamageDirection", 2);
		else
			pAnim->Invoke("setDamageDirection", 4);
	}
	if(fFront == 0.0f && fRight == 0.0f)
	{
		pAnim->Invoke("setDamageDirection", 1);
		pAnim->Invoke("setDamageDirection", 2);
		pAnim->Invoke("setDamageDirection", 3);
		pAnim->Invoke("setDamageDirection", 4);
	}

	m_fDamageIndicatorTimer = gEnv->pTimer->GetFrameStartTime().GetSeconds();
}