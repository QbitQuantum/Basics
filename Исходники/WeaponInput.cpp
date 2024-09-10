bool CWeapon::OnActionZoom(EntityId actorId, const ActionId& actionId, int activationMode, float value)
{
	if (IsModifying())
	{
		return false;
	}

	const bool zoomingIn = IsZoomingIn();
	const bool zoomed = IsZoomed();

	const bool toggleMode = (g_pGameCVars->cl_zoomToggle > 0);
	const bool toggleZoomOn = !(zoomingIn || zoomed);

	const bool buttonPressed = (activationMode == eAAM_OnPress);

	if (!toggleMode)
	{
		// Toggle mode is off, i.e. You have to hold to stay zoomed.
		if(buttonPressed || activationMode == eAAM_OnHold)
		{
			SetInputFlag(eWeaponAction_Zoom);
		}
		else
		{
			ClearInputFlag(eWeaponAction_Zoom);
		}
	}
	else
	{
		// Toggle mode is on.
		if(buttonPressed)
		{
			if (toggleZoomOn)
			{
				SetInputFlag(eWeaponAction_Zoom);
			}
			else
			{
				ClearInputFlag(eWeaponAction_Zoom);
			}
		}
	}
	
	//can ironsight while super jumping in MP
	const bool trumpZoom = !CanZoomInState();

	if (!AreAnyItemFlagsSet(eIF_Modifying) && !trumpZoom)	
	{
		if (!m_fm || !m_fm->IsReloading())
		{
			if (buttonPressed && (!toggleMode || toggleZoomOn))
			{
				if(m_fm && !m_fm->AllowZoom())
				{
					if(IsTargetOn())
					{
						m_fm->Cancel();
					}
					else
					{
						return false;
					}
				}
			}
			else if ((!toggleMode && activationMode == eAAM_OnRelease) || // Not toggle mode and button is released
							 (toggleMode && !toggleZoomOn && buttonPressed)) // Toggle mode, zoom is to be toggled off and button is pressed
			{
				StopZoom(actorId);
			}

			const bool shouldStartZoom = (!toggleMode && (buttonPressed || activationMode == eAAM_OnHold)) ||
																	 (toggleMode && toggleZoomOn && buttonPressed);
			if (m_zm && shouldStartZoom)
			{
				const bool zoomingOut = m_zm->IsZoomingInOrOut() && !zoomingIn;
				if ((!zoomed && !zoomingIn) || zoomingOut)
				{
					StartZoom(actorId,1);
				}
				if (buttonPressed)
				{
					m_snapToTargetTimer = 0.5f;
				}
			}
		}
		else if( (!toggleMode && activationMode == eAAM_OnRelease) || (toggleMode && !toggleZoomOn && buttonPressed) )
		{
			StopZoom(actorId);
		}
	}
	else if (trumpZoom)
	{
		StopZoom(actorId);
	}

	return true;
}