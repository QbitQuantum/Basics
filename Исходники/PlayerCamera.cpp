void PlayerCamera::Update( float dt, Player& player, Input& input, Level& level )
{
	int newPosX = 0,
		newPosY = 0;

	//if(input.GetMouseButtonState(4))
	//{
	//	m_zoomLevel += 1;
	//}
	//if(input.GetMouseButtonState(5))
	//{
	//	m_zoomLevel -= 1;
	//}

	// Sets the camera to always be in the center of the screen where the player is
	newPosX = player.GetPosition().x - (m_screenWidth / 2) + 
		((player.GetWidth() / 2) * (player.GetScale() * m_zoomLevel));
	newPosY = player.GetPosition().y - (m_screenHeight / 2) + 
		((player.GetHeight() / 2) * (player.GetScale() * m_zoomLevel));

	m_posX = Lerp(m_posX, newPosX, 0.07f);
	m_posY = Lerp(m_posY, newPosY, 0.07f);

	//Restrict to the level
	if(m_posX >= (level.GetMapSize()*32) - (m_screenWidth))
	{
		m_posX = (level.GetMapSize()*32) - (m_screenWidth);
	}
	if(m_posX <= 0)
	{
		m_posX = 0;
	}
	if(m_posY >= (level.GetMapSize()*32) - (m_screenHeight))
	{
		m_posY = (level.GetMapSize()*32) - (m_screenHeight);
	}
	if(m_posY <= 0)
	{
		m_posY = 0;
	}


	Camera::Update(dt);
}