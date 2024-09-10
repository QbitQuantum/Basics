int Team_TouchOurFlag( gentity_t *ent, gentity_t *other, int team ) {
	int			i, num, j, enemyTeam;
	gentity_t	*player;
	gclient_t	*cl = other->client;
	int			enemy_flag;
	vec3_t		mins, maxs;
	int			touch[MAX_GENTITIES];
	gentity_t*	enemy;
	float		enemyDist, dist;

	if (cl->sess.sessionTeam == TEAM_RED) {
		enemy_flag = PW_BLUEFLAG;
	} else {
		enemy_flag = PW_REDFLAG;
	}

	if ( ent->flags & FL_DROPPED_ITEM ) {
		// hey, its not home.  return it by teleporting it back
		//PrintMsg( NULL, "%s" S_COLOR_WHITE " returned the %s flag!\n",
		//	cl->pers.netname, TeamName(team));
		PrintCTFMessage(other->s.number, team, CTFMESSAGE_PLAYER_RETURNED_FLAG);

		AddScore(other, ent->r.currentOrigin, CTF_RECOVERY_BONUS);
		other->client->pers.teamState.flagrecovery++;
		other->client->pers.teamState.lastreturnedflag = level.time;
		//ResetFlag will remove this entity!  We must return zero
		Team_ReturnFlagSound(Team_ResetFlag(team), team);
		return 0;
	}

	// the flag is at home base.  if the player has the enemy
	// flag, he's just won!
	if (!cl->ps.powerups[enemy_flag])
		return 0; // We don't have the flag

	// fix: captures after timelimit hit could
	// cause game ending with tied score
	if (level.intermissionQueued)
		return 0;

	// check for enemy closer to grab the flag
	VectorSubtract( ent->s.pos.trBase, minFlagRange, mins );
	VectorAdd( ent->s.pos.trBase, maxFlagRange, maxs );

	num = trap->EntitiesInBox( mins, maxs, touch, MAX_GENTITIES );

	dist = Distance( ent->s.pos.trBase, other->client->ps.origin );

	if (other->client->sess.sessionTeam == TEAM_RED)
		enemyTeam = TEAM_BLUE;
	else
		enemyTeam = TEAM_RED;

	for (j = 0; j < num; j++) {
		enemy = (g_entities + touch[j]);

		if (!enemy || !enemy->inuse || !enemy->client)
			continue;

		if (enemy->client->pers.connected != CON_CONNECTED)
			continue;

		//check if its alive
		if (enemy->health < 1)
			continue;		// dead people can't pickup

		//ignore specs
		if (enemy->client->sess.sessionTeam == TEAM_SPECTATOR)
			continue;

		//check if this is enemy
		if ((enemy->client->sess.sessionTeam != TEAM_RED && enemy->client->sess.sessionTeam != TEAM_BLUE) ||
			enemy->client->sess.sessionTeam != enemyTeam){
			continue;
		}

		//check if enemy is closer to our flag than us
		enemyDist = Distance(ent->s.pos.trBase, enemy->client->ps.origin);
		if (enemyDist < dist) {
			// possible recursion is hidden in this, but
			// infinite recursion wont happen, because we cant
			// have a < b and b < a at the same time
			return Team_TouchEnemyFlag( ent, enemy, team );
		}
	}

	//PrintMsg( NULL, "%s" S_COLOR_WHITE " captured the %s flag!\n", cl->pers.netname, TeamName(OtherTeam(team)));
	PrintCTFMessage(other->s.number, team, CTFMESSAGE_PLAYER_CAPTURED_FLAG);

	cl->ps.powerups[enemy_flag] = 0;

	teamgame.last_flag_capture = level.time;
	teamgame.last_capture_team = team;

	// Increase the team's score
	AddTeamScore(ent->s.pos.trBase, other->client->sess.sessionTeam, 1);

	other->client->pers.teamState.captures++;
	other->client->rewardTime = level.time + REWARD_SPRITE_TIME;
	other->client->ps.persistant[PERS_CAPTURES]++;

	// other gets another 10 frag bonus
	AddScore(other, ent->r.currentOrigin, CTF_CAPTURE_BONUS);

	Team_CaptureFlagSound( ent, team );

	// Ok, let's do the player loop, hand out the bonuses
	for (i = 0; i < sv_maxclients.integer; i++) {
		player = &g_entities[i];
		if (!player->inuse || player == other)
			continue;

		if (player->client->sess.sessionTeam !=
			cl->sess.sessionTeam) {
			player->client->pers.teamState.lasthurtcarrier = -5;
		} else if (player->client->sess.sessionTeam ==
			cl->sess.sessionTeam) {
			AddScore(player, ent->r.currentOrigin, CTF_TEAM_BONUS);
			// award extra points for capture assists
			if (player->client->pers.teamState.lastreturnedflag +
				CTF_RETURN_FLAG_ASSIST_TIMEOUT > level.time) {
				AddScore (player, ent->r.currentOrigin, CTF_RETURN_FLAG_ASSIST_BONUS);
				other->client->pers.teamState.assists++;

				player->client->ps.persistant[PERS_ASSIST_COUNT]++;
				player->client->rewardTime = level.time + REWARD_SPRITE_TIME;

			}
			if (player->client->pers.teamState.lastfraggedcarrier +
				CTF_FRAG_CARRIER_ASSIST_TIMEOUT > level.time) {
				AddScore(player, ent->r.currentOrigin, CTF_FRAG_CARRIER_ASSIST_BONUS);
				other->client->pers.teamState.assists++;
				player->client->ps.persistant[PERS_ASSIST_COUNT]++;
				player->client->rewardTime = level.time + REWARD_SPRITE_TIME;
			}
		}
		//[EXPsys]
		if (g_experianceEnabled.integer)
		{
			if ((player->client->sess.sessionTeam == cl->sess.sessionTeam)) {
				GiveExperiance(player, g_experianceWinRound.integer);
			}
			else
			{
				GiveExperiance(player, g_experianceLoseRound.integer);
			}
		}
	}//[/EXPsys]
	Team_ResetFlags();

	CalculateRanks();

	return 0; // Do not respawn this automatically
}