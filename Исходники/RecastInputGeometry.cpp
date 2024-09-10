void InputGeometry::_convertOgreEntities(const Ogre::AxisAlignedBox& tileBounds)
{
	std::vector<Ogre::Entity*> selectedEntities;
	Ogre::AxisAlignedBox boundingBox;
	Ogre::Matrix4 transform;
	for(auto itr = _sourceMeshes.begin(); itr != _sourceMeshes.end(); ++itr)
	{
		transform = _referenceNode->_getFullTransform().inverse() * (*itr)->getParentSceneNode()->_getFullTransform();
		boundingBox = (*itr)->getBoundingBox();
		boundingBox.transform(transform);
		if(boundingBox.intersects(tileBounds))
		{
			selectedEntities.push_back(*itr);
		}
	}

	_sourceMeshes.clear();
	_sourceMeshes = selectedEntities;

	_convertOgreEntities();
}