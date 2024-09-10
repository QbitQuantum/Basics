void Postprocessing_UpdateQuake(float deltaTime)
{
	if (!quake->enabled)
		return;

	quake->time += deltaTime;

	// Update quake

	bool toCenter = true;

	if (quake->time - quake->lastHitTime > quake->hitLength)
	{
		const float hitSizeX = 0.02f;
		const float hitSizeY = 0.1f;

		const float startFadeOutTime = 0.2f;
		const float fadeOutTime = 0.15f;

		quake->targetOffset.Set(
			hitSizeX * ((Random::GetInt() & 1) ? 1.0f : -1.0f),
			hitSizeY * ((Random::GetInt() & 1) ? 1.0f : -1.0f));
		if (quake->lastHitTime > startFadeOutTime)
		{
			quake->targetOffset *= max(0.0f, (fadeOutTime - (quake->lastHitTime - startFadeOutTime)) / fadeOutTime);
		}

		quake->lastHitTime = quake->time;
		quake->hitLength = Random::GetFloat(0.1f, 0.1f);

		if (toCenter)
			quake->offset = quake->targetOffset;
	}

	Vec2 toTargetDir;
	if (toCenter)
		toTargetDir = Vec2(0, 0) - quake->offset;
	else
		toTargetDir = quake->targetOffset - quake->offset;
	float toTargetLength = toTargetDir.Length();
	toTargetDir.Normalize();

	float moveBy = clamp(toTargetLength, 0.0f, (toCenter ? 0.8f : 1.0f) * deltaTime);

	quake->offset += toTargetDir * moveBy;

	if (quake->offset.Length() <= 0.001f)
		quake->enabled = false;
}