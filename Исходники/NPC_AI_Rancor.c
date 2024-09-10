//----------------------------------
void Rancor_Combat( void )
{
	if ( NPC->count )
	{//holding my enemy
		if ( TIMER_Done2( NPC, "takingPain", qtrue ))
		{
			NPCInfo->localState = LSTATE_CLEAR;
		}
		else
		{
			Rancor_Attack( 0, qfalse );
		}
		NPC_UpdateAngles( qtrue, qtrue );
		return;
	}
	// If we cannot see our target or we have somewhere to go, then do that
	if ( !NPC_ClearLOS4( NPC->enemy ) )//|| UpdateGoal( ))
	{
		NPCInfo->combatMove = qtrue;
		NPCInfo->goalEntity = NPC->enemy;
		NPCInfo->goalRadius = MIN_DISTANCE;//MAX_DISTANCE;	// just get us within combat range

		if ( !NPC_MoveToGoal( qtrue ) )
		{//couldn't go after him?  Look for a new one
			TIMER_Set( NPC, "lookForNewEnemy", 0 );
			NPCInfo->consecutiveBlockedMoves++;
		}
		else 
		{
			NPCInfo->consecutiveBlockedMoves = 0;
		}
		return;
	}

	// Sometimes I have problems with facing the enemy I'm attacking, so force the issue so I don't look dumb
	NPC_FaceEnemy( qtrue );

	{
		float	distance;
		qboolean	advance;
		qboolean	doCharge;

		distance	= Distance( NPC->r.currentOrigin, NPC->enemy->r.currentOrigin );	
		advance = (qboolean)( distance > (NPC->r.maxs[0]+MIN_DISTANCE) ? qtrue : qfalse  );
		doCharge = qfalse;

		if ( advance )
		{//have to get closer
			vec3_t	yawOnlyAngles;
			VectorSet( yawOnlyAngles, 0, NPC->r.currentAngles[YAW], 0 );
			if ( NPC->enemy->health > 0
				&& fabs(distance-250) <= 80 
				&& InFOV3( NPC->enemy->r.currentOrigin, NPC->r.currentOrigin, yawOnlyAngles, 30, 30 ) )
			{
				if ( !Q_irand( 0, 9 ) )
				{//go for the charge
					doCharge = qtrue;
					advance = qfalse;
				}
			}
		}

		if (( advance /*|| NPCInfo->localState == LSTATE_WAITING*/ ) && TIMER_Done( NPC, "attacking" )) // waiting monsters can't attack
		{
			if ( TIMER_Done2( NPC, "takingPain", qtrue ))
			{
				NPCInfo->localState = LSTATE_CLEAR;
			}
			else
			{
				Rancor_Move( 1 );
			}
		}
		else
		{
			Rancor_Attack( distance, doCharge );
		}
	}
}