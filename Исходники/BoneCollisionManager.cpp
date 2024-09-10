void BoneCollisionManager::checkMesh(Ogre::String outFileName, Ogre::SceneNode* node)
{
	std::ofstream file(outFileName.c_str());
	if (file)
	{
		Ogre::Entity* ent = (Ogre::Entity*)node->getAttachedObject(0);
		Ogre::SkeletonInstance* skeletonInst = ent->getSkeleton();
		Ogre::Skeleton::BoneIterator boneI=skeletonInst->getBoneIterator();

		//file<<"Creating bone length information from:\n";
		file<<"Mesh name: "<<ent->getMesh()->getName()<<"\n";
		file<<"Skeleton name: "<<skeletonInst->getName()<<"\n\n";

		while(boneI.hasMoreElements())
		{
			Ogre::Bone* bone=boneI.getNext();
			Ogre::String bName=bone->getName();

			if (bone->getChild(0))
			{
				Ogre::Vector3 curr = bone->_getDerivedPosition();
				Ogre::Vector3 next = bone->getChild(0)->_getDerivedPosition();

				Ogre::Vector3 difference = next-curr;

				//length of bone
				Ogre::Real lenght = difference.length();

				file<<bName<<":\nLength\t\t\t=\t"<<Ogre::StringConverter::toString(lenght,3)<<"\n"<<
					"Position"<<"\t\t=\t"<<Ogre::StringConverter::toString(curr.x,1)<<", "<<
					Ogre::StringConverter::toString(curr.y,1)<<", "<<
					Ogre::StringConverter::toString(curr.z,1)<<"\n";
				if (!bone->getParent())
					file<<bName<<" is a Root Bone!\n\n";
				else
					file<<"\n\n";
			}
		}
	}
}