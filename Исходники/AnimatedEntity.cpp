	void CAnimatedEntity::setBoneWorldPosition(std::string boneName, Vector3 worldPos)
	{
		Ogre::Bone* bone = _entity->getSkeleton()->getBone(boneName);

		bone->setManuallyControlled(true);

		Ogre::Vector3 parentPos = _entityNode->_getDerivedPosition(); 
		Ogre::Vector3 parentQuatXbonePos = worldPos - parentPos;

		Ogre::Quaternion parentQuat = _entityNode->_getDerivedOrientation(); 
		Ogre::Vector3 bonePos = parentQuat.Inverse() * parentQuatXbonePos;
		Ogre::Vector3 inverseParentScale = 1.0 / _entityNode->_getDerivedScale();

		bone->_setDerivedPosition(bonePos * inverseParentScale);
	}