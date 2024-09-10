bool CPlayerStateUtil::ShouldSprint( const CPlayer& player, const SActorFrameMovementParams& movement, IItem* pCurrentPlayerItem )
{
	bool shouldSprint = false;
	const SPlayerStats& stats = player.m_stats;
	const bool movingForward = IsMovingForward( player, movement );

	bool restrictSprint = player.IsJumping() || stats.bIgnoreSprinting || player.IsSliding() || player.IsCinematicFlagActive(SPlayerStats::eCinematicFlag_RestrictMovement);

	CWeapon* pWeapon = pCurrentPlayerItem ? static_cast<CWeapon*>(pCurrentPlayerItem->GetIWeapon()) : NULL;
	bool isZooming = pWeapon ? pWeapon->IsZoomed() && !pWeapon->IsZoomingInOrOut() : false;
	if (pWeapon && !pWeapon->CanSprint())
		restrictSprint = true;
	
	restrictSprint = restrictSprint || (player.GetSprintStaminaLevel() <= 0.f);
	//CryLogAlways("  restrictSprint = %d", restrictSprint);

	if (player.IsSprinting() == false)
	{
		shouldSprint = movingForward && !restrictSprint && !isZooming;
		CCCPOINT_IF(shouldSprint, PlayerMovement_SprintOn);
	}
	else
	{
		shouldSprint = movingForward && !restrictSprint && !isZooming;
		//CryLogAlways("  shouldSprint = %d", shouldSprint);

		shouldSprint = shouldSprint && (!(player.m_actions & ACTION_CROUCH));

		if(!shouldSprint && pWeapon)
		{
			pWeapon->ForcePendingActions();
		}
	}

	CCCPOINT_IF(!player.IsSprinting() && !shouldSprint && (player.m_actions & ACTION_SPRINT), PlayerMovement_SprintRequestIgnored);
	CCCPOINT_IF(player.IsSprinting() && !shouldSprint, PlayerMovement_SprintOff);

	//CryLogAlways("  returning (for \"%s\") shouldSprint = %d", m_player.GetEntity()->GetName(), shouldSprint);
	return shouldSprint;
}