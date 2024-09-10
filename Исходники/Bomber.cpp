void Bomber::move(Ogre::Vector3 distance)
{
	if(warpTimer <= 0.0 && distance.length() <= 10000){
		m_pNode->translate(m_pNode->getOrientation() * -50 * Ogre::Vector3::UNIT_Y);
		m_pNode->needUpdate();
		warpTimer = 60.0f;
	}else{
		warpTimer -= 0.1f;
	}
	
}