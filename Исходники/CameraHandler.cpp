/*---------------------------------------------------------------------------------*/
void CameraHandler::Zoom(const OIS::MouseEvent &arg)
{
	bool okToZoom = false;
	//Direction from imaginary camera position to character
	Ogre::Vector3 directionToCharacter =  mvpCharNode->_getDerivedPosition() - mvpCamNoCollisionNode->_getDerivedPosition();
	//No direction in Y direction.
	directionToCharacter.y = 0;
	//To check if we're too close or too far
	Ogre::Real lengthToCharacter = directionToCharacter.length();

	//If zoom is positive, we only have to worry about going too close
	if (lengthToCharacter > *mvpCamDistanceMin && arg.state.Z.rel > 0)
	{
		okToZoom = true;
	}
	//If zoom is negative, we only have to worry about going too far
	else if (lengthToCharacter < *mvpCamDistanceMax && arg.state.Z.rel < 0)
	{
		okToZoom = true;
	}

	if (okToZoom)
	{
		//Always the same speed, not dependent of the distance
		directionToCharacter.normalise();
		//At the startup, the camera was translated @ Z axis.
		mvpCamNoCollisionNode->translate(Ogre::Vector3::NEGATIVE_UNIT_Z * (*mvpZoom) * arg.state.Z.rel, Ogre::Node::TS_LOCAL);
	}

}