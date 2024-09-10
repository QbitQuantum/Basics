void SkinnedModel::CalculateAABB()
{
	XMFLOAT3 min = XMFLOAT3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
	XMFLOAT3 max = XMFLOAT3(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());

	for(int i = 0; i < 1; i++)
	{
		vector<XMFLOAT4X4> transforms = mAnimator->GetTransforms(1.0f);
		for(int j = 0; j < mMeshList.size(); j++) 
		{
			XNA::AxisAlignedBox aabb = mMeshList[j]->CalculateAABB(transforms);
			XMFLOAT3 meshMin = aabb.Center - aabb.Extents;
			XMFLOAT3 meshMax = aabb.Center + aabb.Extents;

			XMStoreFloat3(&min, XMVectorMin(XMLoadFloat3(&meshMin), XMLoadFloat3(&min)));
			XMStoreFloat3(&max, XMVectorMax(XMLoadFloat3(&meshMax), XMLoadFloat3(&max)));
		}
	}

	mAABB.Center = (min + max) * 0.5f;
	mAABB.Extents = (max - min) * 0.5f;
}