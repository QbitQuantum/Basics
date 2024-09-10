void IKChain::Initialize()
{
	// Get skeleton root Ogre::Bone
	Ogre::Bone* oBoneRoot = mOgreSkeleton->getRootBone();
	Ogre::Vector3 vecBonePos = oBoneRoot->getPosition();
	oBoneRoot->setManuallyControlled(true);
	// Create IK root
	mIKRoot = new IKJoint(oBoneRoot, NULL, oBoneRoot->getPosition().x + mMeshNode->getPosition().x, oBoneRoot->getPosition().y + mMeshNode->getPosition().y, oBoneRoot->getPosition().z + mMeshNode->getPosition().z);
	// Keep track of previously processed Ogre::Bone
	IKJoint* oLastIKJoint = mIKRoot;
	// Current Ogre::Bone
	Ogre::Bone* oCurrentBone = oBoneRoot;
	cout << "Current Ogre::Bone: " << oCurrentBone->getName() << endl;
	mJointCount = 1;
	// Ogre::Bone iterator
	Ogre::Node::ChildNodeIterator oIterator = oCurrentBone->getChildIterator();
	Ogre::Vector3 vecParent = oBoneRoot->_getDerivedPosition();
	while ( oIterator.hasMoreElements() ) 
	{
		oCurrentBone = (Ogre::Bone*)oIterator.getNext();
		oCurrentBone->setManuallyControlled(true);
		cout << "Current Ogre::Bone: " << oCurrentBone->getName() << endl;
		Ogre::Vector3 vecDerived = oCurrentBone->_getDerivedPosition();
		Ogre::Vector3 vecJointPos = oCurrentBone->_getDerivedPosition() + mMeshNode->getPosition();
		vecBonePos = oCurrentBone->getPosition();
		IKJoint* oNewJoint = new IKJoint(oCurrentBone, oLastIKJoint, vecJointPos.x, vecJointPos.y, vecJointPos.z);
		oLastIKJoint->SetChild(oNewJoint);
		oLastIKJoint = oNewJoint;
		oIterator = oCurrentBone->getChildIterator();
		mJointCount++;
		mChainLength += vecParent.distance(oCurrentBone->_getDerivedPosition());
		vecParent = oCurrentBone->_getDerivedPosition();
	}
	mChainLength = mChainLength;
	mIKEffector = oLastIKJoint;
	cout << "Ogre::Bone count is " << mJointCount << endl;
}