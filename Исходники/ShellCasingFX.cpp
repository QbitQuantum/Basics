DBOOL CShellCasingFX::CreateObject(CClientDE *pClientDE)
{
	if (!CSpecialFX::CreateObject(pClientDE)) return DFALSE;

	char* pModelName = DNULL;
	char* pSkinName = DNULL;
	if (!GetFileNames(&pModelName, &pSkinName))
		return DFALSE;

	if (!pModelName || !pSkinName) return DFALSE;

	// Setup the shell...

	ObjectCreateStruct createStruct;
	INIT_OBJECTCREATESTRUCT(createStruct);

	createStruct.m_ObjectType = OT_MODEL;
	createStruct.m_Flags = 0;
	_mbscpy((unsigned char*)createStruct.m_Filename, (const unsigned char*)pModelName);
	_mbscpy((unsigned char*)createStruct.m_SkinName, (const unsigned char*)pSkinName);
	VEC_COPY(createStruct.m_Pos, m_vStartPos);
	ROT_COPY(createStruct.m_Rotation, m_rRot);

	m_hObject = pClientDE->CreateObject(&createStruct);
	if (!m_hObject) return DFALSE;


	m_pClientDE->SetObjectScale(m_hObject, &m_vScale);

	DVector vU, vR, vF;
	pClientDE->GetRotationVectors(&m_rRot, &vU, &vR, &vF);

	DVector vVel;

	if(m_bLeftHanded)
		VEC_NEGATE(vR, vR);

	DFLOAT fUpVel = GetRandom(60.0f, 90.0f);
	VEC_MULSCALAR(vU, vU, fUpVel);
	DFLOAT fRightVel = GetRandom(50.0f, 70.0f);
	VEC_MULSCALAR(vR, vR, fRightVel);
	DFLOAT fForwardVel = GetRandom(10.0f, 25.0f);
	VEC_MULSCALAR(vF, vF, fForwardVel);

	VEC_ADD(vVel, vU, vR);
	VEC_ADD(vVel, vVel, vF);

	InitMovingObject(&m_movingObj, &m_vStartPos, &vVel);;
	m_movingObj.m_PhysicsFlags |= MO_HALFGRAVITY;

	m_fExpireTime = 20.0f + m_pClientDE->GetTime();

	// Set the pitch velocity
	m_fPitchVel = GetRandom(-MATH_CIRCLE * 2, MATH_CIRCLE * 2);
	m_fYawVel = GetRandom(-MATH_CIRCLE * 2, MATH_CIRCLE * 2);
	m_fPitch	= m_fYaw = 0.0f;

	return DTRUE;
}