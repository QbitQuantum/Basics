//----------------------------------------------------------------------------
void Node::WarmUpRendering(Renderer* pRenderer)
{
#ifndef WIRE_WII // Wii does not need to warm up by submitting draw calls
	WIRE_ASSERT(pRenderer);
	UpdateGS(0, true, false);

	Vector3F cameraLocation = WorldBound->GetCenter();
	cameraLocation.Z() += WorldBound->GetRadius();
	Vector3F viewDirection = -Vector3F::UNIT_Z;
	Vector3F up = Vector3F::UNIT_Y;
	Vector3F right = viewDirection.Cross(up);
	CameraPtr spCamera = WIRE_NEW Camera;
	spCamera->SetFrame(cameraLocation, viewDirection, up, right);

	Float fieldOfView = 60.0F;
	Float aspectRatio = 2;
	Float nearPlane = 0.1F;
	Float farPlane = WorldBound->GetRadius() * 2.0F;
	spCamera->SetFrustum(fieldOfView, aspectRatio, nearPlane, farPlane);

	CullerSorting culler;
	culler.SetCamera(spCamera);
	culler.ComputeVisibleSet(this);

	pRenderer->PreDraw(spCamera);

	// draw scene to warm up batching buffers
	pRenderer->Draw(culler.GetVisibleSets());

	// collect and draw all materials separately so none will be missed
	// by CULL_ALWAYS or Switch/LOD nodes.
	THashSet<Material*> materials;
	TStack<Node*> scene(1000);
	scene.Push(this);
	while (!scene.IsEmpty())
	{
		Node* pNode = NULL;
		scene.Pop(pNode);
		RenderObject* pRenderObject = pNode->GetRenderObject();
		if (pRenderObject && pRenderObject->GetMaterial())
		{
			materials.Insert(pRenderObject->GetMaterial());
		}

		for (UInt i = 0; i < pNode->GetQuantity(); i++)
		{
			Node* pChild = DynamicCast<Node>(pNode->GetChild(i)); 
			if (pChild)
			{
				scene.Push(pChild);
			}
		}
	}

	RenderObjectPtr spCube = StandardMesh::CreateCube24(4, pRenderer->
		GetMaxTextureStages(), true);
	THashSet<Material*>::Iterator it(&materials);
	Transformation transformation;
	transformation.SetTranslate(cameraLocation - Vector3F(0, 0, 3));
	for (Material** pMaterial = it.GetFirst(); pMaterial; pMaterial = 
		it.GetNext())
	{
		spCube->SetMaterial(*pMaterial);
		pRenderer->Draw(spCube, transformation);
	}

	pRenderer->PostDraw();
#endif
}