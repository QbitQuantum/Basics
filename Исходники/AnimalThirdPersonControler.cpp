void AnimalThirdPersonControler::orient(int i_xRel, int i_yRel, double i_timeSinceLastFrame)
{
	if (!(m_pAnimal != nullptr && m_pCamera != nullptr))
		return;

	Ogre::Vector3 camPos = m_pCamera->getPosition();
	
	Ogre::Radian angleX(i_xRel * -m_camAngularSpeed);
	Ogre::Radian angleY(i_yRel * -m_camAngularSpeed);

	Ogre::Vector3 avatarToCamera = m_pCamera->getPosition() - m_pAnimal->m_pNode->getPosition();

	// restore lenght
	if (avatarToCamera.length() != m_camDistance)
		avatarToCamera = avatarToCamera.normalisedCopy() * m_camDistance;
	
	// Do not go to the poles
	Ogre::Radian latitude = m_pAnimal->m_pNode->getOrientation().zAxis().angleBetween(avatarToCamera);
	if (latitude < Ogre::Radian(Ogre::Math::DegreesToRadians(10.f)) && angleY < Ogre::Radian(0.f))
		angleY = Ogre::Radian(0.f);
	else if (latitude > Ogre::Radian(Ogre::Math::DegreesToRadians(170.f)) && angleY > Ogre::Radian(0.f))
		angleY = Ogre::Radian(0.f);

	Ogre::Quaternion orient = Ogre::Quaternion(angleY, m_pCamera->getOrientation().xAxis()) * Ogre::Quaternion(angleX, m_pCamera->getOrientation().yAxis());
	Ogre::Vector3 newAvatarToCamera = orient * avatarToCamera;

	// Move camera closer if collides with terrain
	m_collideCamWithTerrain(newAvatarToCamera);
}