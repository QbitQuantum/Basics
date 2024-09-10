LTVector CAIWeaponMelee::GetFirePosition(CAI* pAI)
{
	// Force fire position to come from the edge of the target's radius.
	// This should ensure a successful melee hit.

	if( pAI && m_bForceHit )
	{
		HOBJECT hTarget = pAI->GetAIBlackBoard()->GetBBTargetObject();
		if( IsCharacter( hTarget ) )
		{
			LTVector vTargetPos;
			g_pLTServer->GetObjectPos( hTarget, &vTargetPos );

			LTVector vDir = vTargetPos - pAI->GetPosition();
			vDir.Normalize();

			CCharacter* pChar = (CCharacter*)g_pLTServer->HandleToObject( hTarget );
			LTVector vFirePos = vTargetPos - ( vDir * pChar->GetRadius() );

			return vFirePos;
		}
	}

	// Default behavior.

	return DefaultGetFirePosition(pAI);
}