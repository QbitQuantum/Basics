IAction::EStatus CActionItemIdle::Update(float timePassed)
{
	UpdateFragmentTags();

	CWeapon *weapon = m_ownerPlayer.GetWeapon(m_ownerPlayer.GetCurrentItemId());
	bool canPlayIdleBreak = !weapon || !(weapon->IsZoomed() || weapon->IsZoomingInOrOut());
	if (m_playingIdleBreak)
	{
		if (!canPlayIdleBreak)
		{
			m_playingIdleBreak = false;
		}
	}
	else if (canPlayIdleBreak)
	{
		const float currentTime = gEnv->pTimer->GetAsyncCurTime();
		IPlayerInput* pClientInput = m_ownerPlayer.GetPlayerInput();
		if (pClientInput)
		{
			const float idleBreakDelay = g_pGameCVars->cl_idleBreaksDelayTime;
			const float lastInputTime = pClientInput->GetLastRegisteredInputTime();
			const float referenceTime = (float)__fsel((lastInputTime - m_lastIdleBreakTime), lastInputTime, m_lastIdleBreakTime);

			if ((currentTime - referenceTime) > idleBreakDelay)
			{
				m_playingIdleBreak = true;
				SetFragment(m_fragmentIdleBreak, m_fragTags);
				m_lastIdleBreakTime = currentTime;
			}
		}
	}

	if (!m_playingIdleBreak)
	{
		if (GetRootScope().IsDifferent(m_fragmentIdle, m_fragTags))
		{
			SetFragment(m_fragmentIdle, m_fragTags);
		}
	}

	return BaseClass::Update(timePassed);
}