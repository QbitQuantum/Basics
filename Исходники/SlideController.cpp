	EStatus Update(float timePassed)
	{
		if (IsTransitioningOut())
		{
			const float ROTATION_LERP_SPEED = 10.0f;

			//--- Blend body rotation to match current view
			Ang3 targetViewDir = m_player.GetAngles();
			Quat targetRotation = Quat::CreateRotationZ(targetViewDir.z);
			Quat newRotation = Quat::CreateNlerp(m_player.GetEntity()->GetRotation(), targetRotation, timePassed*ROTATION_LERP_SPEED);
			m_player.GetEntity()->SetRotation(newRotation);
		}
		else
		{
			static uint32 leanParamCRC = gEnv->pSystem->GetCrc32Gen()->GetCRC32Lowercase("SlideFactor");

			const Matrix34 &worldTM = m_player.GetEntity()->GetWorldTM();
			const Vec3 baseRgt = worldTM.GetColumn0();
			const Vec3 baseFwd = worldTM.GetColumn1();
			const Vec3 lookFwd = m_player.GetViewQuatFinal().GetColumn1();
			const float leanAngle = cry_acosf(baseFwd.Dot(lookFwd));

			float targetLeanFactor = clamp(leanAngle / MAX_LEAN_ANGLE, 0.0f, 1.0f);
			if (baseRgt.Dot(lookFwd) < 0.0f)
			{
				targetLeanFactor *= -1.0f;
			}
			CWeapon *pWeapon = m_player.GetWeapon(m_player.GetCurrentItemId());
			if (pWeapon)
			{
				IFireMode *pFiremode = pWeapon->GetFireMode(pWeapon->GetCurrentFireMode());
				if (pFiremode && (pFiremode->GetNextShotTime() > 0.0f))
				{
					targetLeanFactor = 0.0f;
				}
			}
			const float delta					= targetLeanFactor - m_leanFactor;
			const float step					= LEAN_RATE * timePassed;
			const float newLeanFactor	= (float)__fsel(delta, min(m_leanFactor + step, targetLeanFactor), max(m_leanFactor - step, targetLeanFactor));
			SWeightData weightData;
			weightData.weights[0] = newLeanFactor;
			SetParam(leanParamCRC, weightData);
			m_leanFactor = newLeanFactor;

			if (GetRootScope().IsDifferent(m_fragmentID, m_fragTags))
			{
				SetFragment(m_fragmentID, m_fragTags);
			}
		}

		return TPlayerAction::Update(timePassed);
	}