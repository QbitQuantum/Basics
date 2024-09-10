/*
================
idExplodingBarrel::Killed
================
*/
void idExplodingBarrel::Killed( idEntity *inflictor, idEntity *attacker, int damage, const idVec3 &dir, int location ) {

	// This simple condition causes a barrel to explode when shot while burning
#ifdef _DENTONMOD
	if ( IsHidden() || state == EXPLODING ) {
#else
	if ( IsHidden() || state == EXPLODING || state == BURNING ) {
#endif
		return;
	}

	float f = spawnArgs.GetFloat( "burn" );

#ifdef _DENTONMOD
	int explodeHealth = spawnArgs.GetInt( "explode_health" );

	if ( f > 0.0f && state == NORMAL && health > explodeHealth ) {
#else
	if ( f > 0.0f && state == NORMAL ) {
#endif
		state = BURNING;
		PostEventSec( &EV_Explode, f );
		StartSound( "snd_burn", SND_CHANNEL_ANY, 0, false, NULL );
		AddParticles( spawnArgs.GetString ( "model_burn", "" ), true );
		return;
	} else {
		
#ifdef _DENTONMOD	
		if( state == BURNING && health > explodeHealth ) { 
			return;
		}
#endif

		state = EXPLODING;
		if ( gameLocal.isServer ) {
			idBitMsg	msg;
			byte		msgBuf[MAX_EVENT_PARAM_SIZE];

			msg.Init( msgBuf, sizeof( msgBuf ) );
			msg.WriteLong( gameLocal.time );
			ServerSendEvent( EVENT_EXPLODE, &msg, false, -1 );
		}
	}

	// do this before applying radius damage so the ent can trace to any damagable ents nearby
	Hide();
#ifdef _DENTONMOD
	BecomeInactive(TH_PHYSICS); // This causes the physics not to update after explosion
#else					
	physicsObj.SetContents( 0 ); // Set physics content 0 after spawining debris.
#endif
	
	const char *splash = spawnArgs.GetString( "def_splash_damage", "damage_explosion" );
	if ( splash && *splash ) {
		gameLocal.RadiusDamage( GetPhysics()->GetOrigin(), this, attacker, this, this, splash );
	}

	ExplodingEffects( );

	//FIXME: need to precache all the debris stuff here and in the projectiles
	const idKeyValue *kv = spawnArgs.MatchPrefix( "def_debris" );
	// bool first = true;
	while ( kv ) {
		const idDict *debris_args = gameLocal.FindEntityDefDict( kv->GetValue(), false );
		if ( debris_args ) {
			idEntity *ent;
			idVec3 dir;
			idDebris *debris;
			//if ( first ) {
				dir = physicsObj.GetAxis()[1];
			//	first = false;
			//} else {
				dir.x += gameLocal.random.CRandomFloat() * 4.0f;
				dir.y += gameLocal.random.CRandomFloat() * 4.0f;
				//dir.z = gameLocal.random.RandomFloat() * 8.0f;
			//}
			dir.Normalize();

			gameLocal.SpawnEntityDef( *debris_args, &ent, false );
			if ( !ent || !ent->IsType( idDebris::Type ) ) {
				gameLocal.Error( "'projectile_debris' is not an idDebris" );
			}

			debris = static_cast<idDebris *>(ent);
			debris->Create( this, physicsObj.GetOrigin(), dir.ToMat3() );
			debris->Launch();
			debris->GetRenderEntity()->shaderParms[ SHADERPARM_TIME_OF_DEATH ] = ( gameLocal.time + 1500 ) * 0.001f;
			debris->UpdateVisuals();

		}
		kv = spawnArgs.MatchPrefix( "def_debris", kv );
	}
	
	SpawnDrops(); //ivan

#ifdef _DENTONMOD
	physicsObj.SetContents( 0 );
#endif

	physicsObj.PutToRest();

	CancelEvents( &EV_Explode );
	CancelEvents( &EV_Activate );

	f = spawnArgs.GetFloat( "respawn" );
	if ( f > 0.0f ) {
		PostEventSec( &EV_Respawn, f );
	} else {
		PostEventMS( &EV_Remove, 5000 );
	}

	if ( spawnArgs.GetBool( "triggerTargets" ) ) {
		ActivateTargets( this );
	}

	//ivan start - add score only if player is the killer
	if ( attacker && attacker->IsType( idPlayer::Type ) ) {
		static_cast< idPlayer* >( attacker )->AddScore( spawnArgs.GetInt( "score", "100" ) ); 
	}
	//ivan end
}

/*
================
idExplodingBarrel::Damage
================
*/
void idExplodingBarrel::Damage( idEntity *inflictor, idEntity *attacker, const idVec3 &dir,
					  const char *damageDefName, const float damageScale, const int location ) {

	const idDict *damageDef = gameLocal.FindEntityDefDict( damageDefName );
	if ( !damageDef ) {
		gameLocal.Error( "Unknown damageDef '%s'\n", damageDefName );
	}
#ifdef _DENTONMOD		// Following condition means, if inflictor's got a radius damage then explode immediately, 
						// which could cause explosions when barrel's health is greater than 0 so I am disabling it.
#else
	if ( damageDef->FindKey( "radius" ) && GetPhysics()->GetContents() != 0 && GetBindMaster() == NULL ) {
		PostEventMS( &EV_Explode, 400 );
	} else {
#endif
		idEntity::Damage( inflictor, attacker, dir, damageDefName, damageScale, location );
#ifdef _DENTONMOD	
#else
	}
#endif
}

/*
================
idExplodingBarrel::Event_TriggerTargets
================
*/
void idExplodingBarrel::Event_TriggerTargets() {
	ActivateTargets( this );
}

/*
================
idExplodingBarrel::Event_Explode
================
*/
void idExplodingBarrel::Event_Explode() {
	if ( state == NORMAL || state == BURNING ) {
		state = BURNEXPIRED;
		Killed( NULL, NULL, 0, vec3_zero, 0 );
	}
}

/*
================
idExplodingBarrel::Event_Respawn
================
*/
void idExplodingBarrel::Event_Respawn() {
	int i;
	int minRespawnDist = spawnArgs.GetInt( "respawn_range", "256" );
	if ( minRespawnDist ) {
		float minDist = -1;
		for ( i = 0; i < gameLocal.numClients; i++ ) {
			if ( !gameLocal.entities[ i ] || !gameLocal.entities[ i ]->IsType( idPlayer::Type ) ) {
				continue;
			}
			idVec3 v = gameLocal.entities[ i ]->GetPhysics()->GetOrigin() - GetPhysics()->GetOrigin();
			float dist = v.Length();
			if ( minDist < 0 || dist < minDist ) {
				minDist = dist;
			}
		}
		if ( minDist < minRespawnDist ) {
			PostEventSec( &EV_Respawn, spawnArgs.GetInt( "respawn_again", "10" ) );
			return;
		}
	}
	const char *temp = spawnArgs.GetString( "model" );
	if ( temp && *temp ) {
		SetModel( temp );
	}
	health = spawnArgs.GetInt( "health", "5" );
	fl.takedamage = true;
	physicsObj.SetOrigin( spawnOrigin );
	physicsObj.SetAxis( spawnAxis );
	physicsObj.SetContents( CONTENTS_SOLID );
	physicsObj.DropToFloor();
	state = NORMAL;
	Show();
	UpdateVisuals();
}