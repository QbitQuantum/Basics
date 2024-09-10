IActor *CreateObject(XMVECTOR const &xvPos, XMCOLOR const &Color, 
	E_ACTOR_TYPE const eActorType, E_RIGID_BODY_FLAG const eBodyFlag)
{
	const float fBoxSize = 0.4f;

	if (!g_pWireBoxModelRenderer)
	{
		g_pWireBoxModelRenderer = CDistributedObjectCreator::GetInstance()->CreateModelRenderer();
		g_pWireBoxModelRenderer->SetRenderMethod(E_RENDERMETHOD::WIREFRAMED);
		g_pWireBoxModelRenderer->SetRigidBodyFlag(E_RIGID_BODY_FLAG::DYNAMIC);

		CRawModel RawModel;
		RawModel.m_eRidigBodyFlag = E_RIGID_BODY_FLAG::DYNAMIC;
		RawModel.m_vScale = XMFLOAT3(fBoxSize, fBoxSize, fBoxSize);
		ContructBoxVertexBuffer(&RawModel);

		for (auto iMesh : RawModel.m_RawMeshes)
			g_pWireBoxModelRenderer->VAddMesh(iMesh, iMesh);
	}

	if (!g_pSolidBoxModelRenderer)
	{
		g_pSolidBoxModelRenderer = CDistributedObjectCreator::GetInstance()->CreateModelRenderer();
		g_pSolidBoxModelRenderer->SetRenderMethod(E_RENDERMETHOD::SOLID);
		g_pSolidBoxModelRenderer->SetRigidBodyFlag(E_RIGID_BODY_FLAG::DYNAMIC);

		CRawModel RawModel;
		RawModel.m_eRidigBodyFlag = E_RIGID_BODY_FLAG::DYNAMIC;
		RawModel.m_vScale = XMFLOAT3(fBoxSize, fBoxSize, fBoxSize);
		ContructBoxVertexBuffer(&RawModel);

		for (auto iMesh : RawModel.m_RawMeshes)
			g_pSolidBoxModelRenderer->VAddMesh(iMesh, iMesh);
	}

	if (!g_pWireSphereModelRenderer)
	{
		g_pWireSphereModelRenderer = CDistributedObjectCreator::GetInstance()->CreateModelRenderer();
		g_pWireSphereModelRenderer->SetRenderMethod(E_RENDERMETHOD::WIREFRAMED);
		g_pWireSphereModelRenderer->SetRigidBodyFlag(E_RIGID_BODY_FLAG::DYNAMIC);

		CRawModel RawModel;
		RawModel.m_eRidigBodyFlag = E_RIGID_BODY_FLAG::DYNAMIC;
		RawModel.m_vScale = XMFLOAT3(fBoxSize, fBoxSize, fBoxSize);
		ContructSphereVertexBuffer(&RawModel);

		for (auto iMesh : RawModel.m_RawMeshes)
			g_pWireSphereModelRenderer->VAddMesh(iMesh, iMesh);
	}

	if (!g_pSolidSphereModelRenderer)
	{
		g_pSolidSphereModelRenderer = CDistributedObjectCreator::GetInstance()->CreateModelRenderer();
		g_pSolidSphereModelRenderer->SetRenderMethod(E_RENDERMETHOD::SOLID);
		g_pSolidSphereModelRenderer->SetRigidBodyFlag(E_RIGID_BODY_FLAG::DYNAMIC);

		CRawModel RawModel;
		RawModel.m_eRidigBodyFlag = E_RIGID_BODY_FLAG::DYNAMIC;
		RawModel.m_vScale = XMFLOAT3(fBoxSize, fBoxSize, fBoxSize);
		ContructSphereVertexBuffer(&RawModel);

		for (auto iMesh : RawModel.m_RawMeshes)
			g_pSolidSphereModelRenderer->VAddMesh(iMesh, iMesh);
	}

	if (!g_pWirePlaneModelRenderer)
	{
		g_pWirePlaneModelRenderer = CDistributedObjectCreator::GetInstance()->CreateModelRenderer();
		g_pWirePlaneModelRenderer->SetRenderMethod(E_RENDERMETHOD::WIREFRAMED);

		CRawModel RawModel;
		RawModel.m_vScale = XMFLOAT3(500.0f, 500.0f, 500.0f);
		ContructRegularGrid(XMINT2(5, 5), &RawModel);

		for (auto iMesh : RawModel.m_RawMeshes)
			g_pWirePlaneModelRenderer->VAddMesh(iMesh, iMesh);
	}

	if (!g_pSolidPlaneModelRenderer)
	{
		g_pSolidPlaneModelRenderer = CDistributedObjectCreator::GetInstance()->CreateModelRenderer();
		g_pSolidPlaneModelRenderer->SetRenderMethod(E_RENDERMETHOD::SOLID);

		CRawModel RawModel;
		RawModel.m_vScale = XMFLOAT3(500.0f, 500.0f, 500.0f);
		ContructRegularGrid(XMINT2(5, 5), &RawModel);

		for (auto iMesh : RawModel.m_RawMeshes)
			g_pSolidPlaneModelRenderer->VAddMesh(iMesh, iMesh);
	}

	IActor *pActor = nullptr;

	//CObject *pObject;

	switch (eActorType)
	{
	case E_ACTOR_TYPE::CUBE:
		{
			// g_pWireBoxModelRenderer g_pSolidBoxModelRenderer

		pActor = new CBox(xvPos - XMVectorReplicate(fBoxSize / 2), xvPos + XMVectorReplicate(fBoxSize / 2),
			g_pWireBoxModelRenderer);
		}
		break;
	case E_ACTOR_TYPE::SPHERE:
	{
		XMFLOAT3 vPos;
		XMStoreFloat3(&vPos, xvPos);

		pActor = new CSphere(vPos, 1.0f, g_pWireSphereModelRenderer);
	}
		break;
	case E_ACTOR_TYPE::PLANE:
		pActor = new CPlane(g_pSolidPlaneModelRenderer);
		((CPlane *)pActor)->GetPlane().x = XMVectorGetX(xvPos);
		((CPlane *)pActor)->GetPlane().y = XMVectorGetY(xvPos);
		((CPlane *)pActor)->GetPlane().z = XMVectorGetZ(xvPos);
		((CPlane *)pActor)->GetPlane().w = XMVectorGetW(xvPos);
		
		break;
	}

	pActor->VInit();

	for (auto iObject : pActor->GetObjects())
	{
		iObject->SetColor(Color);
	}

	return pActor;
}