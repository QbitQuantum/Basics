void AvoidPushawayProps( CBaseCombatCharacter *pPlayer, CUserCmd *pCmd )
{
	// Figure out what direction we're moving and the extents of the box we're going to sweep 
	// against physics objects.
	Vector currentdir;
	Vector rightdir;
	AngleVectors( pCmd->viewangles, &currentdir, &rightdir, NULL );

	CBaseEntity *props[512];
#ifdef CLIENT_DLL
	int nEnts = GetPushawayEnts( pPlayer, props, ARRAYSIZE( props ), 0.0f, PARTITION_CLIENT_SOLID_EDICTS, NULL );
#else
	int nEnts = GetPushawayEnts( pPlayer, props, ARRAYSIZE( props ), 0.0f, PARTITION_ENGINE_SOLID_EDICTS, NULL );
#endif

	const Vector & ourCenter = pPlayer->WorldSpaceCenter();
	Vector nearestPropPoint;
	Vector nearestPlayerPoint;

	for ( int i=0; i < nEnts; i++ )
	{
		// Don't respond to this entity on the client unless it has PHYSICS_MULTIPLAYER_FULL set.
		IMultiplayerPhysics *pInterface = dynamic_cast<IMultiplayerPhysics*>( props[i] );
		if ( pInterface && pInterface->GetMultiplayerPhysicsMode() != PHYSICS_MULTIPLAYER_SOLID )
			continue;

		const float minMass = 10.0f; // minimum mass that can push a player back
		const float maxMass = 30.0f; // cap at a decently large value
		float mass = maxMass;
		if ( pInterface )
		{
			mass = pInterface->GetMass();
		}
		mass = clamp( mass, minMass, maxMass );
		
		mass = max( mass, 0 );
		mass /= maxMass; // bring into a 0..1 range

		// Push away from the collision point. The closer our center is to the collision point,
		// the harder we push away.
		props[i]->CollisionProp()->CalcNearestPoint( ourCenter, &nearestPropPoint );
		pPlayer->CollisionProp()->CalcNearestPoint( nearestPropPoint, &nearestPlayerPoint );
		Vector vPushAway = (nearestPlayerPoint - nearestPropPoint);
		float flDist = VectorNormalize( vPushAway );

		const float MaxPushawayDistance = 5.0f;
		if ( flDist > MaxPushawayDistance && !pPlayer->CollisionProp()->IsPointInBounds( nearestPropPoint ) )
		{
			continue;
		}

		// If we're not pushing, try from our center to the nearest edge of the prop
		if ( vPushAway.IsZero() )
		{
			vPushAway = (ourCenter - nearestPropPoint);
			flDist = VectorNormalize( vPushAway );
		}

		// If we're still not pushing, try from our center to the center of the prop
		if ( vPushAway.IsZero() )
		{
			vPushAway = (ourCenter - props[i]->WorldSpaceCenter());
			flDist = VectorNormalize( vPushAway );
		}

		flDist = max( flDist, 1 );

		float flForce = sv_pushaway_player_force.GetFloat() / flDist * mass;
		flForce = min( flForce, sv_pushaway_max_player_force.GetFloat() );

#ifndef CLIENT_DLL
		pPlayer->PushawayTouch( props[i] );

		// We can get right up next to rotating doors before they start to move, so scale back our force so we don't go flying
		if ( FClassnameIs( props[i], "func_door_rotating" ) || FClassnameIs( props[i], "prop_door_rotating" ) )
#endif
		{
			flForce *= 0.25f;
		}

		vPushAway *= flForce;

		pCmd->forwardmove += vPushAway.Dot( currentdir );
		pCmd->sidemove    += vPushAway.Dot( rightdir );
	}
}