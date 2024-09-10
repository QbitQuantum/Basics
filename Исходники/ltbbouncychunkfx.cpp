bool CLTBBouncyChunkFX::Init(ILTClient *pClientDE, FX_BASEDATA *pBaseData, const CBaseFXProps *pProps)
{
	// Perform base class initialisation

	if (!CBaseFX::Init(pClientDE, pBaseData, pProps)) 
		return false;

	LTVector vChunkDir = GetProps()->m_vChunkDir;
	if (pBaseData->m_bUseTargetData)
	{
		vChunkDir = pBaseData->m_vTargetNorm;
	}

	LTVector vPos;
	LTRotation rRot;
	if (m_hParent)
	{
		m_pLTClient->GetObjectPos(m_hParent, &vPos);
		m_pLTClient->GetObjectRotation(m_hParent, &rRot);
	}	
	else
	{
		vPos = m_vCreatePos;
		rRot = m_rCreateRot;
	}

	float scale;
	CalcScale(m_tmElapsed, GetProps()->m_tmLifespan, &scale);

	LTVector vScale(scale, scale, scale);

	ObjectCreateStruct ocs;
	INIT_OBJECTCREATESTRUCT(ocs);

	ocs.m_ObjectType		= OT_MODEL;
	ocs.m_Flags				= FLAG_NOLIGHT | FLAG_VISIBLE;
	ocs.m_Pos				= vPos + GetProps()->m_vOffset;
	ocs.m_Rotation			= rRot;
	ocs.m_Scale				= vScale;
	strcpy(ocs.m_Filename, GetProps()->m_sModelName);
	strcpy(ocs.m_SkinName, GetProps()->m_sSkinName);

	m_hBouncyChunk = m_pLTClient->CreateObject(&ocs);

	// Setup an initial vector for the velocity

	LTVector vOther;
	vOther.x = 1.0f;
	vOther.y = 0.0f;
	vOther.z = 1.0f;
	vOther.Norm();

	LTVector vRight = vChunkDir.Cross(vOther);
	LTVector vUp    = vRight.Cross(vOther);

	m_vVel = vRight * (-GetProps()->m_fChunkSpread + (float)(rand() % (int)(GetProps()->m_fChunkSpread * 2.0f)));
	m_vVel += vUp * (-GetProps()->m_fChunkSpread + (float)(rand() % (int)(GetProps()->m_fChunkSpread * 2.0f)));
	m_vVel += vChunkDir * GetProps()->m_fChunkSpeed;
	m_vVel.Norm(GetProps()->m_fChunkSpeed);

	// Create the base object

	CreateDummyObject();
		
	// Success !!

	return true;
}