bool CAIWeaponAbstract::GetShootPosition( CAI* pAI, AimContext& Context,LTVector& outvShootPos )
{
	ASSERT(pAI);

	// Cineractive firing.

	if( m_eFiringState == kAIFiringState_CineFiring )
	{
		LTVector vDir = pAI->GetWeaponForward( m_pWeapon );
		vDir.Normalize();
		outvShootPos = pAI->GetPosition() + ( vDir * 5000.f );
		return true;
	}

	// If perfect accuracy is enabled, we are done.

	if( pAI->GetAIBlackBoard()->GetBBPerfectAccuracy() )
	{
		HOBJECT hTarget = pAI->GetAIBlackBoard()->GetBBTargetObject();
		g_pLTServer->GetObjectPos( hTarget, &outvShootPos );
		return true;
	}

	// Initially aim for the target's visible position.
	// If the target is not visible at all, use his actual position.
	// This is a failsafe for AI shooting at the origin if they have
	// not yet seen the target ever.

	LTVector vVisiblePosition = pAI->GetTarget()->GetVisiblePosition();
	if( !pAI->GetAIBlackBoard()->GetBBTargetVisibleFromWeapon() )
	{
		vVisiblePosition = pAI->GetAIBlackBoard()->GetBBTargetPosition();
	}
	outvShootPos = vVisiblePosition;

	// If Target is within the FullAccuracy radius, we are done.

	if( pAI->GetTarget()->GetTargetDistSqr() < pAI->GetFullAccuracyRadiusSqr() )
	{
		return true;
	}

	// The following code forces the AI to intenionally miss every x
	// number of shots, depending on their accuracy. This gives players
	// the excitement of getting shot at without killing them too fast.

	// For example, if accuracy = 0.5 there will be a guaranteed sequence
	// of HIT, MISS, HIT, MISS, ...
	// If accuracy = 0.25, then HIT, MISS, MISS, MISS, HIT, MISS, MISS, MISS, etc.
	// If accuracy = 0.75, then HIT, HIT, HIT, MISS, HIT, HIT, HIT, MISS, etc.

	// Calculate the ratio of hits to misses based on the current 
	// accuracy.  This needs to be recalculated for every shot, 
	// because accuracy may change at any time.

	float fAccuracy = m_flWeaponContextInaccuracyScalar * pAI->GetAccuracy();
	if( fAccuracy <= 0.f )
	{
		Context.m_cMisses = 1;
		Context.m_cHits = 0;
	}
	else if( fAccuracy >= 1.f )
	{
		Context.m_cMisses = 0;
		Context.m_cHits = 1;
	}
	else if( fAccuracy < 0.5f )
	{
		Context.m_cMisses = (uint32)( ( ( 1.f - fAccuracy ) / fAccuracy ) + 0.5f );
		Context.m_cHits = 1;
	}
	else 
	{
		Context.m_cMisses = 1;
		Context.m_cHits = (uint32)( ( fAccuracy / ( 1.f - fAccuracy ) ) + 0.5f );
	}

	// If we have met or exceeded the required number of misses, 
	// reset the counters.

	if( Context.m_iMiss >= Context.m_cMisses )
	{
		Context.m_iHit = 0;
		Context.m_iMiss = 0;
	}

	//
	// First take care of hits, then take care of misses.
	//

	// Hit.

	if( Context.m_iHit < Context.m_cHits )
	{
		++Context.m_iHit;

		// Blind fire.

		if( pAI->GetAIBlackBoard()->GetBBBlindFire() )
		{
			GetBlindFirePosition( pAI, outvShootPos, !FIRE_MISS );
			return false;
		}

		// Suppression fire at last known pos.

		if( pAI->GetAIBlackBoard()->GetBBSuppressionFire() )
		{
			HOBJECT hTarget = pAI->GetAIBlackBoard()->GetBBTargetObject();

			CAIWMFact factQuery;
			factQuery.SetFactType( kFact_Character );
			factQuery.SetTargetObject( hTarget );
			CAIWMFact* pFact = pAI->GetAIWorkingMemory()->FindWMFact( factQuery );
			if( pFact )
			{
				outvShootPos = pFact->GetPos();
			}
		}

		// Default fire.

		// If target has started moving or change directions recently,
		// factor in some inaccuracy.

		float fInnaccuracy = LTMAX( 0.f, pAI->GetTarget()->GetCurMovementInaccuracy() );
		if( fInnaccuracy > 0.f )
		{
			LTVector vShootOffset = LTVector(	GetRandom( -fInnaccuracy, fInnaccuracy ),
				GetRandom( -fInnaccuracy * 0.5f, fInnaccuracy * 0.5f ),
				GetRandom( -fInnaccuracy, fInnaccuracy ) );
			vShootOffset.Normalize();

			outvShootPos += vShootOffset * 100.0f;
		}
		
		return true;
	}

	// Miss.

	else 
	{
		++Context.m_iMiss;

		// Blind fire.

		if( pAI->GetAIBlackBoard()->GetBBBlindFire() )
		{
			GetBlindFirePosition( pAI, outvShootPos, FIRE_MISS );
			return false;
		}

		// Default fire.

		HOBJECT hTarget = pAI->GetAIBlackBoard()->GetBBTargetObject();
		if( !IsCharacter( hTarget ) )
		{
			return false;
		}

		CCharacter* pChar = (CCharacter*)g_pLTServer->HandleToObject( hTarget );
		if( !pChar )
		{
			return false;
		}

		// Intentionally shoot a little short of the target.

		LTVector vPos = pAI->GetAIBlackBoard()->GetBBTargetPosition();;

		// Suppression fire at last known pos.

		if( pAI->GetAIBlackBoard()->GetBBSuppressionFire() )
		{
			CAIWMFact factQuery;
			factQuery.SetFactType( kFact_Character );
			factQuery.SetTargetObject( hTarget );
			CAIWMFact* pFact = pAI->GetAIWorkingMemory()->FindWMFact( factQuery );
			if( pFact )
			{
				vPos = pFact->GetPos();
			}
		}

		float fDist = sqrt( pAI->GetTarget()->GetTargetDistSqr() );

		float fRadius = pChar->GetRadius();

		float fRand = GetRandom( 0.f, 1.f );
		fDist -= ( fRadius * 2.f ) + ( fRand * pAI->GetAccuracyMissPerturb() );

		// Calculate a position to the right or left of the target.

		LTVector vDir = vPos - pAI->GetPosition();
		if( vDir != LTVector::GetIdentity() )
		{
			vDir.Normalize();
		}

		vPos = pAI->GetPosition() + ( vDir * fDist );

		LTVector vRight = vDir.Cross( LTVector( 0.f, 1.f, 0.f ) );

		fRand = GetRandom( 0.f, 1.f );
		float fPerturb = ( ( pAI->GetAccuracyMissPerturb() * 2.f ) * fRand ) - pAI->GetAccuracyMissPerturb();
		vRight *= fPerturb;

		// Apply the offset to miss the target.

		outvShootPos = vPos + vRight;

		// Force bullets to land in front of the target, on the floor.

		if( m_pAIWeaponRecord->bForceMissToFloor )
		{
			float fFloor = pAI->GetAIBlackBoard()->GetBBTargetPosition().y;
			fFloor -= pAI->GetAIBlackBoard()->GetBBTargetDims().y;
			outvShootPos.y = fFloor;
		}

		return false;
	}

	return false;
}