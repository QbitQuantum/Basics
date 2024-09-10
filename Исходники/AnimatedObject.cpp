	//! Returns the bounding box in world space. [NOTE] Does not work [TODO].
	AxisAlignedBox AnimatedObject::GetBoundingBox()
	{
		//AxisAlignedBox aabb = mSkinnedModel->GetBoundingBox();	// [WIP] The precalculated AABB for the model.
		SkinnedMeshList* meshList = mSkinnedModel->GetMeshList();
		XNA::AxisAlignedBox aabb = meshList->operator[](0)->GetPrimitive()->GetBoundingBox();
		XMFLOAT3 min = aabb.Center - aabb.Extents;
		XMFLOAT3 max = aabb.Center + aabb.Extents;
		for(int i = 1; i < meshList->size(); i++)
		{
			AxisAlignedBox meshAABB = (*meshList)[i]->GetPrimitive()->GetBoundingBox();
			XMFLOAT3 meshMin = meshAABB.Center - meshAABB.Extents;
			XMFLOAT3 meshMax = meshAABB.Center + meshAABB.Extents;

			XMStoreFloat3(&min, XMVectorMin(XMLoadFloat3(&meshMin), XMLoadFloat3(&min)));
			XMStoreFloat3(&max, XMVectorMax(XMLoadFloat3(&meshMax), XMLoadFloat3(&max)));
		}

		aabb.Center =  (min + max) * 0.5f;
		aabb.Extents = (max - min) * 0.5f;

		// Break up the world matrix into it's components.
		XMVECTOR scale, rotation, translation;
		XMMatrixDecompose(&scale, &rotation, &translation, GetWorldMatrix());

		// Transform the AABB with the components.
		TransformAxisAlignedBoxCustom(&aabb, &aabb, scale, rotation, translation);

		aabb.Center = GetPosition();	// [NOTE] Not like this in StaticObject.

		return aabb;
	}