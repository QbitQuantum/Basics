bool CAIActionAttackTurret::TargetInFOV( CAI* pAI )
{
	// Sanity check.

	if( !pAI )
	{
		return false;
	}

	// No ranged weapon!

	CWeapon* pWeapon = pAI->GetAIWeaponMgr()->GetWeaponOfType( kAIWeaponType_Ranged );
	if( !pWeapon )
	{
		return false;
	}

	// Compare the weapon's forward to the target direction.

	LTVector vWeaponForward = pAI->GetWeaponForward( pWeapon );
	LTVector vDirToTarget = pAI->GetAIBlackBoard()->GetBBTargetPosition() - pAI->GetPosition();
	vDirToTarget.Normalize();

	// Target is outside of the weapon's FOV.

	float fFOV20 = cos( DEG2RAD( 10.f ) );
	if( vDirToTarget.Dot( vWeaponForward ) <= fFOV20 )
	{
		return false;
	}

	// Target is inside of the weapon's FOV.

	return true;
}