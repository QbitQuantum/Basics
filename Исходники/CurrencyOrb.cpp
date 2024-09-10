void CurrencyOrb::DoTrackPlayer(float delta)
{
	mSineWaveProps.DoSineWave = false;

	Player * player = GameObjectManager::Instance()->GetPlayer();
	if (!player)
	{
		return;
	}

	// accelerate towards the target
	Vector3 direction = Vector3(player->CollisionCentreX(), player->CollisionCentreY(), player->Z()) - m_position;

	direction.Normalise();

	m_direction = direction;

	float multiplier = mTimeTracking > 2.0f ? 3.0f : 1.0f;

	bool prioritiseX = false;
	if (std::abs(m_direction.X) > std::abs(m_direction.Y))
	{
		AccelerateX(m_direction.X, kAccelerateRate * multiplier);
		prioritiseX = true;
	}
	else
	{
		AccelerateY(m_direction.Y, kAccelerateRate * multiplier);
	}

	if (prioritiseX && ((m_direction.X < 0 && m_velocity.X > 0) ||
		(m_direction.X > 0 && m_velocity.X < 0)))
	{
		// the velocity of the orb is still moving in the opposite x direction
		// let's give it a helping hand to catch up by accelerating harshly
		AccelerateX(m_direction.X, kHarshAccelerateRate * multiplier);
	}

	if (!prioritiseX && ((m_direction.Y < 0 && m_velocity.Y > 0) ||
		(m_direction.Y > 0 && m_velocity.Y < 0)))
	{
		// the velocity of the orb is still moving in the opposite y direction
		// let's give it a helping hand to catch up by accelerating harshly
		AccelerateY(m_direction.Y, kHarshAccelerateRate * multiplier);
	}

	Vector2 dir = Vector2(m_velocity.X, m_velocity.Y);
	dir.Normalise();

	if (dir.X > 0)
	{
		SetRotationAngle(-acos(dir.Dot(Vector2(0, -1))));
	}
	else
	{
		SetRotationAngle(acos(dir.Dot(Vector2(0, -1))));
	}
}