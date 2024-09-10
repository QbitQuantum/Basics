bool CAIActionAttackLungeUncloaked::ValidateContextPreconditions( CAI* pAI, CAIWorldState& wsWorldStateGoal, bool bIsPlanning )
{
	// AI doesn't have a target.

	if (!pAI->HasTarget( kTarget_Character ))
	{
		return false;
	}

	// Target is not visible.

	if( !pAI->GetAIBlackBoard()->GetBBTargetVisibleFromWeapon() )
	{
		return false;
	}

	// AI does not have a weapon of the correct type

	if (!AIWeaponUtils::HasWeaponType(pAI, GetWeaponType(), bIsPlanning))
	{
		return false;
	}

	// AI does not have any ammo for this weapon.

	if ( !AIWeaponUtils::HasAmmo( pAI, GetWeaponType(), bIsPlanning ) )
	{
		return false;
	}

	// Someone else is lunging.  Only one AI may lunge at a time.

	CAIWMFact factQuery;
	factQuery.SetFactType( kFact_Knowledge );
	factQuery.SetKnowledgeType( kKnowledge_Lunging );
	CAIWMFact* pFact = g_pAIWorkingMemoryCentral->FindWMFact(factQuery);
	if( pFact )
	{
		// Clear records of dead AI.

		if( IsDeadAI( pFact->GetSourceObject() ) )
		{
			g_pAIWorkingMemoryCentral->ClearWMFacts( factQuery );
		}
		else return false;
	}

	// Bail if the Action's SmartObject record does not exist.

	AIDB_SmartObjectRecord* pSmartObjectRecord = g_pAIDB->GetAISmartObjectRecord( m_pActionRecord->eSmartObjectID );
	if( !pSmartObjectRecord )
	{
		return false;
	}


	// Someone has lunged too recently.

	if( pSmartObjectRecord->fTimeout > 0.f )
	{
		factQuery.SetFactType( kFact_Knowledge );
		factQuery.SetKnowledgeType( kKnowledge_NextLungeTime );
		pFact = g_pAIWorkingMemoryCentral->FindWMFact(factQuery);
		if( pFact && ( pFact->GetTime() > g_pLTServer->GetTime() ) )
		{
			return false;
		}
	}

	// Bail if the AI does not have the desire to lunge.
	// The desire indicates the max range of the lunge.

	CAIWMFact factDesireQuery;
	factDesireQuery.SetFactType( kFact_Desire );
	factDesireQuery.SetDesireType( kDesire_Lunge );
	CAIWMFact* pDesireFact = pAI->GetAIWorkingMemory()->FindWMFact( factDesireQuery );
	if( !pDesireFact )
	{
		return false;
	}

	// Target must be in range.

	LTVector vTarget = pAI->GetAIBlackBoard()->GetBBTargetPosition();
	float fDistSqr = vTarget.DistSqr( pAI->GetPosition() );

	// Target too close.

	if( fDistSqr < pSmartObjectRecord->fMinDist * pSmartObjectRecord->fMinDist )
	{
		return false;
	}

	// Target too far.

	float fMaxDist = GetLungeMaxDist( pAI, pDesireFact );
	if( fDistSqr > fMaxDist * fMaxDist )
	{
		return false;
	}

	// No straight path to the target.

	LTVector vDir = vTarget - pAI->GetPosition();
	vDir.Normalize();
	LTVector vDest = pAI->GetPosition() + ( vDir * ( fMaxDist + 50.f ) );
	if( !g_pAIPathMgrNavMesh->StraightPathExists( pAI, pAI->GetCharTypeMask(), pAI->GetPosition(), vDest, pAI->GetAIBlackBoard()->GetBBTargetReachableNavMeshPoly(), pAI->GetRadius() ) )
	{
		return false;
	}

	// Lunge!

	return true;
}