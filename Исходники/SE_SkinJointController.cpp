void SE_SkinJointController::createBoneBaseMatrixInverse()
{
	mBoneBaseMatrixInverse.resize(mBoneVector.size());
	for(int i = 0 ; i < mBoneVector.size() ; i++)
	{
		SE_Bone* bone = mBoneVector[i];
		SE_Matrix4f boneBaseMatrix = bone->getBaseMatrix();
		SE_Bone* parent = bone->getParent();
		while(parent)
		{
			SE_Matrix4f parentBaseMatrix = parent->getBaseMatrix();
			boneBaseMatrix = parentBaseMatrix.mul(boneBaseMatrix);
			parent = parent->getParent();
		}
		mBoneBaseMatrixInverse[i] = boneBaseMatrix.inverse();
	}
}