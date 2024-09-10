void ModelConverter::WriteSkeleton( const Ogre::Skeleton* pSkel, DiSkeleton* skeleton )
{
	SkeletonBlendMode blendMode = pSkel->getBlendMode() == Ogre::ANIMBLEND_CUMULATIVE?
		Demi::ANIMBLEND_CUMULATIVE:Demi::ANIMBLEND_AVERAGE;

	skeleton->SetBlendMode(blendMode);

	unsigned short numBones = pSkel->getNumBones();
	if (numBones > MAX_BONE_NUM)
	{
		MessageBox(NULL,_T("Too many bones. sorry."),_T("Too many bones. sorry."),MB_ICONERROR | MB_OK );
		return;
	}

	// save transformations
	for (unsigned short i = 0; i < numBones; ++i)
	{
		LogManager::getSingleton().logMessage("   Exporting Bone number " + StringConverter::toString(i));
		Bone* pBone = pSkel->getBone(i);
		
		Demi::DiBone* pMtBone = skeleton->CreateBone(
			pBone->getName().c_str(), pBone->getHandle());

		Vector3 pos,scale;
		Quaternion rot;
		pos   = pBone->getPosition();
		scale = pBone->getScale();
		rot   = pBone->getOrientation();

		pMtBone->SetPosition(pos.x,pos.y,pos.z);

		Demi::DiQuat orient(rot.w,rot.x,rot.y,rot.z);
		pMtBone->SetOrientation(orient);

		pMtBone->SetScale(scale.x, scale.y, scale.z);
	}

	// save parents
	for (unsigned short i = 0; i < numBones; ++i)
	{
		Bone* pBone = pSkel->getBone(i);
		String name = pBone->getName() ;

		if ((pBone->getParent())!=NULL) // root bone
		{
			Bone* pParent = (Bone*)pBone->getParent();
			unsigned short parentID = pParent->getHandle();

			Demi::DiBone* pMtChild = skeleton->GetBone(i);
			Demi::DiBone* pMtParent = skeleton->GetBone(parentID);
			pMtParent->AddChild(pMtChild);
		}
	}
}