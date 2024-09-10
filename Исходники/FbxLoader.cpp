void LoadAnimation(AnimationData& aAnimation,FbxNode* aNode,FbxAMatrix& aParentOrientation, FbxPose* aPose, FbxAnimLayer* aCurrentAnimLayer, int parentBone)
{
	FbxAMatrix lGlobalPosition = GetGlobalPosition(aNode, static_cast<FbxTime>(0.0f), aPose, &aParentOrientation);
	FbxNodeAttribute* lNodeAttribute = aNode->GetNodeAttribute();
	int boneId = -1;
	if (lNodeAttribute)
	{
		if(lNodeAttribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
		{
			Bone newBone;
			newBone.myAnimationTime = GetAnimationTime(aNode,aCurrentAnimLayer);
			float oneFrameTime = 1.0f/24.0f;
				
			CU::Matrix44f fixMatrix;
			fixMatrix.myMatrix[0] = -1;
			FbxAMatrix lLocalTransform = aNode->EvaluateLocalTransform();
			newBone.myBaseOrientation = fixMatrix * CreateMatrix(lLocalTransform) * fixMatrix;

			char buffer[32];
			_itoa_s<32>(parentBone,buffer,10);
			newBone.myName = aNode->GetName();	
			newBone.myName += buffer;

			int lNodeIndex = aPose->Find(aNode);
			auto bindPoseMatrix = aPose->GetMatrix(lNodeIndex);

			FbxAMatrix bindMatrix;
			memcpy((double*)bindMatrix, (double*)bindPoseMatrix, sizeof(bindMatrix.mData));

			FbxAMatrix localPosOffset;
				
			memcpy((double*)localPosOffset, (double*)bindPoseMatrix, sizeof(localPosOffset.mData));
			localPosOffset =  localPosOffset * aParentOrientation.Inverse();

			newBone.myBindMatrix = fixMatrix * CreateMatrix(lGlobalPosition.Inverse()) * fixMatrix;

			CU::Matrix44f localStartOffset = CreateMatrix(bindMatrix.Inverse());
			for(float currentFrameTime = 0.0f;currentFrameTime < newBone.myAnimationTime;currentFrameTime+= oneFrameTime)
			{
				KeyFrame keyFrame;
				keyFrame.myTime = currentFrameTime;

				FbxTime time;
				time.SetSecondDouble(currentFrameTime);
				keyFrame.myMatrix = fixMatrix * CreateMatrix(aNode->EvaluateLocalTransform(time)) * fixMatrix;
				newBone.myFrames.push_back(keyFrame);
			}
			FbxAMatrix animationMatrix;

			FbxSkeleton* sekeleton = aNode->GetSkeleton();
			if(sekeleton->IsSkeletonRoot())
			{
				aAnimation.myBindMatrix = CU::Matrix44<float>();
				aAnimation.myRootBone = aAnimation.myBones.size();
			}
			boneId = aAnimation.myBones.size();
			aNode->SetUserDataPtr((void*)boneId);

			if(parentBone != -1)
			{
				aAnimation.myBones[parentBone].myChilds.push_back(boneId);
			}
			newBone.myId = boneId;
			aAnimation.myBones.push_back(newBone);
		}
	}

	const int lChildCount = aNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		LoadAnimation( aAnimation, aNode->GetChild(lChildIndex), lGlobalPosition , aPose, aCurrentAnimLayer, boneId);
	}
}