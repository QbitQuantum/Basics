void cMonster::Tick(float a_Dt, cChunk & a_Chunk)
{
	super::Tick(a_Dt, a_Chunk);

	if (m_Health <= 0)
	{
		// The mob is dead, but we're still animating the "puff" they leave when they die
		m_DestroyTimer += a_Dt / 1000;
		if (m_DestroyTimer > 1)
		{
			Destroy(true);
		}
		return;
	}

	if ((m_Target != NULL) && m_Target->IsDestroyed())
		m_Target = NULL;

	// Burning in daylight
	HandleDaylightBurning(a_Chunk);

	a_Dt /= 1000;

	if (m_bMovingToDestination)
	{
		if (m_bOnGround)
		{
			if (DoesPosYRequireJump((int)floor(m_Destination.y)))
			{
				m_bOnGround = false;

				// TODO: Change to AddSpeedY once collision detection is fixed - currently, mobs will go into blocks attempting to jump without a teleport
				AddPosY(1.2);  // Jump!!
			}
		}

		Vector3d Distance = m_Destination - GetPosition();
		if (!ReachedDestination() && !ReachedFinalDestination())  // If we haven't reached any sort of destination, move
		{
			Distance.y = 0;
			Distance.Normalize();

			if (m_bOnGround)
			{
				Distance *= 2.5f;
			}
			else if (IsSwimming())
			{
				Distance *= 1.3f;
			}
			else
			{
				// Don't let the mob move too much if he's falling.
				Distance *= 0.25f;
			}

			// Apply walk speed:
			Distance *= m_RelativeWalkSpeed;

			AddSpeedX(Distance.x);
			AddSpeedZ(Distance.z);

			// It's too buggy!
			/*
			if (m_EMState == ESCAPING)
			{
				// Runs Faster when escaping :D otherwise they just walk away
				SetSpeedX (GetSpeedX() * 2.f);
				SetSpeedZ (GetSpeedZ() * 2.f);
			}
			*/
		}
		else
		{
			if (ReachedFinalDestination())  // If we have reached the ultimate, final destination, stop pathfinding and attack if appropriate
			{
				FinishPathFinding();
			}
			else
			{
				TickPathFinding();  // We have reached the next point in our path, calculate another point
			}
		}
	}

	SetPitchAndYawFromDestination();
	HandleFalling();

	switch (m_EMState)
	{
		case IDLE:
		{
			// If enemy passive we ignore checks for player visibility
			InStateIdle(a_Dt);
			break;
		}
		case CHASING:
		{
			// If we do not see a player anymore skip chasing action
			InStateChasing(a_Dt);
			break;
		}
		case ESCAPING:
		{
			InStateEscaping(a_Dt);
			break;
		}
			
		case ATTACKING: break;
	}  // switch (m_EMState)

	BroadcastMovementUpdate();
}