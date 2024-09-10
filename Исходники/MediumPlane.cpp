void MediumPlane::shoot()
{
	if (Game::Instance()->isPracticeMode())
		return;

	m_target = Game::Instance()->getRandomPLayerCenter();

	if (m_enemyWeapon)
	{
		Vector2D shootDirection = m_target - (m_shootingOffset + m_position);
		shootDirection.normalize();
		Vector2D shootPosition = m_shootingOffset + m_position;
		m_enemyWeapon->shoot(shootPosition, shootDirection);
	}
}