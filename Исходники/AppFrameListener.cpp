void AppFrameListener::moveInGameCamera()
{
	//mCamNode->setPosition(Ogre::Vector3(100,200,100));
	////mCamNode->setOrientation(planeOri);
	//mCamNode->lookAt(Ogre::Vector3::ZERO, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_Z);

	//return;


	Ogre::Vector3 planePos, planeDir, planeOmega;
	Ogre::Quaternion planeOri;

	mAirplane->getPositionOrientation(planePos,	planeOri);	
	mAirplane->getOmega(planeOmega);

	planeOmega = planeOri.Inverse() * planeOmega;	

	mCamNode->setPosition(planePos);
	mCamNode->setOrientation(planeOri);
	
	
	if( Ogre::Math::Abs(planeOmega.x) - Ogre::Math::Abs(mLastPlaneOmegaX) < 60*mTimeSinceLastFrame)
		mLastPlaneOmegaX = planeOmega.x;
	if( Ogre::Math::Abs(planeOmega.z) - Ogre::Math::Abs(mLastPlaneOmegaZ) < 60*mTimeSinceLastFrame)
		mLastPlaneOmegaZ = planeOmega.z;
	//if( planeVel.z > 0 && planeVel.z - mLastPlaneSpeed < 1)
	//	mLastPlaneSpeed = planeVel.z;

	
	
	if(mCamPosition != 0 || mCamLookBack)
	{
		mCamNode->pitch( Ogre::Radian(mLastPlaneOmegaX)*-0.1 );
		mCamNode->roll( Ogre::Radian(mLastPlaneOmegaZ)*-0.1);
	}
	if(mCamLookBack)
	{
		mCamNode->yaw(Ogre::Degree(180));
		//mCamNode->translate(Ogre::Vector3(0,5,-20), Ogre::Node::TS_LOCAL);
	}
	
	mCamNode->translate(mCamTranslation, Ogre::Node::TS_LOCAL);			


	//Launch a ray from airplane in it's direction, to get the first hit in order 
	//to find the correct position for the crosshair
	Ogre::Vector3 closestPos;
	Ogre::Matrix4 camMatrix;			
	bool enemyHit = false;
	enemyHit = mAirplane->getTargetHitPoint(closestPos);
	camMatrix = mCamera->getProjectionMatrix() * mCamera->getViewMatrix(true);			
	mHUDManager->setCrosshairVScroll((camMatrix*closestPos).y, enemyHit);	

	

}