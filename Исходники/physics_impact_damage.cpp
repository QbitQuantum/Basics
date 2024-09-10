float CalculateObjectStress( IPhysicsObject *pObject, CBaseEntity *pInputOwnerEntity, vphysics_objectstress_t *pOutput )
{
	CUtlVector< CBaseEntity * > pObjectList;
	CUtlVector< Vector >		objectForce;
	bool hasLargeObject = false;

	// add a slot for static objects
	pObjectList.AddToTail( NULL );
	objectForce.AddToTail( vec3_origin );
	// add a slot for friendly objects
	pObjectList.AddToTail( NULL );
	objectForce.AddToTail( vec3_origin );

	CBaseCombatCharacter *pBCC = pInputOwnerEntity->MyCombatCharacterPointer();

	IPhysicsFrictionSnapshot *pSnapshot = pObject->CreateFrictionSnapshot();
	float objMass = pObject->GetMass();
	while ( pSnapshot->IsValid() )
	{
		float force = pSnapshot->GetNormalForce();
		if ( force > 0.0f )
		{
			IPhysicsObject *pOther = pSnapshot->GetObject(1);
			CBaseEntity *pOtherEntity = static_cast<CBaseEntity *>(pOther->GetGameData());
			if ( !pOtherEntity )
			{
				// object was just deleted, but we still have a contact point this frame...
				// just assume it came from the world.
				pOtherEntity = GetWorldEntity();
			}
			CBaseEntity *pOtherOwner = pOtherEntity;
			if ( pOtherEntity->GetOwnerEntity() )
			{
				pOtherOwner = pOtherEntity->GetOwnerEntity();
			}

			int outIndex = 0;
			if ( !pOther->IsMoveable() )
			{
				outIndex = 0;
			}
			// NavIgnored objects are often being pushed by a friendly
			else if ( pBCC && (pBCC->IRelationType( pOtherOwner ) == D_LI || pOtherEntity->IsNavIgnored()) )
			{
				outIndex = 1;
			}
			// player held objects do no stress
			else if ( pOther->GetGameFlags() & FVPHYSICS_PLAYER_HELD )
			{
				outIndex = 1;
			}
			else
			{
				if ( pOther->GetMass() >= VPHYSICS_LARGE_OBJECT_MASS )
				{
					if ( pInputOwnerEntity->GetGroundEntity() != pOtherEntity)
					{
						hasLargeObject = true;
					}
				}
				// moveable, non-friendly
				
				// aggregate contacts over each object to avoid greater stress in multiple contact cases
				// NOTE: Contacts should be in order, so this shouldn't ever search, but just in case
				outIndex = pObjectList.Count();
				for ( int i = pObjectList.Count()-1; i >= 2; --i )
				{
					if ( pObjectList[i] == pOtherOwner )
					{
						outIndex = i;
						break;
					}
				}
				if ( outIndex == pObjectList.Count() )
				{
					pObjectList.AddToTail( pOtherOwner );
					objectForce.AddToTail( vec3_origin );
				}
			}

			if ( outIndex != 0 && pInputOwnerEntity->GetMoveType() != MOVETYPE_VPHYSICS && !IsPhysicallyControlled(pOtherEntity, pOther) )
			{
				// UNDONE: Test this!  This is to remove any shadow/shadow stress.  The game should handle this with blocked/damage
				force = 0.0f;
			}

			Vector normal;
			pSnapshot->GetSurfaceNormal( normal );
			objectForce[outIndex] += normal * force;
		}
		pSnapshot->NextFrictionData();
	}
	pObject->DestroyFrictionSnapshot( pSnapshot );
	pSnapshot = NULL;

	// clear out all friendly force
	objectForce[1].Init();

	float sum = 0;
	Vector negativeForce = vec3_origin;
	Vector positiveForce = vec3_origin;

	Assert( pObjectList.Count() == objectForce.Count() );
	for ( int objectIndex = pObjectList.Count()-1; objectIndex >= 0; --objectIndex )
	{
		sum += objectForce[objectIndex].Length();
		for ( int i = 0; i < 3; i++ )
		{
			if ( objectForce[objectIndex][i] < 0 )
			{
				negativeForce[i] -= objectForce[objectIndex][i];
			}
			else
			{
				positiveForce[i] += objectForce[objectIndex][i];
			}
		}
	}

	// "external" stress is two way (something pushes on the object and something else pushes back)
	// so the set of minimum values per component are the projections of the two-way force
	// "internal" stress is one way (the object is pushing against something OR something pushing back)
	// the momentum must have come from inside the object (gravity, controller, etc)
	Vector internalForce = vec3_origin;
	Vector externalForce = vec3_origin;

	for ( int i = 0; i < 3; i++ )
	{
		if ( negativeForce[i] < positiveForce[i] )
		{
			internalForce[i] = positiveForce[i] - negativeForce[i];
			externalForce[i] = negativeForce[i];
		}
		else
		{
			internalForce[i] = negativeForce[i] - positiveForce[i];
			externalForce[i] = positiveForce[i];
		}
	}

	// sum is kg in / s
	Vector gravVector;
	physenv->GetGravity( &gravVector );
	float gravity = gravVector.Length();
	if ( pInputOwnerEntity->GetMoveType() != MOVETYPE_VPHYSICS && pObject->IsMoveable() )
	{
		Vector lastVel;
		lastVel.Init();
		if ( pObject->GetShadowController() )
		{
			pObject->GetShadowController()->GetLastImpulse( &lastVel );
		}
		else 
		{
			if ( ( pObject->GetCallbackFlags() & CALLBACK_IS_PLAYER_CONTROLLER ) )
			{
				CBasePlayer *pPlayer = ToBasePlayer( pInputOwnerEntity );
				IPhysicsPlayerController *pController = pPlayer ? pPlayer->GetPhysicsController() : NULL;
				if ( pController )
				{
					pController->GetLastImpulse( &lastVel );
				}
			}
		}
		
		// Work in progress...

		// Peek into the controller for this object.  Look at the input velocity and make sure it's all
		// accounted for in the computed stress.  If not, redistribute external to internal as it's 
		// probably being reflected in a way we can't measure here.
		float inputLen = lastVel.Length() * (1.0f / physenv->GetSimulationTimestep()) * objMass;
		if ( inputLen > 0.0f )
		{
			float internalLen = internalForce.Length();
			if ( internalLen < inputLen )
			{
				float ratio = internalLen / inputLen;
				Vector delta = internalForce * (1.0f - ratio);
				internalForce += delta;
				float deltaLen = delta.Length();
				sum -= deltaLen;
				float extLen = VectorNormalize(externalForce) - deltaLen;
				if ( extLen < 0 )
				{
					extLen = 0;
				}
				externalForce *= extLen;
			}
		}
	}

	float invGravity = gravity;
	if ( invGravity <= 0 )
	{
		invGravity = 1.0f;
	}
	else
	{
		invGravity = 1.0f / invGravity;
	}
	sum *= invGravity;
	internalForce *= invGravity;
	externalForce *= invGravity;
	if ( !pObject->IsMoveable() )
	{
		// the above algorithm will see almost all force as internal if the object is not moveable 
		// (it doesn't push on anything else, so nothing is reciprocated)
		// exceptions for friction of a single other object with multiple contact points on this object
		
		// But the game wants to see it all as external because obviously the object can't move, so it can't have
		// internal stress
		externalForce = internalForce;
		internalForce.Init();

		if ( !pObject->IsStatic() )
		{
			sum += objMass;
		}
	}
	else
	{
		// assume object is at rest
		if ( sum > objMass )
		{
			sum = objMass + (sum-objMass) * 0.5;
		}
	}

	if ( pOutput )
	{
		pOutput->exertedStress = internalForce.Length();
		pOutput->receivedStress = externalForce.Length();
		pOutput->hasNonStaticStress = pObjectList.Count() > 2 ? true : false;
		pOutput->hasLargeObjectContact = hasLargeObject;
	}

	// sum is now kg 
	return sum;
}