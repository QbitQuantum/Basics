void GhostEnemy::Update(double dt)
{
	// Get a direction to the target
	Vector2 moveVector = Vector3(m_target.x, m_target.y) - m_transforms.Translation;
	if (moveVector != Vector2::ZERO_VECTOR)
	{
		moveVector.Normalize();
	}

	// Set the length to move
	moveVector = moveVector * m_moveSpeed * dt;

	m_transforms.Translation += moveVector;

	// Update the weapon
	if (m_weapon != NULL)
	{
		m_weapon->Update(dt);
	}

	// Shoot when possitble
	m_attacked = Attack();
}