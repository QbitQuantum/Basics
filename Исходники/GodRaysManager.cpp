 void GodRaysManager::_updateProjector()
 {
   const Ogre::Vector3& SunPosition = mHydrax->getSunPosition();
   const Ogre::Vector3& CameraPosition = mHydrax->getCamera()->getDerivedPosition();
   Ogre::Plane WaterPlane = Ogre::Plane(Ogre::Vector3(0, 1, 0), mHydrax->getPosition());
   Ogre::Ray SunToCameraRay = Ogre::Ray(SunPosition, CameraPosition - SunPosition);
   Ogre::Vector3 WaterProjectionPoint = SunToCameraRay.getPoint(SunToCameraRay.intersects(WaterPlane).second);
   Ogre::Vector3 WaterPosition = Ogre::Vector3(WaterProjectionPoint.x, mHydrax->getHeigth(WaterProjectionPoint), WaterProjectionPoint.z);
   mProjectorSN->setPosition(WaterProjectionPoint);
   mProjectorCamera->setFarClipDistance((WaterProjectionPoint - CameraPosition).length());
   mProjectorSN->setDirection(-(WaterProjectionPoint - CameraPosition).normalisedCopy(), Ogre::Node::TS_WORLD);
 }