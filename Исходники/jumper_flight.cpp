void Jumper::Flight::updatePhysics(void)
{
    SpinalCord* spinalCord = _jumper->getSpinalCord();
    Virtues* virtues = _jumper->getVirtues();
	CanopySimulator* canopy = _jumper->getDominantCanopy();

    // velocity of base jumper's body
    NxVec3 velocity = _phActor->getLinearVelocity();
    
    // horizontal velocity (including wind)
    NxVec3 velocityH = velocity; 
    velocityH += _jumper->getScene()->getWindAtPoint( _phActor->getGlobalPosition() );    
    velocityH.y = 0;

    // shock penalty
    float penalty = _jumper->getVirtues()->getControlPenalty( _jumper->getShock() );
    penalty = ( 1 - penalty );

    // update canopy controls
	// modifier to 50% input
	if (spinalCord->modifier) {
		float dt = _jumper->getDeltaTime();
		if (spinalCord->left > 0.5f && Gameplay::iGameplay->getActionChannel(iaLeft)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaLeft)->downAmplitude(dt, 0.5f);
		if (spinalCord->right > 0.5f && Gameplay::iGameplay->getActionChannel(iaRight)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaRight)->downAmplitude(dt, 0.5f);
		if (spinalCord->leftWarp > 0.5f && Gameplay::iGameplay->getActionChannel(iaLeftWarp)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaLeftWarp)->downAmplitude(dt, 0.5f);
		if (spinalCord->rightWarp > 0.5f && Gameplay::iGameplay->getActionChannel(iaRightWarp)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaRightWarp)->downAmplitude(dt, 0.5f);
		if (spinalCord->leftRearRiser > 0.5f && Gameplay::iGameplay->getActionChannel(iaLeftRearRiser)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaLeftRearRiser)->downAmplitude(dt, 0.5f);
		if (spinalCord->rightRearRiser > 0.5f && Gameplay::iGameplay->getActionChannel(iaRightRearRiser)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaRightRearRiser)->downAmplitude(dt, 0.5f);

		if (spinalCord->leftReserve > 0.5f && Gameplay::iGameplay->getActionChannel(iaReserveLeft)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaReserveLeft)->downAmplitude(dt, 0.5f);
		if (spinalCord->rightReserve > 0.5f && Gameplay::iGameplay->getActionChannel(iaReserveRight)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaReserveRight)->downAmplitude(dt, 0.5f);
		if (spinalCord->leftReserveWarp > 0.5f && Gameplay::iGameplay->getActionChannel(iaReserveLeftWarp)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaReserveLeftWarp)->downAmplitude(dt, 0.5f);
		if (spinalCord->rightReserveWarp > 0.5f && Gameplay::iGameplay->getActionChannel(iaReserveRightWarp)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaReserveRightWarp)->downAmplitude(dt, 0.5f);
		if (spinalCord->leftReserveRearRiser > 0.5f && Gameplay::iGameplay->getActionChannel(iaReserveLeftRearRiser)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaReserveLeftRearRiser)->downAmplitude(dt, 0.5f);
		if (spinalCord->rightReserveRearRiser > 0.5f && Gameplay::iGameplay->getActionChannel(iaReserveRightRearRiser)->getTrigger()) Gameplay::iGameplay->getActionChannel(iaReserveRightRearRiser)->downAmplitude(dt, 0.5f);
	}


	// set risers
    canopy->setLeftWarpDeep( spinalCord->leftWarp * penalty );
    canopy->setRightWarpDeep( spinalCord->rightWarp * penalty );
    canopy->setLeftRearRiser( spinalCord->leftRearRiser * penalty );
    canopy->setRightRearRiser( spinalCord->rightRearRiser * penalty );

	canopy->setWLOToggles( spinalCord->trigger_wlo );
    canopy->setHookKnife( spinalCord->trigger_hook );


    // update reserve canopy controls
	if (_jumper->isPlayer() &&
		_jumper->getCanopyReserveSimulator() &&
		_jumper->getDominantCanopy() != _jumper->getCanopyReserveSimulator() && 
		_jumper->getCanopyReserveSimulator()->isOpened()) {

		// set toggles
		CanopySimulator *reserve_canopy = _jumper->getCanopyReserveSimulator();
		reserve_canopy->setLeftDeep( spinalCord->leftReserve * penalty );
		reserve_canopy->setRightDeep( spinalCord->rightReserve * penalty );
		// set risers
		reserve_canopy->setLeftWarpDeep( spinalCord->leftReserveWarp * penalty );
		reserve_canopy->setRightWarpDeep( spinalCord->rightReserveWarp * penalty );
		reserve_canopy->setLeftRearRiser( spinalCord->leftReserveRearRiser * penalty );
		reserve_canopy->setRightRearRiser( spinalCord->rightReserveRearRiser * penalty );

		reserve_canopy->setWLOToggles( spinalCord->trigger_wlo );
		reserve_canopy->setHookKnife( spinalCord->trigger_hook );
	}
    // determine animation sequence to be played
    _targetSequence = &passiveFlightSequence;

	// get total left and right input
	float totalInputLeft = 0.0f;
	float totalInputRight = 0.0f;
	float toggleLeft = spinalCord->left;
	float toggleRight = spinalCord->right;
	if (canopy->getLeftForcedDeep() != -1.0f) toggleLeft = 0.0f;
	if (canopy->getRightForcedDeep() != -1.0f) toggleRight = 0.0f;

	// hard toggle input if unstowing
	if (canopy->getLeftStowed() && spinalCord->trigger_left) {
		toggleLeft = 0.75f;
	}
	if (canopy->getRightStowed() && spinalCord->trigger_right) {
		toggleRight = 0.75f;
	}

	// set toggles
	canopy->setLeftDeep( spinalCord->left * penalty );
	canopy->setRightDeep( spinalCord->right * penalty );

	if (toggleLeft > spinalCord->leftRearRiser && toggleLeft > spinalCord->leftWarp) {
		totalInputLeft = toggleLeft;
	} else if (spinalCord->leftRearRiser > toggleLeft && spinalCord->leftRearRiser > spinalCord->leftWarp) {
		totalInputLeft = spinalCord->leftRearRiser;
	} else {
		totalInputLeft = spinalCord->leftWarp;
	}
	if (toggleRight > spinalCord->rightRearRiser && toggleRight > spinalCord->rightWarp) {
		totalInputRight = toggleRight;
	} else if (spinalCord->rightRearRiser > toggleRight && spinalCord->rightRearRiser > spinalCord->rightWarp) {
		totalInputRight = spinalCord->rightRearRiser;
	} else {
		totalInputRight = spinalCord->rightWarp;
	}


	if( totalInputLeft != 0 && totalInputRight == 0 ) {
		if (canopy->getLeftStowed() && spinalCord->trigger_left) {
			_targetSequence = &unstowLeftSequence;
		} else if (spinalCord->modifier) {
			_targetSequence = &steerLeftSequenceHalf;
		} else {
			_targetSequence = &steerLeftSequence;
		}
	}
	if( totalInputRight != 0 && totalInputLeft == 0 ) {
		if (canopy->getRightStowed() && spinalCord->trigger_right) {
			_targetSequence = &unstowRightSequence;
		} else if (spinalCord->modifier) {
			_targetSequence = &steerRightSequenceHalf;
		} else {
			_targetSequence = &steerRightSequence;
		}
	}
	if( totalInputLeft != 0 && totalInputRight != 0 ) {
		if (canopy->getLeftStowed() || canopy->getRightStowed()) {
			_targetSequence = &groupingUnstowSequence;
		} else if (spinalCord->modifier) {
			_targetSequence = &groupingSequenceHalf;
		} else {
			_targetSequence = &groupingSequence;
		}
	}

	// unstow toggles
	if (spinalCord->left > 0.1f) {
		canopy->setLeftStowed(false);
	}
	if (spinalCord->right > 0.1f) {
		canopy->setRightStowed(false);
	}

    // local coordinate system of base jumper
    NxMat34 pose = _phActor->getGlobalPose();
    NxVec3 x = pose.M.getColumn(0);
    NxVec3 y = pose.M.getColumn(1);
    NxVec3 z = pose.M.getColumn(2);



	// altitude [m]
	//NxVec3 pos = _phActor->getGlobalPosition();
	//const float altitude = pos.y;
	//const float arch_pose_area = 1.9f;

	//// air density: converted to linear from barometric equation [0:10] km altitude
	//// http://www.denysschen.com/catalogue/density.aspx
	//const float AirDensityOld = altitude <= 10000.0f ? (1.196f - 0.0000826f * altitude) : (0.27f);

	//// add drag force
	//float Cd = 0.4f;	// altitude suit = 0.4f
	//const float mTracking = database::Suit::getRecord( _jumper->getVirtues()->equipment.suit.id )->mTracking;
	//Cd *= mTracking;
	//// Drag force vector
	//NxVec3 VecFd = -_phActor->getLinearVelocity();
	//VecFd.normalize();

	//float Fd = 0.5f * AirDensityOld * velocity.magnitudeSquared() * Cd * arch_pose_area * getCore()->getRandToolkit()->getUniform(0.94f, 1.06f);
	//_phActor->addForceAtLocalPos(Fd*VecFd, NxVec3(0, -3.0f, 0));

    // air resistance coefficient
    const float ARmult = 2.5f;
    float AR = ARmult * virtues->getTrackingAirResistance();
    if( database::Suit::getRecord( virtues->equipment.suit.id )->wingsuit )
    {
        AR = ARmult * virtues->getFrogAirResistance();
    }

    // terminal velocity
    const float Vt = sqrt( 9.8f * _phActor->getMass() / AR );
    const float It = velocity.magnitude() / Vt;

    NxVec3 dir = velocity * -1;
    dir.normalize();

    // air resistance force
    const NxVec3 Far = dir * getAirResistancePower( velocity.magnitude() / Vt ) * _phActor->getMass() * 9.8f;

    // finalize motion equation    
    _phActor->addForce( Far );
}