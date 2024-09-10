void NPCCharacter::_actionLook(const Ogre::Vector3& target)
{
	Ogre::Bone* headBone;
	std::string n = _node->getName();
	Ogre::Skeleton* skel = static_cast<Ogre::Entity*>(_movableObject)->getSkeleton();
	headBone = skel->getBone("Bip01_Head");

	headBone->setManuallyControlled(true);
	headBone->setInheritOrientation(true);
	int nAnim = skel->getNumAnimations();

	//have to do this to allow the head to turn properly.
	for(int i = 0; i < nAnim; ++i)
	{
		skel->getAnimation(i)->destroyNodeTrack(headBone->getHandle());
	}

	Ogre::Vector3 test = headBone->_getDerivedPosition() * CHARACTER_SCALE_FACTOR + _node->getPosition();
	Ogre::Vector3 dir = target - test;
	Ogre::Quaternion nodeRot,boneRot;
	Ogre::Euler boneEuler; boneEuler.setDirection(dir,true,false);
	/*boneRot = _node->convertLocalToWorldOrientation(_node->getOrientation()) * headBone->_getDerivedOrientation();
	Ogre::Vector3 boneTest = boneRot * Ogre::Vector3::UNIT_Z;*/
	//Ogre::Vector3 boneTest = headBone->getOrientation() * Ogre::Vector3::UNIT_Z;

	//turns the direction vector into a 2D normalized vector on the X/Z axis.
	dir.y = 0;
	dir.normalise();

	//All of this ray query stuff is to make sure that the AI can "see" the target before attempting to look at it.
	Ogre::SceneManager* scene = _node->getCreator();
	Ogre::Ray ray(headBone->_getDerivedPosition() * CHARACTER_SCALE_FACTOR + _node->getPosition(),dir);

	Ogre::RaySceneQuery* query = scene->createRayQuery(ray);
	query->setSortByDistance(true);
	query->setQueryMask(CHARACTER_MASK | SCENERY_MASK);

	Ogre::RaySceneQueryResult results = query->execute();

	bool withinView = false;
	if(results.size() == 0)
	{
		withinView = true;
	}
	else
	{
		if(results.begin()->movable->getParentNode()->getName() == getName())
		{
			if(results.size() == 1)
			{
				withinView = true;
			}
		}
		
		if(!withinView && results.size() > 1 && std::next(results.begin())->distance > test.distance(target))
		{
			withinView = true;
		}
	}

	scene->destroyQuery(query);

	if(withinView)
	{
		Ogre::Euler node;
		Ogre::Euler t = headOrientation.getRotationTo(dir);
		t.limitYaw(Ogre::Radian(3.0));
		t.limitPitch(Ogre::Radian(0.0));

		headOrientation = headOrientation + t;
		headOrientation.limitYaw(Ogre::Degree(100));
		headOrientation.limitPitch(Ogre::Degree(60));

		headBone->setOrientation(headOrientation);

		/*headBone->rotate(boneTest.getRotationTo(dir),Ogre::Node::TS_WORLD);

		Ogre::Quaternion boneRotation = _node->convertLocalToWorldOrientation(_node->getOrientation()) * headBone->_getDerivedOrientation() * (Ogre::Quaternion(Ogre::Degree(180),Ogre::Vector3::UNIT_Y));
		Ogre::Quaternion nodeRotation = _node->_getDerivedOrientation();
		Ogre::Quaternion diff = nodeRotation.Inverse() * boneRotation;*/
	}

	_isActFinished = true;
}