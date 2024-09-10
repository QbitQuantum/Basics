void ESKOgre::buildBone(unsigned short b, Ogre::Skeleton *ogre_skeleton, Ogre::Bone *parent_bone) {
	ESKBone *bone = bones[b];
	Ogre::Bone *mBone = ogre_skeleton->createBone(bone->name);
  if (parent_bone)
  {
    parent_bone->addChild(mBone);
  }

	Ogre::Matrix4 parent_matrix = Ogre::Matrix4::IDENTITY;

	if (bone->parent_index < bones.size()) {
		ESKBone *pbone = bones[bone->parent_index];

		parent_matrix = Ogre::Matrix4(pbone->transform_matrix[0], pbone->transform_matrix[4], pbone->transform_matrix[8], pbone->transform_matrix[12],
									  pbone->transform_matrix[1], pbone->transform_matrix[5], pbone->transform_matrix[9], pbone->transform_matrix[13],
									  pbone->transform_matrix[2], pbone->transform_matrix[6], pbone->transform_matrix[10], pbone->transform_matrix[14],
									  pbone->transform_matrix[3], pbone->transform_matrix[7], pbone->transform_matrix[11], pbone->transform_matrix[15]);
	}


	Ogre::Matrix4 transform_matrix(bone->transform_matrix[0], bone->transform_matrix[4], bone->transform_matrix[8], bone->transform_matrix[12],
								   bone->transform_matrix[1], bone->transform_matrix[5], bone->transform_matrix[9], bone->transform_matrix[13],
								   bone->transform_matrix[2], bone->transform_matrix[6], bone->transform_matrix[10], bone->transform_matrix[14],
								   bone->transform_matrix[3], bone->transform_matrix[7], bone->transform_matrix[11], bone->transform_matrix[15]);

	transform_matrix = transform_matrix * parent_matrix.inverse();

	Ogre::Vector3 mPos;
	Ogre::Vector3 mScale;
	Ogre::Quaternion mRot;
	transform_matrix.decomposition(mPos, mScale, mRot);

	LOG_DEBUG("Bone %d Setup for %s: %f %f %f %d\n", b, bone->name.c_str(), (float)mPos.x, (float)mPos.y, (float)mPos.z, bone->index_4);

	mBone->setPosition(mPos * -1);
	mBone->setScale(mScale);
	mBone->setOrientation(mRot.Inverse());
	mBone->setInitialState();

	mBone->setManuallyControlled(false);

	for (size_t i = 0; i < bones.size(); i++) {
		if (bones[i]->parent_index == b) {
			buildBone(i, ogre_skeleton, mBone);
		}
	}
}