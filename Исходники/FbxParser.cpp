void FBXParser::ProcessFBXBoneNodes(const aiScene* pFbxScene, aiNode* pFbxNode, int parentBoneIndex, CParaXModel* pMesh)
{
	const std::string nodeName(pFbxNode->mName.C_Str());
	// this will force create a bone for every node. Bones without weights are just treated as ordinary nodes, 
	// so it is important to add them here
	int bone_index = CreateGetBoneIndex(pFbxNode->mName.C_Str());
	if (bone_index >= 0)
	{
		ParaEngine::Bone& bone = m_bones[bone_index];
		// use static transform for non-animated bones
		Matrix4 matTrans = reinterpret_cast<const Matrix4&>(pFbxNode->mTransformation);
		bone.matTransform = matTrans.transpose();
		// bone.calc is true, if there is bone animation. 
		if (!bone.IsAnimated())
		{
			bone.flags |= ParaEngine::Bone::BONE_STATIC_TRANSFORM;
		}
	}
	m_bones[bone_index].parent = parentBoneIndex;

	// process any mesh on the node
	int numMeshes = pFbxNode->mNumMeshes;
	for (int i = 0; i < numMeshes; i++)
	{
		ProcessFBXMesh(pFbxScene, pFbxScene->mMeshes[pFbxNode->mMeshes[i]], pFbxNode, pMesh);
	}

	// for children 
	for (int i = 0; i < (int)pFbxNode->mNumChildren; i++)
	{
		ProcessFBXBoneNodes(pFbxScene, pFbxNode->mChildren[i], bone_index, pMesh);
	}
}