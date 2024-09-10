bool CExporter::generateSkinBone(grp::SkinnedMeshExporter* skinnedMesh, INode* node, ISkin* skin)
{
	Matrix3 mSkinOffset;
	if (!skin->GetSkinInitTM(node, mSkinOffset, true))
	{
		setLastError("获取Skin偏移矩阵失败");
		return false;
	}

	int iNumBone = skin->GetNumBones();
	skinnedMesh->m_boneNames.resize(iNumBone);
	skinnedMesh->m_offsetMatrices.resize(iNumBone);
	for (int i = 0; i < iNumBone; ++i)
	{
		//mbs only
		INode* pBone = skin->GetBone(i);
		if (NULL == pBone)
		{
			setLastError("找不到skin依赖的骨骼");
			return false;
		}
		if (ENUM_NODE_DUMMY == checkNodeType(pBone))
		{
			char szError[1024];
			::StringCchPrintf(szError, sizeof(szError), "发现绑定到虚拟体[%s]的顶点", pBone->GetName());
			setLastError(szError);
			return false;
		}

		wchar_t unicodeString[256];
		mbstowcs(unicodeString, pBone->GetName(), 255);
		skinnedMesh->m_boneNames[i] = unicodeString;

		Matrix3 mBoneOffset;
		skin->GetBoneInitTM(pBone, mBoneOffset);
		mBoneOffset.Invert();
		Matrix3 meshOffset = node->GetObjectTM(0);
		mBoneOffset = meshOffset * mBoneOffset;
		//mBoneOffset = mSkinOffset * mBoneOffset;
		grp::Matrix& mCore = skinnedMesh->m_offsetMatrices[i];
		::MatrixFromMatrix3(mCore, mBoneOffset);
	}
	return true;
}