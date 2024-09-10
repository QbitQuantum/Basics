void DoClientThinks( gentity_t *ent ) {
	int lastCmd, lastTime;
	int latestTime;
	int drop_threshold = LAG_MAX_DROP_THRESHOLD;
	int startPackets = ent->client->cmdcount;

	if ( ent->client->cmdcount <= 0 )
		return;

	// allow some more movement if time has passed
	latestTime = trap_Milliseconds();
	if ( ent->client->lastCmdRealTime > latestTime ) {
		// zinx - stoopid server went backwards in time, reset the delta
		// instead of giving them even -less- movement ability
		ent->client->cmddelta = 0;
	} else {
		ent->client->cmddelta -= (latestTime - ent->client->lastCmdRealTime);
	}
	if ( ent->client->cmdcount <= 1 && ent->client->cmddelta < 0 )
		ent->client->cmddelta = 0;
	ent->client->lastCmdRealTime = latestTime;

	lastCmd = (ent->client->cmdhead + ent->client->cmdcount - 1) % LAG_MAX_COMMANDS;

	lastTime = ent->client->ps.commandTime;
	latestTime = ent->client->cmds[lastCmd].serverTime;

	while ( ent->client->cmdcount > 0 ) {
		usercmd_t *cmd = &ent->client->cmds[ent->client->cmdhead];
		float speed, delta, scale;
		int savedTime;
		qboolean deltahax = qfalse;

		int serverTime = cmd->serverTime;
		int totalDelta = latestTime - cmd->serverTime;
		int timeDelta;

		if ( ent->client->pers.pmoveFixed ) {
			serverTime = ((serverTime + pmove_msec.integer-1) / pmove_msec.integer) * pmove_msec.integer;
		}

		timeDelta = serverTime - lastTime;

		if ( totalDelta >= drop_threshold ) {
			// zinx - whoops. too lagged.
			drop_threshold = LAG_MIN_DROP_THRESHOLD;
			lastTime = ent->client->ps.commandTime = cmd->serverTime;
			goto drop_packet;
		}

		if ( totalDelta < 0 ) {
			// zinx - oro? packet from the future
			goto drop_packet;
		}
		
		if ( timeDelta <= 0 ) {
			// zinx - packet from the past
			goto drop_packet;
		}

		scale = 1.f / LAG_DECAY;

		speed = G_CmdScale( ent, cmd );
		delta = (speed * (float)timeDelta);
		delta *= scale;

		if ( timeDelta > 50 ) {
			timeDelta = 50;
			delta = (speed * (float)timeDelta);
			delta *= scale;
			deltahax = qtrue;
		}

		if ( (ent->client->cmddelta + delta) >= LAG_MAX_DELTA ) {
			// too many commands this server frame

			// if it'll fit in the next frame, just wait until then.
			if ( delta < LAG_MAX_DELTA
			 && (totalDelta + delta) < LAG_MIN_DROP_THRESHOLD )
				break;

			// try to split it up in to smaller commands

			delta = ((float)LAG_MAX_DELTA - ent->client->cmddelta);
			timeDelta = ceil(delta / speed); // prefer speedup
			delta = (float)timeDelta * speed;

			if ( timeDelta < 1 )
				break;

			delta *= scale;
			deltahax = qtrue;
		}

		ent->client->cmddelta += delta;

		if ( deltahax ) {
			savedTime = cmd->serverTime;
			cmd->serverTime = lastTime + timeDelta;
		} else {
			savedTime = 0;	// zinx - shut up compiler
		}

		// zinx - erh.  hack, really. make it run for the proper amount of time.
		ent->client->ps.commandTime = lastTime;
		ClientThink_cmd( ent , cmd );
		lastTime = ent->client->ps.commandTime;

		if ( deltahax ) {
			cmd->serverTime = savedTime;

			if ( delta <= 0.1f )
				break;

			continue;
		}

	  drop_packet:
		if ( ent->client->cmdcount <= 0 ) {
			// ent->client was cleared...
			break;
		}

		ent->client->cmdhead = (ent->client->cmdhead + 1) % LAG_MAX_COMMANDS;
		ent->client->cmdcount--;
		continue;
	}

	// zinx - added ping, packets processed this frame
	// warning: eats bandwidth like popcorn
	if ( g_antiwarp.integer & 32 ) {
		trap_SendServerCommand(
			ent - g_entities,
			va( "cp \"%d %d\n\"", latestTime - lastTime, startPackets - ent->client->cmdcount )
		);
	}

	// zinx - debug; size is added lag (amount above player's network lag)
	// rotation is time
	if ( (g_antiwarp.integer & 16) && ent->client->cmdcount ) {
		vec3_t org, parms;

		VectorCopy( ent->client->ps.origin, org );
		SnapVector( org );

		parms[0] = 3;
		parms[1] = (float)(latestTime - ent->client->ps.commandTime) / 10.f;
		if (parms[1] < 1.f) parms[1] = 1.f;
		parms[2] = (ent->client->ps.commandTime * 180.f) / 1000.f;

		//etpro_AddDebugLine( org, parms, ((ent - g_entities) % 32), LINEMODE_SPOKES, LINESHADER_RAILCORE, 0, qfalse );
	}
	
	//ent->client->ps.stats[STAT_ANTIWARP_DELAY] = latestTime - ent->client->ps.commandTime;
	//if (ent->client->ps.stats[STAT_ANTIWARP_DELAY] < 0)
	//	ent->client->ps.stats[STAT_ANTIWARP_DELAY] = 0;
}