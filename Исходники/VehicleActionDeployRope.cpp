//------------------------------------------------------------------------
EntityId CVehicleActionDeployRope::CreateRope(IPhysicalEntity* pLinkedEntity, const Vec3& highPos, const Vec3& lowPos)
{
	IEntitySystem* pEntitySystem = gEnv->pEntitySystem;
	assert(pEntitySystem);

	char pRopeName[256];
	_snprintf(pRopeName, 256, "%s_rope_%d", m_pVehicle->GetEntity()->GetName(), m_seatId);
	pRopeName[sizeof(pRopeName)-1] = '\0';

	SEntitySpawnParams params;
	params.sName = pRopeName;
	params.nFlags = ENTITY_FLAG_CLIENT_ONLY;
	params.pClass = pEntitySystem->GetClassRegistry()->FindClass("RopeEntity");

	IEntity* pRopeEntity = pEntitySystem->SpawnEntity(params, true);
	if (!pRopeEntity)
		return 0;

	pRopeEntity->SetFlags(pRopeEntity->GetFlags() | ENTITY_FLAG_CASTSHADOW );

	pRopeEntity->CreateProxy(ENTITY_PROXY_ROPE);

	IEntityRopeProxy* pEntityRopeProxy = (IEntityRopeProxy*) pRopeEntity->GetProxy(ENTITY_PROXY_ROPE);
	if (!pEntityRopeProxy)
	{
		pEntitySystem->RemoveEntity(pRopeEntity->GetId());
		return 0;
	}

	IRopeRenderNode* pRopeNode = pEntityRopeProxy->GetRopeRendeNode();
	assert(pRopeNode);

	Vec3 ropePoints[2];
	ropePoints[0] = highPos;
	ropePoints[1] = lowPos;

	IRopeRenderNode::SRopeParams m_ropeParams;

	m_ropeParams.nFlags = IRopeRenderNode::eRope_CheckCollisinos | IRopeRenderNode::eRope_Smooth;
	m_ropeParams.fThickness = 0.05f;
	m_ropeParams.fAnchorRadius = 0.1f;
	m_ropeParams.nNumSegments = 8;
	m_ropeParams.nNumSides = 4;
	m_ropeParams.nMaxSubVtx = 3;
	m_ropeParams.nPhysSegments = 8;
	m_ropeParams.mass = 1.0f;
	m_ropeParams.friction = 2;
	m_ropeParams.frictionPull = 2;
	m_ropeParams.wind.Set(0,0,0);
	m_ropeParams.windVariance = 0;
	m_ropeParams.waterResistance = 0;
	m_ropeParams.jointLimit = 0;
	m_ropeParams.maxForce = 0;
	m_ropeParams.airResistance = 0;
	m_ropeParams.fTextureTileU = 1.0f;
	m_ropeParams.fTextureTileV = 10.0f;

	pRopeNode->SetParams(m_ropeParams);
	pRopeNode->SetPoints(ropePoints, 2);
	pRopeNode->SetEntityOwner(m_pVehicle->GetEntity()->GetId());

	pRopeNode->LinkEndEntities(m_pVehicle->GetEntity()->GetPhysics(), NULL);

	return pRopeEntity->GetId();
}