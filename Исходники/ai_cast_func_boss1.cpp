const char *AIFunc_Heinrich_Earthquake( cast_state_t *cs ) {
	gentity_t   *ent = &g_entities[cs->entityNum];
	gentity_t   *enemy;
	cast_state_t *ecs;
	vec3_t enemyVec;
	float enemyDist, scale;
	trace_t *tr;

	cs->aiFlags |= AIFL_SPECIAL_FUNC;

	if ( cs->enemyNum < 0 ) {
		if ( !ent->client->ps.torsoTimer ) {
			return AIFunc_DefaultStart( cs );
		}
		return NULL;
	}

	enemy = &g_entities[cs->enemyNum];
	ecs = AICast_GetCastState( cs->enemyNum );

	VectorMA( enemy->r.currentOrigin, HEINRICH_STOMP_DELAY, enemy->client->ps.velocity, enemyVec );
	enemyDist = VectorDistance( ent->r.currentOrigin, enemyVec );

	if ( ent->client->ps.torsoTimer < 500 ) {
		int rnd;
		aicast_predictmove_t move;
		vec3_t vec;

		AICast_PredictMovement( ecs, 2, 0.5, &move, &g_entities[cs->enemyNum].client->pers.cmd, -1 );
		VectorSubtract( move.endpos, cs->bs->origin, vec );
		vec[2] = 0;
		enemyDist = VectorLength( vec );
		enemyDist -= g_entities[cs->enemyNum].r.maxs[0];
		enemyDist -= ent->r.maxs[0];
		//
		if ( enemyDist < 140 ) {
			// combo attack
			rnd = rand() % 3;
			switch ( rnd ) {
			case 0:
				return AIFunc_Heinrich_SwordSideSlashStart( cs );
			case 1:
				return AIFunc_Heinrich_SwordKnockbackStart( cs );
			case 2:
				return AIFunc_Heinrich_SwordLungeStart( cs );
			}
		} else {    // back to roaming
			ent->client->ps.legsTimer = 0;
			ent->client->ps.torsoTimer = 0;
			cs->castScriptStatus.scriptNoMoveTime = 0;
			AICast_Heinrich_Taunt( cs );
			return AIFunc_DefaultStart( cs );
		}
	}

	// time for the thump?
	if ( !( cs->aiFlags & AIFL_MISCFLAG1 ) ) {
		// face them
		AICast_AimAtEnemy( cs );
		// ready for damage?
		if ( cs->thinkFuncChangeTime < level.time - HEINRICH_STOMP_DELAY ) {
			cs->aiFlags |= AIFL_MISCFLAG1;
			// play the stomp sound
			G_AddEvent( ent, EV_GENERAL_SOUND, G_SoundIndex( aiDefaults[ent->aiCharacter].soundScripts[ORDERSDENYSOUNDSCRIPT] ) );
			// check for striking the player
			tr = CheckMeleeAttack( ent, 70, qfalse );
			// do melee damage
			if ( tr && ( tr->entityNum == cs->enemyNum ) ) {
				G_Damage( &g_entities[tr->entityNum], ent, ent, vec3_origin, tr->endpos, HEINRICH_STOMP_DAMAGE, 0, MOD_GAUNTLET );
			}
			// call the debris trigger
			AICast_ScriptEvent( cs, "trigger", "quake" );
		}
	}

	enemyDist = Distance( enemy->s.pos.trBase, ent->s.pos.trBase );

	// do the earthquake effects
	if ( cs->thinkFuncChangeTime < level.time - HEINRICH_STOMP_DELAY ) {
		// throw the player into the air, if they are on the ground
		if ( ( enemy->s.groundEntityNum != ENTITYNUM_NONE ) && enemyDist < HEINRICH_STOMP_RANGE ) {
			scale = 0.5 + 0.5 * ( (float)ent->client->ps.torsoTimer / 1000.0 );
			if ( scale > 1.0 ) {
				scale = 1.0;
			}
			VectorSubtract( ent->s.pos.trBase, enemy->s.pos.trBase, enemyVec );
			VectorScale( enemyVec, 2.0 * ( 0.6 + 0.5 * random() ) * scale * ( 0.6 + 0.6 * ( 1.0 - ( enemyDist / HEINRICH_STOMP_RANGE ) ) ), enemyVec );
			enemyVec[2] = scale * HEINRICH_STOMP_VELOCITY_Z * ( 1.0 - 0.5 * ( enemyDist / HEINRICH_STOMP_RANGE ) );
			// bounce the player using this velocity
			VectorAdd( enemy->client->ps.velocity, enemyVec, enemy->client->ps.velocity );
		}
	}

	return NULL;
}