bool CHostageImprov::FaceTowards(const Vector &target, float deltaT)
{
	bool bError = false;
	Vector2D to = (target - GetFeet()).Make2D();

#ifndef PLAY_GAMEDLL
	to.NormalizeInPlace();
#else
	// TODO: fix test demo
	float_precision float_x = target.x - GetFeet().x;
	float_precision float_y = target.y - GetFeet().y;
	float_precision flLen = to.Length();

	if (flLen <= 0)
	{
		to.x = 1;
		to.y = 0;
	}
	else
	{
		to.x = float_x / flLen;
		to.y = float_y / flLen;
	}
#endif

	float moveAngle = GetMoveAngle();

	Vector2D lat(BotCOS(moveAngle), BotSIN(moveAngle));
	Vector2D dir(-lat.y, lat.x);

	float_precision dot = DotProduct(to, dir);

	if (DotProduct(to, lat) < 0.0f)
	{
		if (dot >= 0.0f)
			dot = 1.0f;
		else
			dot = -1.0f;

		bError = true;
	}

	const float maxTurnRate = 0.05f;

	if (bError || Q_fabs(dot) >= maxTurnRate)
	{
		const float tolerance = 300.0f;
		float moveRatio = dot * deltaT * tolerance + moveAngle;

		BotCOS(moveRatio);
		BotSIN(moveRatio);

		m_moveAngle = moveRatio;
		m_hostage->pev->angles.y = moveRatio;

		return false;
	}

	return true;
}