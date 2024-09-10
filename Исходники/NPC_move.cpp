qboolean NPC_MoveToGoal( qboolean tryStraight ) 
{
	float	distance;
	vec3_t	dir;

#if	AI_TIMERS
	int	startTime = GetTime(0);
#endif//	AI_TIMERS
	//If taking full body pain, don't move
	if ( PM_InKnockDown( &NPC->client->ps ) || ( ( NPC->s.legsAnim >= BOTH_PAIN1 ) && ( NPC->s.legsAnim <= BOTH_PAIN18 ) ) )
	{
		return qfalse;
	}

#ifdef __DOMINANCE_NPC__
	if (NPC->enemy 
		&& NPC->s.weapon == WP_SABER
		&& (!NPC_EnemyVisible( NPC, NPC->enemy ) || (Distance(NPC->r.currentOrigin, NPC->enemy->r.currentOrigin) > 96 || NPC->genericValue15 < level.time)))
	{
		// Enemy is visible, but out of range for lghtsaber... Move closer...
		NPC->client->ps.speed = NPCInfo->stats.runSpeed;

		if (!NPC_FollowRoutes())
		{
			//trap->Print("NPC_FollowRoutes failed!\n");
			return qfalse;
		}

		return qtrue;
	}
	else if (NPC->enemy 
		&& NPC_EnemyVisible( NPC, NPC->enemy ))
	{
		// Enemy is visible and in range, no need to move at the moment...
		return qfalse;
	}
	else if (NPC->enemy)
	{// Have an enemy that is not currently visible...
		if (NPC->s.weapon == WP_SABER
			&& (Distance(NPC->r.currentOrigin, NPC->enemy->r.currentOrigin) > 96 || NPC->genericValue15 < level.time))
		{
			if (NPC->genericValue14 < level.time)
			{
				// Give up...
				NPC->enemy = NULL;
				NPCInfo->goalEntity = NULL;
				NPC->longTermGoal = -1;
			}
		}
		else if (NPC->enemy 
			&& NPC->genericValue15 < level.time)
		{
			if (NPC->genericValue14 < level.time)
			{
				// Give up...
				NPC->enemy = NULL;
				NPCInfo->goalEntity = NULL;
				NPC->longTermGoal = -1;
			}
		}

		NPC->client->ps.speed = NPCInfo->stats.runSpeed;

		if (!NPC_FollowRoutes())
		{
			//trap->Print("NPC_FollowRoutes failed!\n");
			return qfalse;
		}

		return qtrue;
	}
	else
	{// Dominance: Use bot waypointing AI if it is available! - Unique1
		NPC->enemy = NULL;
		NPCInfo->goalEntity = NULL;

		NPC->client->ps.speed = NPCInfo->stats.walkSpeed;

		if (!NPC_FollowRoutes())
		{
			//trap->Print("NPC_FollowRoutes failed!\n");
			return qfalse;
		}

		return qtrue;
	}
#endif //__DOMINANCE_NPC__

	/*
	if( NPC->s.eFlags & EF_LOCKED_TO_WEAPON )
	{//If in an emplaced gun, never try to navigate!
		return qtrue;
	}
	*/
	//rwwFIXMEFIXME: emplaced support

	//FIXME: if can't get to goal & goal is a target (enemy), try to find a waypoint that has line of sight to target, at least?
	//Get our movement direction
#if 1
	if ( NPC_GetMoveDirectionAltRoute( dir, &distance, tryStraight ) == qfalse )
#else
	if ( NPC_GetMoveDirection( dir, &distance ) == qfalse )
#endif
		return qfalse;

	NPCInfo->distToGoal		= distance;

	//Convert the move to angles
	vectoangles( dir, NPCInfo->lastPathAngles );
	if ( (ucmd.buttons&BUTTON_WALKING) )
	{
		NPC->client->ps.speed = NPCInfo->stats.walkSpeed;
	}
	else
	{
		NPC->client->ps.speed = NPCInfo->stats.runSpeed;
	}

	//FIXME: still getting ping-ponging in certain cases... !!!  Nav/avoidance error?  WTF???!!!
	//If in combat move, then move directly towards our goal
	if ( NPC_CheckCombatMove() )
	{//keep current facing
		G_UcmdMoveForDir( NPC, &ucmd, dir );
	}
	else
	{//face our goal
		//FIXME: strafe instead of turn if change in dir is small and temporary
		NPCInfo->desiredPitch	= 0.0f;
		NPCInfo->desiredYaw		= AngleNormalize360( NPCInfo->lastPathAngles[YAW] );
		
		//Pitch towards the goal and also update if flying or swimming
		if ( (NPC->client->ps.eFlags2&EF2_FLYING) )//moveType == MT_FLYSWIM )
		{
			NPCInfo->desiredPitch = AngleNormalize360( NPCInfo->lastPathAngles[PITCH] );
			
			if ( dir[2] )
			{
				float scale = (dir[2] * distance);
				if ( scale > 64 )
				{
					scale = 64;
				}
				else if ( scale < -64 )
				{
					scale = -64;
				}
				NPC->client->ps.velocity[2] = scale;
				//NPC->client->ps.velocity[2] = (dir[2] > 0) ? 64 : -64;
			}
		}

		//Set any final info
		ucmd.forwardmove = 127;
	}

#if	AI_TIMERS
	navTime += GetTime( startTime );
#endif//	AI_TIMERS
	return qtrue;
}