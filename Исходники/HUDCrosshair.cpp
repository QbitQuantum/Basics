void CHUDCrosshair::Update(float fDeltaTime)
{
	if(m_bBroken)
		return;

	IActor *pClientActor = g_pGame->GetIGameFramework()->GetClientActor();
	IItemSystem *pItemSystem = g_pGame->GetIGameFramework()->GetIItemSystem();
	
	if(!pClientActor || !pItemSystem)
		return;

	IInventory *pInventory = pClientActor->GetInventory();
	if(!pInventory)
		return;

  IItem *pItem = pItemSystem->GetItem(pInventory->GetCurrentItem());      
  IWeapon *pWeapon = NULL;
	IWeapon *pSlaveWeapon = NULL;
	const float fAlternateIronSight = 0.03f;
  
  if(pItem)
	{
		pWeapon = pItem->GetIWeapon();        

		if(pItem->IsDualWieldMaster())
		{
			if(IItem *pSlave=pItem->GetDualWieldSlave())
				pSlaveWeapon = pSlave->GetIWeapon();
		}
  }
  else if(IVehicle *pVehicle=pClientActor->GetLinkedVehicle())
  {
    pItem = pItemSystem->GetItem(pVehicle->GetCurrentWeaponId(pClientActor->GetEntityId()));
    if(pItem)
      pWeapon = pItem->GetIWeapon();
  }

	if(pWeapon)
	{
		float fMinSpread = 0.0f;
		float fMaxSpread = 0.0f;

		m_spread = 0.0f;

		if(IFireMode *pFireMode=pWeapon->GetFireMode(pWeapon->GetCurrentFireMode()))
		{
			fMinSpread = pFireMode->GetMinSpread();
			fMaxSpread = pFireMode->GetMaxSpread();

			m_spread = pFireMode->GetSpread();
		}

		if(pSlaveWeapon)
		{
			if(IFireMode *pSlaveFireMode=pSlaveWeapon->GetFireMode(pSlaveWeapon->GetCurrentFireMode()))
			{
				fMinSpread += pSlaveFireMode->GetMinSpread();
				fMaxSpread += pSlaveFireMode->GetMaxSpread();

				m_spread += pSlaveFireMode->GetSpread();
			}
		}

		CPlayer *pPlayer = static_cast<CPlayer*>(pClientActor);
		if(pPlayer && pPlayer->GetNanoSuit() && pPlayer->GetNanoSuit()->GetMode() == NANOMODE_STRENGTH)
			m_spread *=0.5;

		if(g_pGameCVars->hud_iAlternateCrosshairSpread)
		{
			if(m_spread < fMinSpread)
				m_spread = min(m_spread,g_pGameCVars->hud_fAlternateCrosshairSpreadCrouch) / g_pGameCVars->hud_fAlternateCrosshairSpreadCrouch;
			else
				m_spread = min(m_spread,g_pGameCVars->hud_fAlternateCrosshairSpreadNeutral) / g_pGameCVars->hud_fAlternateCrosshairSpreadNeutral;
		}
		else
		{
			m_spread = min((m_spread-fMinSpread),15.0f) / 15.0f;

			IZoomMode *pZoomMode = pWeapon->GetZoomMode(pWeapon->GetCurrentZoomMode());
			if(pZoomMode && !pZoomMode->IsToggle() && (pZoomMode->IsZoomed() || pZoomMode->IsZooming()))
			{
				m_spread -= fAlternateIronSight;
			}
			else
			{
				m_spread = min(m_spread,1.0f);
				m_spread = max(m_spread,0.0f);
			}
		}
	}

	if(m_animCrossHair.GetVisible() && !g_pHUD->InSpectatorMode())
	{
		//also disables the damage indicator
		if(/*g_pGameCVars->hud_crosshair>0 && m_iCrosshair > 0 &&*/ (g_pGameCVars->g_difficultyLevel<4 || gEnv->bMultiplayer))
		{
			m_animCrossHair.GetFlashPlayer()->Advance(fDeltaTime);
			m_animCrossHair.GetFlashPlayer()->Render();
		}

		if(m_animInterActiveIcons.GetVisible()) //if the crosshair is invisible, the use icon should be too
		{
			if(!m_bHideUseIconTemp)	//hides the icon, when something is already grabbed/being used
			{
				m_animInterActiveIcons.GetFlashPlayer()->Advance(fDeltaTime);
				m_animInterActiveIcons.GetFlashPlayer()->Render();
			}
		}
	}

	if(m_animFriendCross.GetVisible())
	{
		m_animFriendCross.GetFlashPlayer()->Advance(fDeltaTime);
		m_animFriendCross.GetFlashPlayer()->Render();
	}

	if(!g_pGameCVars->hud_iAlternateCrosshairSpread)
	{
		m_spread = max(m_spread,-fAlternateIronSight);
		m_spread = min(m_spread,1.0f);
	}

	if (m_smoothSpread != m_spread)
	{
		Interpolate(m_smoothSpread, m_spread, 20.0f, fDeltaTime);
		m_animCrossHair.Invoke("setRecoil", m_smoothSpread);
	}

	UpdateCrosshair();
}