	void Update(IEntity &entity, float timePassed)
	{
		if (m_invalid)
			return;

		QuatT applyingDelta(IDENTITY);

		const float newTime   = min(m_lastTime + timePassed, m_targetTime);
		const float deltaTime = newTime - m_lastTime;
		if (deltaTime > 0.0f)
		{
			Quat totalDeltaRot, lastTotalDeltaRot;

			const float targetTimeInverse = (float)__fres(m_targetTime);

			const float dt = deltaTime * targetTimeInverse;

			const float t     = newTime * targetTimeInverse;
			const float lastT = m_lastTime * targetTimeInverse;

			totalDeltaRot.SetSlerp(Quat(IDENTITY), m_deltaRot, t);
			lastTotalDeltaRot.SetSlerp(Quat(IDENTITY), m_deltaRot, lastT);

			applyingDelta.q = (!lastTotalDeltaRot * totalDeltaRot);
			applyingDelta.t = (m_delta * dt);

			m_lastTime = newTime;
		}
		else if (m_targetTime == 0.f)
		{
			applyingDelta.t = m_delta;
			applyingDelta.q = m_deltaRot;
			m_invalid       = true;
		}

		//CryLog("Moving %s from (%f, %f, %f) to (%f, %f, %f) delta (%f, %f, %f) timeDelta: %f time: %f timeTgt: %f",
		//			entity.GetName(),
		//			entity.GetPos().x, entity.GetPos().y, entity.GetPos().z,
		//			(entity.GetPos()+applyingDelta.t).x, (entity.GetPos()+applyingDelta.t).y, (entity.GetPos()+applyingDelta.t).z,
		//			applyingDelta.t.x, applyingDelta.t.y, applyingDelta.t.z,
		//			deltaTime, newTime, m_targetTime);

		if (m_pAnimatedCharacter)
		{
			m_pAnimatedCharacter->ForceMovement(applyingDelta);
		}
		else
		{
			if (IEntity* pParent = entity.GetParent())
				applyingDelta.t = !pParent->GetRotation() * applyingDelta.t;

			entity.SetPosRotScale(entity.GetPos() + applyingDelta.t, entity.GetRotation() * applyingDelta.q, entity.GetScale());
		}
	}