PhysicsRagDoll::RagBone* PhysicsRagDoll::_addAllBones(PhysicsRagDoll::RagBone* parent, TiXmlElement* boneElement, Actor* parentActor)
{
	// get the information for the bone represented by this element.
    Ogre::Vector3 dir = getAttributeValueAsVector3(boneElement, "dir");
	Ogre::Real length = getAttributeValueAsReal(boneElement, "length");
		
	Ogre::Vector3 size = getAttributeValueAsVector3(boneElement, "size");
	
	
	Ogre::String skeleton_bone = getAttributeValueAsStdString(boneElement, "skeleton_bone");
	Ogre::Bone* ogrebone = mSkeleton->getBone(skeleton_bone);


	Ogre::String shapestr = getAttributeValueAsStdString(boneElement, "shape");
	PhysicsRagDoll::RagBone::BoneShape shape = PhysicsRagDoll::RagBone::BS_BOX;

	if (shapestr=="box")
		shape = PhysicsRagDoll::RagBone::BS_BOX;
	
	if (shapestr=="capsule")
		shape = PhysicsRagDoll::RagBone::BS_CAPSULE;
	
	if (shapestr=="cylinder")
		shape = PhysicsRagDoll::RagBone::BS_CYLINDER;
	
	if (shapestr=="cone")
		shape = PhysicsRagDoll::RagBone::BS_CONE;
	
	if (shapestr=="ellipsoid")
		shape = PhysicsRagDoll::RagBone::BS_ELLIPSOID;

	if (shapestr=="hull")
		shape = PhysicsRagDoll::RagBone::BS_CONVEXHULL;

	Ogre::Real mass = getAttributeValueAsReal(boneElement, "mass");
	
	///////////////////////////////////////////////////////////////////////////////
	RagBone* me = _addBone(mWorld, parent, dir, shape, size, mass, ogrebone,  parentActor);
	///////////////////////////////////////////////////////////////////////////////

	// position the bone.
	Ogre::Quaternion boneorient = mNode->_getDerivedOrientation() * ogrebone->_getDerivedOrientation();
	Ogre::Vector3 bonepos;
	if (shape != PhysicsRagDoll::RagBone::BS_CONVEXHULL)
		bonepos = mNode->_getFullTransform() * ogrebone->_getDerivedPosition() + (boneorient * (dir * (length*0.5f)));
	else
		bonepos = mNode->_getFullTransform() * ogrebone->_getDerivedPosition();

    if (me->getBody())
    	me->getBody()->setPositionOrientation(bonepos, boneorient);

	// set offsets
	if (!parent)
	{
		Ogre::Quaternion offsetorient = (boneorient.Inverse()) * mNode->_getDerivedOrientation();
		Ogre::Vector3 offsetpos = boneorient.Inverse() * (mNode->_getDerivedPosition() - bonepos);
		me->setOffset(offsetorient, offsetpos);
	}


	// get the joint to connect this bone with it's parent.
	if (parent && me->getBody())
	{
		TiXmlElement* jointElement = getChildNamed(boneElement, "Joint");
		if (!jointElement)
		{
			// error!
            LOG_ERROR(Logger::CORE, " Joint not found while creating Ragdoll! ");
			return me;
		}

		Ogre::Vector3 jointpin = getAttributeValueAsVector3(jointElement, "pin");
		Ogre::String jointtypestr = getAttributeValueAsStdString(jointElement, "type");
		PhysicsRagDoll::JointType jointtype = PhysicsRagDoll::JT_BALLSOCKET;

		if (jointtypestr == "ballsocket")
			jointtype = PhysicsRagDoll::JT_BALLSOCKET;

		if (jointtypestr == "hinge")
			jointtype = PhysicsRagDoll::JT_HINGE;


		Ogre::Real limit1 = getAttributeValueAsReal(jointElement, "limit1");
		Ogre::Real limit2 = getAttributeValueAsReal(jointElement, "limit2");

		Ogre::Vector3 jpos = mNode->_getFullTransform() * ogrebone->_getDerivedPosition();
		Ogre::Vector3 jpin = (mNode->_getDerivedOrientation() * parent->getOgreBone()->_getDerivedOrientation()) * jointpin;

		_joinBones(jointtype, parent, me, jpos, jpin, limit1, limit2, mWorld);
	}
	
    LOG_MESSAGE(Logger::CORE, " added bone from '"+ogrebone->getName()+"'.");

	///////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////
	// add all children of this bone.
    for (TiXmlNode* cur = boneElement->FirstChild(); cur; cur = cur->NextSibling())
    {
        if (cur->Type() == TiXmlNode::ELEMENT && hasNodeName(cur, "Bone"))
        {
		    _addAllBones(me, cur->ToElement(), parentActor);
        }
	}

    return me;
}