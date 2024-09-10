// Set up a real move. Return true if it represents real movement, else false.
bool DDA::Init(const GCodes::RawMove *nextMove, bool doMotorMapping)
{
	// 1. Compute the new endpoints and the movement vector
	const int32_t *positionNow = prev->DriveCoordinates();
	const Move *move = reprap.GetMove();
	if (doMotorMapping)
	{
		move->MotorTransform(nextMove->coords, endPoint);			// transform the axis coordinates if on a delta or CoreXY printer
		isDeltaMovement = move->IsDeltaMode()
							&& (endPoint[X_AXIS] != positionNow[X_AXIS] || endPoint[Y_AXIS] != positionNow[Y_AXIS] || endPoint[Z_AXIS] != positionNow[Z_AXIS]);
	}
	else
	{
		isDeltaMovement = false;
	}

	isPrintingMove = false;
	bool realMove = false, xyMoving = false;
	const bool isSpecialDeltaMove = (move->IsDeltaMode() && !doMotorMapping);
	float accelerations[DRIVES];
	const float *normalAccelerations = reprap.GetPlatform()->Accelerations();
	for (size_t drive = 0; drive < DRIVES; drive++)
	{
		accelerations[drive] = normalAccelerations[drive];
		if (drive >= AXES || !doMotorMapping)
		{
			endPoint[drive] = Move::MotorEndPointToMachine(drive, nextMove->coords[drive]);
		}

		int32_t delta;
		if (drive < AXES)
		{
			endCoordinates[drive] = nextMove->coords[drive];
			delta = endPoint[drive] - positionNow[drive];
		}
		else
		{
			delta = endPoint[drive];
		}

		DriveMovement& dm = ddm[drive];
		if (drive < AXES && !isSpecialDeltaMove)
		{
			directionVector[drive] = nextMove->coords[drive] - prev->GetEndCoordinate(drive, false);
			dm.state = (isDeltaMovement || delta != 0)
						? DMState::moving				// on a delta printer, if one tower moves then we assume they all do
						: DMState::idle;
		}
		else
		{
			directionVector[drive] = (float)delta/reprap.GetPlatform()->DriveStepsPerUnit(drive);
			dm.state = (delta != 0) ? DMState::moving : DMState::idle;
		}

		if (dm.state == DMState::moving)
		{
			dm.totalSteps = labs(delta);				// for now this is the number of net steps, but gets adjusted later if there is a reverse in direction
			dm.direction = (delta >= 0);				// for now this is the direction of net movement, but gets adjusted later if it is a delta movement
			realMove = true;

			if (drive < Z_AXIS)
			{
				xyMoving = true;
			}

			if (drive >= AXES && xyMoving)
			{
				if (delta > 0)
				{
					isPrintingMove = true;				// we have both movement and extrusion
				}
				float compensationTime = reprap.GetPlatform()->GetElasticComp(drive);
				if (compensationTime > 0.0)
				{
					// Compensation causes instant velocity changes equal to acceleration * k, so we may need to limit the acceleration
					accelerations[drive] = min<float>(accelerations[drive], reprap.GetPlatform()->ConfiguredInstantDv(drive)/compensationTime);
				}
			}
		}
	}

	// 2. Throw it away if there's no real movement.
	if (!realMove)
	{
		return false;
	}

	// 3. Store some values
	endStopsToCheck = nextMove->endStopsToCheck;
	filePos = nextMove->filePos;
	usePressureAdvance = nextMove->usePressureAdvance;

	// The end coordinates will be valid at the end of this move if it does not involve endstop checks and is not a special move on a delta printer
	endCoordinatesValid = (endStopsToCheck == 0) && (doMotorMapping || !move->IsDeltaMode());

	// 4. Normalise the direction vector and compute the amount of motion.
	// If there is any XYZ movement, then we normalise it so that the total XYZ movement has unit length.
	// This means that the user gets the feed rate that he asked for. It also makes the delta calculations simpler.
	if (xyMoving || ddm[Z_AXIS].state == DMState::moving)
	{
		totalDistance = Normalise(directionVector, DRIVES, AXES);
		if (isDeltaMovement)
		{
			// The following are only needed when doing delta movements. We could defer computing them until Prepare(), which would make simulation faster.
			a2plusb2 = fsquare(directionVector[X_AXIS]) + fsquare(directionVector[Y_AXIS]);
			cKc = (int32_t)(directionVector[Z_AXIS] * DriveMovement::Kc);

			const DeltaParameters& dparams = move->GetDeltaParams();
			const float initialX = prev->GetEndCoordinate(X_AXIS, false);
			const float initialY = prev->GetEndCoordinate(Y_AXIS, false);
			const float diagonalSquared = fsquare(dparams.GetDiagonal());
			const float a2b2D2 = a2plusb2 * diagonalSquared;

			for (size_t drive = 0; drive < AXES; ++drive)
			{
				const float A = initialX - dparams.GetTowerX(drive);
				const float B = initialY - dparams.GetTowerY(drive);
				const float stepsPerMm = reprap.GetPlatform()->DriveStepsPerUnit(drive);
				DriveMovement& dm = ddm[drive];
				const float aAplusbB = A * directionVector[X_AXIS] + B * directionVector[Y_AXIS];
				const float dSquaredMinusAsquaredMinusBsquared = diagonalSquared - fsquare(A) - fsquare(B);
				float h0MinusZ0 = sqrtf(dSquaredMinusAsquaredMinusBsquared);
				dm.mp.delta.hmz0sK = (int32_t)(h0MinusZ0 * stepsPerMm * DriveMovement::K2);
				dm.mp.delta.minusAaPlusBbTimesKs = -(int32_t)(aAplusbB * stepsPerMm * DriveMovement::K2);
				dm.mp.delta.dSquaredMinusAsquaredMinusBsquaredTimesKsquaredSsquared =
						(int64_t)(dSquaredMinusAsquaredMinusBsquared * fsquare(stepsPerMm * DriveMovement::K2));

				// Calculate the distance at which we need to reverse direction.
				if (a2plusb2 <= 0.0)
				{
					// Pure Z movement. We can't use the main calculation because it divides by a2plusb2.
					dm.direction = (directionVector[Z_AXIS] >= 0.0);
					dm.mp.delta.reverseStartStep = dm.totalSteps + 1;
				}
				else
				{
					// The distance to reversal is the solution to a quadratic equation. One root corresponds to the carriages being above the bed,
					// the other root corresponds to the carriages being above the bed.
					const float drev = ((directionVector[Z_AXIS] * sqrt(a2b2D2 - fsquare(A * directionVector[Y_AXIS] - B * directionVector[X_AXIS])))
										- aAplusbB)/a2plusb2;
					if (drev > 0.0 && drev < totalDistance)		// if the reversal point is within range
					{
						// Calculate how many steps we need to move up before reversing
						float hrev = directionVector[Z_AXIS] * drev + sqrt(dSquaredMinusAsquaredMinusBsquared - 2 * drev * aAplusbB - a2plusb2 * fsquare(drev));
						int32_t numStepsUp = (int32_t)((hrev - h0MinusZ0) * stepsPerMm);

						// We may be almost at the peak height already, in which case we don't really have a reversal.
						// We must not set reverseStartStep to 1, because then we would set the direction when Prepare() calls CalcStepTime(), before the previous move finishes.
						if (numStepsUp < 1 || (dm.direction && (uint32_t)numStepsUp <= dm.totalSteps))
						{
							dm.mp.delta.reverseStartStep = dm.totalSteps + 1;
						}
						else
						{
							dm.mp.delta.reverseStartStep = (uint32_t)numStepsUp + 1;

							// Correct the initial direction and the total number of steps
							if (dm.direction)
							{
								// Net movement is up, so we will go up a bit and then down by a lesser amount
								dm.totalSteps = (2 * numStepsUp) - dm.totalSteps;
							}
							else
							{
								// Net movement is down, so we will go up first and then down by a greater amount
								dm.direction = true;
								dm.totalSteps = (2 * numStepsUp) + dm.totalSteps;
							}
						}
					}
					else
					{
						dm.mp.delta.reverseStartStep = dm.totalSteps + 1;
					}
				}
			}
		}
	}
	else
	{
		totalDistance = Normalise(directionVector, DRIVES, DRIVES);
	}

	// 5. Compute the maximum acceleration available and maximum top speed
	float normalisedDirectionVector[DRIVES];			// Used to hold a unit-length vector in the direction of motion
	memcpy(normalisedDirectionVector, directionVector, sizeof(normalisedDirectionVector));
	Absolute(normalisedDirectionVector, DRIVES);
	acceleration = VectorBoxIntersection(normalisedDirectionVector, accelerations, DRIVES);

	// Set the speed to the smaller of the requested and maximum speed.
	// Also enforce a minimum speed of 0.5mm/sec. We need a minimum speed to avoid overflow in the movement calculations.
	float reqSpeed = nextMove->feedRate;
	if (isSpecialDeltaMove)
	{
		// Special case of a raw or homing move on a delta printer
		// We use the Cartesian motion system to implement these moves, so the feed rate will be interpreted in Cartesian coordinates.
		// This is wrong, we want the feed rate to apply to the drive that is moving the farthest.
		float maxDistance = 0.0;
		for (size_t axis = 0; axis < AXES; ++axis)
		{
			if (normalisedDirectionVector[axis] > maxDistance)
			{
				maxDistance = normalisedDirectionVector[axis];
			}
		}
		if (maxDistance != 0.0)				// should always be true
		{
			reqSpeed /= maxDistance;		// because normalisedDirectionVector is unit-normalised
		}
	}
	requestedSpeed = max<float>(0.5, min<float>(reqSpeed, VectorBoxIntersection(normalisedDirectionVector, reprap.GetPlatform()->MaxFeedrates(), DRIVES)));

	// On a Cartesian or CoreXY printer, it is OK to limit the X and Y speeds and accelerations independently, and in consequence to allow greater values
	// for diagonal moves. On a delta, this is not OK and any movement in the XY plane should be limited to the X/Y axis values, which we assume to be equal.
	if (isDeltaMovement)
	{
		const float xyFactor = sqrt(fsquare(normalisedDirectionVector[X_AXIS]) + fsquare(normalisedDirectionVector[X_AXIS]));
		const float maxSpeed = reprap.GetPlatform()->MaxFeedrates()[X_AXIS];
		if (requestedSpeed * xyFactor > maxSpeed)
		{
			requestedSpeed = maxSpeed/xyFactor;
		}

		const float maxAcceleration = normalAccelerations[X_AXIS];
		if (acceleration * xyFactor > maxAcceleration)
		{
			acceleration = maxAcceleration/xyFactor;
		}
	}

	// 6. Calculate the provisional accelerate and decelerate distances and the top speed
	endSpeed = 0.0;					// until the next move asks us to adjust it

	if (prev->state != provisional)
	{
		// There is no previous move that we can adjust, so this move must start at zero speed.
		startSpeed = 0.0;
	}
	else
	{
		// Try to meld this move to the previous move to avoid stop/start
		// Assuming that this move ends with zero speed, calculate the maximum possible starting speed: u^2 = v^2 - 2as
		float maxStartSpeed = sqrtf(acceleration * totalDistance * 2.0);
		prev->targetNextSpeed = min<float>(maxStartSpeed, requestedSpeed);
		DoLookahead(prev);
		startSpeed = prev->targetNextSpeed;
	}

	RecalculateMove();
	state = provisional;
	return true;
}