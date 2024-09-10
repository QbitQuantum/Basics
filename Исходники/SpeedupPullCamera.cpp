void SpeedupPullCamera::update(const sf::Time& frameTime)
{
	if (g_inputController->isKeyActive(Key::Up))
	{
		m_cameraTop -= CAMERA_SPEED_PER_S * frameTime.asSeconds();
		m_cameraCenter.y = m_cameraTop + (m_cameraWindowHeight / 2.f);
	}
	if (g_inputController->isKeyActive(Key::Down))
	{
		m_cameraTop += CAMERA_SPEED_PER_S * frameTime.asSeconds();
		m_cameraCenter.y = m_cameraTop + (m_cameraWindowHeight / 2.f);
	}
}