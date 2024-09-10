void AvHAlienTurret::Shoot(const Vector &inOrigin, const Vector &inToEnemy, const Vector& inVecEnemyVelocity)
{
	// Spawn spike
	AvHSpike* theSpike = GetClassPtr((AvHSpike*)NULL );
	theSpike->Spawn();

	// Make it invisible
	if(!GetGameRules()->GetDrawInvisibleEntities())
	{
		theSpike->pev->effects = EF_NODRAW;
	}
	else
	{
		theSpike->pev->effects = 0;
		theSpike->pev->frame = 0;
		theSpike->pev->scale = 0.5;
		theSpike->pev->rendermode = kRenderTransAlpha;
		theSpike->pev->renderamt = 255;
	}

	// Predict where enemy will be when the spike hits and shoot that way
	float theTimeToReachEnemy = inToEnemy.Length()/(float)kOffenseChamberSpikeVelocity;
	Vector theEnemyPosition;
	VectorAdd(this->pev->origin, inToEnemy, theEnemyPosition);

	float theVelocityLength = inVecEnemyVelocity.Length();
	Vector theEnemyNormVelocity = inVecEnemyVelocity.Normalize();

	// Don't always hit very fast moving targets (jetpackers)
	const float kVelocityFactor = .7f;

	Vector thePredictedPosition;
	VectorMA(theEnemyPosition, theVelocityLength*kVelocityFactor*theTimeToReachEnemy, theEnemyNormVelocity, thePredictedPosition);

	Vector theOrigin = inOrigin;
	
	//Vector theDirToEnemy = inDirToEnemy.Normalize();

	Vector theDirToPredictedEnemy;
	VectorSubtract(thePredictedPosition, this->pev->origin, theDirToPredictedEnemy);
	Vector theDirToEnemy = theDirToPredictedEnemy.Normalize();

	//Vector theAttachOrigin, theAttachAngles;
	//GetAttachment(0, theAttachOrigin, theAttachAngles);
	
	//UTIL_SetOrigin(theSpike->pev, theStartPos);
	//VectorCopy(theStartPos, theSpike->pev->origin);
	VectorCopy(inOrigin, theSpike->pev->origin);

	// Pass this velocity to event
	int theVelocityScalar = kOffenseChamberSpikeVelocity;

	Vector theInitialVelocity;
	VectorScale(theDirToEnemy, theVelocityScalar, theInitialVelocity);
	
	// Set spike owner to OC so it doesn't collide with it
	theSpike->pev->owner = this->edict();

	// Set Spike's team :)
	theSpike->pev->team = this->pev->team;

	VectorCopy(theInitialVelocity, theSpike->pev->velocity);

	// Set amount of damage it will do
	theSpike->SetDamage(BALANCE_VAR(kOffenseChamberDamage));

	// Take into account network precision
	Vector theNetworkDirToEnemy;
	VectorScale(theDirToEnemy, 100.0f, theNetworkDirToEnemy);

	PLAYBACK_EVENT_FULL(0, 0, this->mEvent, 0, theOrigin, theNetworkDirToEnemy, 1.0f, 0.0, /*theWeaponIndex*/ this->entindex(), 0, 0, 0 );

	// Play attack anim
	this->PlayAnimationAtIndex(6, true);

	this->Uncloak();
}