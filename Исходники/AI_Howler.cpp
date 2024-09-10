/*
-------------------------
NPC_BSHowler_Default
-------------------------
*/
void NPC_BSHowler_Default( void )
{
	if ( NPC->client->ps.legsAnim != BOTH_GESTURE1 )
	{
		NPC->count = 0;
	}
	//FIXME: if in jump, do damage in front and maybe knock them down?
	if ( !TIMER_Done( NPC, "attacking" ) )
	{
		if ( NPC->enemy )
		{
			//NPC_FaceEnemy( qfalse );
			Howler_Attack( Distance( NPC->enemy->currentOrigin, NPC->currentOrigin ) );
		}
		else
		{
			//NPC_UpdateAngles( qfalse, qtrue );
			Howler_Attack( 0.0f );
		}
		NPC_UpdateAngles( qfalse, qtrue );
		return;
	}

	if ( NPC->enemy )
	{
		if ( NPCInfo->stats.aggression > 0 )
		{
			if ( TIMER_Done( NPC, "aggressionDecay" ) )
			{
				NPCInfo->stats.aggression--;
				TIMER_Set( NPC, "aggressionDecay", 500 );
			}
		}
		if ( !TIMER_Done( NPC, "flee" ) 
			&& NPC_BSFlee() )	//this can clear ENEMY
		{//successfully trying to run away
			return;
		}
		if ( NPC->enemy == NULL)
		{
			NPC_UpdateAngles( qfalse, qtrue );
			return;
		}
		if ( NPCInfo->localState == LSTATE_FLEE )
		{//we were fleeing, now done (either timer ran out or we cannot flee anymore
			if ( NPC_ClearLOS( NPC->enemy ) )
			{//if enemy is still around, go berzerk
				NPCInfo->localState = LSTATE_BERZERK;
			}
			else
			{//otherwise, lick our wounds?
				NPCInfo->localState = LSTATE_CLEAR;
				TIMER_Set( NPC, "standing", Q_irand( 3000, 10000 ) );
			}
		}
		else if ( NPCInfo->localState == LSTATE_BERZERK )
		{//go nuts!
		}
		else if ( NPCInfo->stats.aggression >= Q_irand( 75, 125 ) )
		{//that's it, go nuts!
			NPCInfo->localState = LSTATE_BERZERK;
		}
		else if ( !TIMER_Done( NPC, "retreating" ) )
		{//trying to back off
			NPC_FaceEnemy( qtrue );
			if ( NPC->client->ps.speed > NPCInfo->stats.walkSpeed )
			{
				NPC->client->ps.speed = NPCInfo->stats.walkSpeed;
			}
			ucmd.buttons |= BUTTON_WALKING;
			if ( Distance( NPC->enemy->currentOrigin, NPC->currentOrigin ) < HOWLER_RETREAT_DIST )
			{//enemy is close
				vec3_t moveDir;
				AngleVectors( NPC->currentAngles, moveDir, NULL, NULL );
				VectorScale( moveDir, -1, moveDir );
				if ( !NAV_DirSafe( NPC, moveDir, 8 ) )
				{//enemy is backing me up against a wall or ledge!  Start to get really mad!
					NPCInfo->stats.aggression += 2;
				}
				else
				{//back off
					ucmd.forwardmove = -127;
				}
				//enemy won't leave me alone, get mad...
				NPCInfo->stats.aggression++;
			}
			return;
		}
		else if ( TIMER_Done( NPC, "standing" ) )
		{//not standing around
			if ( !(NPCInfo->last_ucmd.forwardmove)
				&& !(NPCInfo->last_ucmd.rightmove) )
			{//stood last frame
				if ( TIMER_Done( NPC, "walking" ) 
					&& TIMER_Done( NPC, "running" ) )
				{//not walking or running
					if ( Q_irand( 0, 2 ) )
					{//run for a while
						TIMER_Set( NPC, "walking", Q_irand( 4000, 8000 ) );
					}
					else
					{//walk for a bit
						TIMER_Set( NPC, "running", Q_irand( 2500, 5000 ) );
					}
				}
			}
			else if ( (NPCInfo->last_ucmd.buttons&BUTTON_WALKING) )
			{//walked last frame
				if ( TIMER_Done( NPC, "walking" ) )
				{//just finished walking
					if ( Q_irand( 0, 5 ) || DistanceSquared( NPC->enemy->currentOrigin, NPC->currentOrigin ) < MAX_DISTANCE_SQR )
					{//run for a while
						TIMER_Set( NPC, "running", Q_irand( 4000, 20000 ) );
					}
					else
					{//stand for a bit
						TIMER_Set( NPC, "standing", Q_irand( 2000, 6000 ) );
					}
				}
			}
			else
			{//ran last frame
				if ( TIMER_Done( NPC, "running" ) )
				{//just finished running
					if ( Q_irand( 0, 8 ) || DistanceSquared( NPC->enemy->currentOrigin, NPC->currentOrigin ) < MAX_DISTANCE_SQR )
					{//walk for a while
						TIMER_Set( NPC, "walking", Q_irand( 3000, 10000 ) );
					}
					else
					{//stand for a bit
						TIMER_Set( NPC, "standing", Q_irand( 2000, 6000 ) );
					}
				}
			}
		}
		if ( NPC_ValidEnemy( NPC->enemy ) == qfalse )
		{
			TIMER_Remove( NPC, "lookForNewEnemy" );//make them look again right now
			if ( !NPC->enemy->inuse || level.time - NPC->enemy->s.time > Q_irand( 10000, 15000 ) )
			{//it's been a while since the enemy died, or enemy is completely gone, get bored with him
				NPC->enemy = NULL;
				Howler_Patrol();
				NPC_UpdateAngles( qtrue, qtrue );
				return;
			}
		}
		if ( TIMER_Done( NPC, "lookForNewEnemy" ) )
		{
			gentity_t *sav_enemy = NPC->enemy;//FIXME: what about NPC->lastEnemy?
			NPC->enemy = NULL;
			gentity_t *newEnemy = NPC_CheckEnemy( NPCInfo->confusionTime < level.time, qfalse, qfalse );
			NPC->enemy = sav_enemy;
			if ( newEnemy && newEnemy != sav_enemy )
			{//picked up a new enemy!
				NPC->lastEnemy = NPC->enemy;
				G_SetEnemy( NPC, newEnemy );
				if ( NPC->enemy != NPC->lastEnemy )
				{//clear this so that we only sniff the player the first time we pick them up
					NPC->useDebounceTime = 0;
				}
				//hold this one for at least 5-15 seconds
				TIMER_Set( NPC, "lookForNewEnemy", Q_irand( 5000, 15000 ) );
			}
			else
			{//look again in 2-5 secs
				TIMER_Set( NPC, "lookForNewEnemy", Q_irand( 2000, 5000 ) );
			}
		}
		Howler_Combat();
		if ( TIMER_Done( NPC, "speaking" ) )
		{
			if ( !TIMER_Done( NPC, "standing" )
				|| !TIMER_Done( NPC, "retreating" ))
			{
				G_SoundOnEnt( NPC, CHAN_VOICE, va( "sound/chars/howler/idle_hiss%d.mp3", Q_irand( 1, 2 ) ) );
			}
			else if ( !TIMER_Done( NPC, "walking" ) 
				|| NPCInfo->localState == LSTATE_FLEE )
			{
				G_SoundOnEnt( NPC, CHAN_VOICE, va( "sound/chars/howler/howl_talk%d.mp3", Q_irand( 1, 5 ) ) );
			}
			else
			{
				G_SoundOnEnt( NPC, CHAN_VOICE, va( "sound/chars/howler/howl_yell%d.mp3", Q_irand( 1, 5 ) ) );
			}
			if ( NPCInfo->localState == LSTATE_BERZERK
				|| NPCInfo->localState == LSTATE_FLEE )
			{
				TIMER_Set( NPC, "speaking", Q_irand( 1000, 4000 ) );
			}
			else
			{
				TIMER_Set( NPC, "speaking", Q_irand( 3000, 8000 ) );
			}
		}
		return;
	}
	else
	{
		if ( TIMER_Done( NPC, "speaking" ) )
		{
			if ( !Q_irand( 0, 3 ) )
			{
				G_SoundOnEnt( NPC, CHAN_VOICE, va( "sound/chars/howler/idle_hiss%d.mp3", Q_irand( 1, 2 ) ) );
			}
			else
			{
				G_SoundOnEnt( NPC, CHAN_VOICE, va( "sound/chars/howler/howl_talk%d.mp3", Q_irand( 1, 5 ) ) );
			}
			TIMER_Set( NPC, "speaking", Q_irand( 4000, 12000 ) );
		}
		if ( NPCInfo->stats.aggression > 0 )
		{
			if ( TIMER_Done( NPC, "aggressionDecay" ) )
			{
				NPCInfo->stats.aggression--;
				TIMER_Set( NPC, "aggressionDecay", 200 );
			}
		}
		if ( TIMER_Done( NPC, "standing" ) )
		{//not standing around
			if ( !(NPCInfo->last_ucmd.forwardmove)
				&& !(NPCInfo->last_ucmd.rightmove) )
			{//stood last frame
				if ( TIMER_Done( NPC, "walking" ) 
					&& TIMER_Done( NPC, "running" ) )
				{//not walking or running
					if ( NPCInfo->goalEntity )
					{//have somewhere to go
						if ( Q_irand( 0, 2 ) )
						{//walk for a while
							TIMER_Set( NPC, "walking", Q_irand( 3000, 10000 ) );
						}
						else
						{//run for a bit
							TIMER_Set( NPC, "running", Q_irand( 2500, 5000 ) );
						}
					}
				}
			}
			else if ( (NPCInfo->last_ucmd.buttons&BUTTON_WALKING) )
			{//walked last frame
				if ( TIMER_Done( NPC, "walking" ) )
				{//just finished walking
					if ( Q_irand( 0, 3 ) )
					{//run for a while
						TIMER_Set( NPC, "running", Q_irand( 3000, 6000 ) );
					}
					else
					{//stand for a bit
						TIMER_Set( NPC, "standing", Q_irand( 2500, 5000 ) );
					}
				}
			}
			else
			{//ran last frame
				if ( TIMER_Done( NPC, "running" ) )
				{//just finished running
					if ( Q_irand( 0, 2 ) )
					{//walk for a while
						TIMER_Set( NPC, "walking", Q_irand( 6000, 15000 ) );
					}
					else
					{//stand for a bit
						TIMER_Set( NPC, "standing", Q_irand( 4000, 6000 ) );
					}
				}
			}
		}
		if ( NPCInfo->scriptFlags & SCF_LOOK_FOR_ENEMIES )
		{
			Howler_Patrol();
		}
		else
		{
			Howler_Idle();
		}
	}

	NPC_UpdateAngles( qfalse, qtrue );
}