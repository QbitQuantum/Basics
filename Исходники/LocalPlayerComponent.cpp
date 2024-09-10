//------------------------------------------------------------------------------------
// Adjust the aim dir before we pass it to the torsoAim pose modifier, this allows us
// to have the weapon deviate from the camera in certain circumstances
// Should only be called once per frame as it time-steps internal vars
//------------------------------------------------------------------------------------
void CLocalPlayerComponent::AdjustTorsoAimDir(float fFrameTime, Vec3 &aimDir)
{
	const f32 HALF_PI = gf_PI * 0.5f;
	float newElevLimit = HALF_PI;

	const f32 MIN_FLATTEN_LEVEL		= -0.3f;
	const f32 MAX_FLATTEN_LEVEL		= -0.1f;
	const f32 TARGET_FLATTEN_ELEV	= -0.2f;
	const f32 LIMIT_CHANGE_RATE		= HALF_PI;

	if (g_pGameCVars->pl_swimAlignArmsToSurface && m_rPlayer.IsSwimming() && (m_rPlayer.m_playerStateSwim_WaterTestProxy.GetRelativeWaterLevel() > MIN_FLATTEN_LEVEL))
	{
		newElevLimit = (m_rPlayer.m_playerStateSwim_WaterTestProxy.GetRelativeWaterLevel() - MIN_FLATTEN_LEVEL) / (MAX_FLATTEN_LEVEL - MIN_FLATTEN_LEVEL);
		newElevLimit = LERP(gf_PI * 0.5f, TARGET_FLATTEN_ELEV, clamp_tpl(newElevLimit, 0.0f, 1.0f));
	}

	float limitDelta = LIMIT_CHANGE_RATE * fFrameTime;
	float limitDiff	 = newElevLimit - m_stapElevLimit;
	float smoothedLimit = (float) fsel(fabs_tpl(limitDiff) - limitDelta, m_stapElevLimit + (fsgnf(limitDiff) * limitDelta), newElevLimit);
	m_stapElevLimit = smoothedLimit;

	if (smoothedLimit < HALF_PI)
	{
		//--- Need to limit, convert to yaw & elev, limit & then convert back
		float yaw, elev;
		float xy = aimDir.GetLengthSquared2D();
		if (xy > 0.001f)
		{
			yaw = atan2_tpl(aimDir.y,aimDir.x);
			elev = asin_tpl(clamp_tpl(aimDir.z, -1.f, +1.f));
		}
		else
		{
			yaw = 0.f;
			elev = (float)fsel(aimDir.z, +1.f, -1.f) * (gf_PI*0.5f);
		}

		elev = min(elev, smoothedLimit);

		float sinYaw, cosYaw;
		float sinElev, cosElev;

		sincos_tpl(yaw, &sinYaw, &cosYaw);
		sincos_tpl(elev, &sinElev, &cosElev);

		aimDir.x = cosYaw * cosElev;
		aimDir.y = sinYaw * cosElev;
		aimDir.z = sinElev;
	}
}