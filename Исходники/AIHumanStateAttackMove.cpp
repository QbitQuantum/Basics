void CAIHumanStateAttackMove::SelectMoveAnim()
{
	// Only turn around once.
	// This prevents the AI from flipping out when the players runs around him.

	if( m_bTurnedAround )
	{
		return;
	}

	LTVector vDestDir = m_vAttackMoveDest - GetAI()->GetPosition();
	vDestDir.y = 0.f;
	vDestDir.Normalize();
	LTVector vTargetDir = GetAI()->GetTarget()->GetVisiblePosition() - GetAI()->GetPosition();
	vTargetDir.y = 0.f;
	vTargetDir.Normalize();

	// Should the AI turn around and face forward?

	if( m_pStrategyFollowPath->GetMovement() == kAP_BackUp )
	{
		LTFLOAT fDot = vDestDir.Dot( vTargetDir );	
		if( fDot > c_fFOV160 )
		{
			GetAI()->FaceTargetRotImmediately();
			m_pStrategyFollowPath->SetMovement( kAP_Run );
			m_bTurnedAround = LTTRUE;
		}
	}

	// Should the AI turn around and face backward?

	else {
		vDestDir = -vDestDir;
		LTFLOAT fDot = vDestDir.Dot( vTargetDir );	
		if( fDot > c_fFOV160 )
		{
			GetAI()->FaceTargetRotImmediately();
			m_pStrategyFollowPath->SetMovement( kAP_BackUp );
			m_bTurnedAround = LTTRUE;
		}
	}
}