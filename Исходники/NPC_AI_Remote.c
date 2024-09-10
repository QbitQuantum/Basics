/*
-------------------------
Remote_MaintainHeight
-------------------------
*/
void Remote_MaintainHeight( void )
{	
	float	dif;

	// Update our angles regardless
	NPC_UpdateAngles( qtrue, qtrue );

	if ( NPC->client->ps.velocity[2] )
	{
		NPC->client->ps.velocity[2] *= VELOCITY_DECAY;

		if ( fabs( NPC->client->ps.velocity[2] ) < 2 )
		{
			NPC->client->ps.velocity[2] = 0;
		}
	}
	// If we have an enemy, we should try to hover at or a little below enemy eye level
	if ( NPC->enemy )
	{
		if (TIMER_Done( NPC, "heightChange"))
		{
			TIMER_Set( NPC,"heightChange",Q_irand( 1000, 3000 ));

			// Find the height difference
			dif = (NPC->enemy->r.currentOrigin[2] +  Q_irand( 0, NPC->enemy->r.maxs[2]+8 )) - NPC->r.currentOrigin[2]; 

			// cap to prevent dramatic height shifts
			if ( fabs( dif ) > 2 )
			{
				if ( fabs( dif ) > 24 )
				{
					dif = ( dif < 0 ? -24 : 24 );
				}
				dif *= 10;
				NPC->client->ps.velocity[2] = (NPC->client->ps.velocity[2]+dif)/2;
				G_Sound( NPC, CHAN_AUTO, G_SoundIndex("sound/chars/remote/misc/hiss.wav"));
			}
		}
	}
	else
	{
		gentity_t *goal = NULL;

		if ( NPCInfo->goalEntity )	// Is there a goal?
		{
			goal = NPCInfo->goalEntity;
		}
		else
		{
			goal = NPCInfo->lastGoalEntity;
		}
		if ( goal )
		{
			dif = goal->r.currentOrigin[2] - NPC->r.currentOrigin[2];

			if ( fabs( dif ) > 24 )
			{
				dif = ( dif < 0 ? -24 : 24 );
				NPC->client->ps.velocity[2] = (NPC->client->ps.velocity[2]+dif)/2;
			}
		}
	}

	// Apply friction
	if ( NPC->client->ps.velocity[0] )
	{
		NPC->client->ps.velocity[0] *= VELOCITY_DECAY;

		if ( fabs( NPC->client->ps.velocity[0] ) < 1 )
		{
			NPC->client->ps.velocity[0] = 0;
		}
	}

	if ( NPC->client->ps.velocity[1] )
	{
		NPC->client->ps.velocity[1] *= VELOCITY_DECAY;

		if ( fabs( NPC->client->ps.velocity[1] ) < 1 )
		{
			NPC->client->ps.velocity[1] = 0;
		}
	}
}