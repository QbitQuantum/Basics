void CDABViewModel::AddViewModelBob( CBasePlayer *owner, Vector& eyePosition, QAngle& eyeAngles )
{
	CSDKPlayer* pOwner = ToSDKPlayer(owner);
	if (!pOwner)
		return;

	// Offset it a tad so that it moves while looking around.
	eyePosition.x += da_weaponoffset.GetFloat();

	Vector vecViewForward, vecViewRight, vecViewUp;
	AngleVectors(EyeAngles(), &vecViewForward, &vecViewRight, &vecViewUp);

	Vector vecViewDirection(vecViewForward.x, vecViewForward.y, 0);
	vecViewDirection.NormalizeInPlace();

	float flMaxVelocity = 100;
	Vector vecOwnerVelocity = pOwner->GetAbsVelocity();
	if (vecOwnerVelocity.LengthSqr() > flMaxVelocity*flMaxVelocity)
		vecOwnerVelocity = (vecOwnerVelocity / vecOwnerVelocity.Length()) * flMaxVelocity;

	m_vecPlayerVelocityLerp.x = Approach(vecOwnerVelocity.x, m_vecPlayerVelocityLerp.x, 1000*gpGlobals->frametime);
	m_vecPlayerVelocityLerp.y = Approach(vecOwnerVelocity.y, m_vecPlayerVelocityLerp.y, 1000*gpGlobals->frametime);
	m_vecPlayerVelocityLerp.z = Approach(vecOwnerVelocity.z, m_vecPlayerVelocityLerp.z, 1000*gpGlobals->frametime);

	Vector vecPlayerVelocityLerp = m_vecPlayerVelocityLerp;
	vecPlayerVelocityLerp.NormalizeInPlace();

	float flViewVelocityDot = fabs(vecPlayerVelocityLerp.Dot(vecViewRight));
	eyePosition += m_vecPlayerVelocityLerp * da_weaponlag.GetFloat() * flViewVelocityDot;

	if (pOwner->m_Shared.GetViewBobRamp() && pOwner->m_Shared.GetRunSpeed())
	{
		float flViewBobMagnitude = pOwner->m_Shared.GetViewBobRamp() * da_weaponbob.GetFloat();

		float flRunPeriod = M_PI * 3;
		float flRunUpBob = sin(pOwner->GetCurrentTime() * flRunPeriod * 2) * (flViewBobMagnitude / 2);
		float flRunRightBob = sin(pOwner->GetCurrentTime() * flRunPeriod) * flViewBobMagnitude;

		float flWalkPeriod = M_PI * 1.5f;
		float flWalkUpBob = sin(pOwner->GetCurrentTime() * flWalkPeriod * 2) * (flViewBobMagnitude / 2);
		float flWalkRightBob = sin(pOwner->GetCurrentTime() * flWalkPeriod) * flViewBobMagnitude;

		// 0 is walk, 1 is run.
		float flRunRamp = RemapValClamped(pOwner->m_Shared.GetViewBobRamp(), pOwner->m_Shared.GetAimInSpeed()/pOwner->m_Shared.GetRunSpeed(), 1.0f, 0.0f, 1.0f);

		float flRightBob = RemapValClamped(flRunRamp, 0, 1, flWalkRightBob, flRunRightBob);
		float flUpBob = RemapValClamped(flRunRamp, 0, 1, flWalkUpBob, flRunUpBob);

		eyePosition += vecViewRight * flRightBob + vecViewUp * (flUpBob - pOwner->m_Shared.GetViewBobRamp() * da_weapondrop.GetFloat());
	}

	if (pOwner->m_Shared.GetViewTilt())
	{
		Vector vecDiveRight = Vector(0, 0, 1).Cross(pOwner->m_Shared.GetDiveDirection());

		float flRightDot = vecViewDirection.Dot(vecDiveRight);
		float flUpDot = vecViewDirection.Dot(pOwner->m_Shared.GetDiveDirection());

		eyeAngles.z -= flRightDot * pOwner->m_Shared.GetViewTilt() * 8;

		eyePosition += (vecViewUp * (flUpDot * 0.5f) + vecViewDirection * (flUpDot * 0.5f)) * pOwner->m_Shared.GetViewTilt();

		float flDiveBobMagnitude = 0.5f * pOwner->m_Shared.GetViewTilt();
		float flDiveBobPeriod = M_PI * 0.5f;
		float flDiveUpBob = sin(pOwner->GetCurrentTime() * flDiveBobPeriod * 2) * (flDiveBobMagnitude / 2);
		float flDiveRightBob = cos(pOwner->GetCurrentTime() * flDiveBobPeriod * 2) * (flDiveBobMagnitude / 2);

		eyePosition += vecViewRight * flDiveRightBob + vecViewUp * flDiveUpBob;
	}
}