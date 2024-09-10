void CCSBot::StuckCheck()
{
	if (m_isStuck)
	{
		// we are stuck - see if we have moved far enough to be considered unstuck
		Vector delta = pev->origin - m_stuckSpot;

		const float unstuckRange = 75.0f;
		if (delta.IsLengthGreaterThan(unstuckRange))
		{
			// we are no longer stuck
			ResetStuckMonitor();
			PrintIfWatched("UN-STUCK\n");
		}
	}
	else
	{
		// check if we are stuck
		// compute average velocity over a short period (for stuck check)
		Vector vel = pev->origin - m_lastOrigin;

		// if we are jumping, ignore Z
		if (IsJumping())
			vel.z = 0.0f;

		// cannot be Length2D, or will break ladder movement (they are only Z)
		float moveDist = vel.Length();
		float deltaT = g_flBotFullThinkInterval;

		m_avgVel[ m_avgVelIndex++ ] = moveDist / deltaT;

		if (m_avgVelIndex == MAX_VEL_SAMPLES)
			m_avgVelIndex = 0;

		if (m_avgVelCount < MAX_VEL_SAMPLES)
		{
			m_avgVelCount++;
		}
		else
		{
			// we have enough samples to know if we're stuck
			float avgVel = 0.0f;
			for (int t = 0; t < m_avgVelCount; ++t)
				avgVel += m_avgVel[t];

			avgVel /= m_avgVelCount;

			// cannot make this velocity too high, or bots will get "stuck" when going down ladders
			float stuckVel = (IsUsingLadder()) ? 10.0f : 20.0f;

			if (avgVel < stuckVel)
			{
				// we are stuck - note when and where we initially become stuck
				m_stuckTimestamp = gpGlobals->time;
				m_stuckSpot = pev->origin;
				m_stuckJumpTimestamp = gpGlobals->time + RANDOM_FLOAT(0.0f, 0.5f);

				PrintIfWatched("STUCK\n");
				if (IsLocalPlayerWatchingMe() && cv_bot_debug.value > 0.0f)
				{
					EMIT_SOUND(ENT(pev), CHAN_ITEM, "buttons/button11.wav", VOL_NORM, ATTN_NORM);
				}

				m_isStuck = true;
			}
		}
	}

	// always need to track this
	m_lastOrigin = pev->origin;
}