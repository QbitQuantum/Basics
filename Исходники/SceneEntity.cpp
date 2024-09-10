bool SceneEntity::notifyMoved(const OIS::MouseEvent &evt, const Ogre::Ray &ray)
{
	if(evt.state.buttonDown(OIS::MB_Left))
	{
		Ogre::Vector3 position = ray.getPoint(mCollsionDepth) + mPickedNodeOffset;
		Ogre::Vector3 pos = position - mSceneNode->getPosition();

		float dis = pos.length();
		if(dis < 500)
		{
			if(mIsXFixed) position.x = mSceneNode->getPosition().x;
			if(mIsYFixed) position.y = mSceneNode->getPosition().y;
			if(mIsZFixed) position.z = mSceneNode->getPosition().z;
 
			mSceneNode->setPosition(position);
			AxisEntity::getSingletonPtr()->setPosition(position);
			AxisEntity::getSingletonPtr()->setVisible(true);
		}
	}
	return true;
}