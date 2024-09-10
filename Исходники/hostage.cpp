void CHostage::Wiggle(void)
{
	TraceResult tr;
	Vector vec = Vector(0, 0, 0);
	Vector wiggle_directions[8] =
	{
		Vector(50, 0, 0),
		Vector(-50, 0, 0),
		Vector(0, 50, 0),
		Vector(0, -50, 0),
		Vector(50, 50, 0),
		Vector(50, -50, 0),
		Vector(-50, 50, 0),
		Vector(-50, -50, 0)
	};

	for (int i = 0; i < 8; i++)
	{
		if (m_LocalNav->PathTraversable(pev->origin, pev->origin + wiggle_directions[i], TRUE) == TRAVERSABLE_NO)
			vec = vec - wiggle_directions[i];
	}

	Vector vecSrc, vecDest;
	vec = vec + Vector(RANDOM_FLOAT(-3, 3), RANDOM_FLOAT(-3, 3), 0);
	pev->velocity = pev->velocity + (vec.Normalize() * 100);
	vecSrc = pev->origin;
	vecDest = vecSrc + (pev->velocity.Normalize() * 500);
	UTIL_DrawBeamPoints(vecSrc, vecDest, 10, 0, 0, 255);
}