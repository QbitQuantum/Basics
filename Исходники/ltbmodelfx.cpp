bool CLTBModelFX::Init(ILTClient *pClientDE, FX_BASEDATA *pBaseData, const CBaseFXProps *pProps)
{
	// Perform base class initialisation

	if (!CBaseFX::Init(pClientDE, pBaseData, pProps)) 
		return false;

	// Use the "target" Normal instead, if one was specified...

	LTVector vNorm = GetProps()->m_vNorm;

	if( pBaseData->m_vTargetNorm.LengthSquared() > MATH_EPSILON )
	{
		vNorm = pBaseData->m_vTargetNorm;
		vNorm.Normalize();
	}

	// Develop the Right and Up vectors based off the Forward...

	LTVector vR, vU;
	if( (1.0f == vNorm.y) || (-1.0f == vNorm.y) )
	{
		vR = LTVector( 1.0f, 0.0f, 0.0f ).Cross( vNorm );
	}
	else
	{
		vR = LTVector( 0.0f, 1.0f, 0.0f ).Cross( vNorm );
	}

	vU = vNorm.Cross( vR );
	m_rNormalRot = LTRotation( vNorm, vU );


	ObjectCreateStruct ocs;

	// Combine the direction we would like to face with our parents rotation...

	if( m_hParent )
	{
		m_pLTClient->GetObjectRotation( m_hParent, &ocs.m_Rotation );
	}
	else
	{
		ocs.m_Rotation = m_rCreateRot;
	}

	ocs.m_Rotation = ocs.m_Rotation * m_rNormalRot;	

	ocs.m_ObjectType		= OT_MODEL;
	ocs.m_Flags				|= pBaseData->m_dwObjectFlags |	(GetProps()->m_bShadow ? FLAG_SHADOW : 0 );
	ocs.m_Flags2			|= pBaseData->m_dwObjectFlags2;
	
	// Calculate the position with the offset in 'local' coordinate space...

	LTMatrix mMat;
	ocs.m_Rotation.ConvertToMatrix( mMat );

	m_vPos = ocs.m_Pos = m_vCreatePos + (mMat * GetProps()->m_vOffset);

	
	SAFE_STRCPY( ocs.m_Filename, GetProps()->m_szModelName );
	
	SAFE_STRCPY( ocs.m_SkinNames[0], GetProps()->m_szSkinName[0] );
	SAFE_STRCPY( ocs.m_SkinNames[1], GetProps()->m_szSkinName[1] );
	SAFE_STRCPY( ocs.m_SkinNames[2], GetProps()->m_szSkinName[2] );
	SAFE_STRCPY( ocs.m_SkinNames[3], GetProps()->m_szSkinName[3] );
	SAFE_STRCPY( ocs.m_SkinNames[4], GetProps()->m_szSkinName[4] );
	
	SAFE_STRCPY( ocs.m_RenderStyleNames[0], GetProps()->m_szRenderStyle[0] );
	SAFE_STRCPY( ocs.m_RenderStyleNames[1], GetProps()->m_szRenderStyle[1] );
	SAFE_STRCPY( ocs.m_RenderStyleNames[2], GetProps()->m_szRenderStyle[2] );
	SAFE_STRCPY( ocs.m_RenderStyleNames[3], GetProps()->m_szRenderStyle[3] );

	m_hObject = m_pLTClient->CreateObject(&ocs);
	if( !m_hObject ) 
		return LTFALSE;

	ILTModel		*pLTModel = m_pLTClient->GetModelLT();
	ANIMTRACKERID	nTracker;
	
	pLTModel->GetMainTracker( m_hObject, nTracker );

	//setup the animation if the user specified one
	if( strlen(GetProps()->m_szAnimName) > 0)
	{
		//ok, we need to set this
		HMODELANIM hAnim = m_pLTClient->GetAnimIndex(m_hObject, GetProps()->m_szAnimName);

		if(hAnim != INVALID_MODEL_ANIM)
		{
			//ok, lets set this animation
			pLTModel->SetCurAnim(m_hObject, nTracker, hAnim);
			pLTModel->ResetAnim(m_hObject, nTracker);
		}
	}
	//disable looping on this animation (so we can actually stop!)
	pLTModel->SetLooping(m_hObject, nTracker, false);

	// Setup the initial data needed to override the models animation length...
	if( GetProps()->m_bOverrideAniLength )
	{
		uint32 nAnimLength;

		pLTModel->GetCurAnimLength( m_hObject, nTracker, nAnimLength );
		pLTModel->SetCurAnimTime( m_hObject, nTracker, 0 );

		float fAniLength = (GetProps()->m_fAniLength < MATH_EPSILON) ? GetProps()->m_tmLifespan : GetProps()->m_fAniLength;
		
		if( fAniLength >= MATH_EPSILON || fAniLength <= -MATH_EPSILON )
			m_fAniRate = (nAnimLength * 0.001f) / fAniLength;

		pLTModel->SetAnimRate( m_hObject, nTracker, m_fAniRate );
	}

	// Success !!

	return LTTRUE;
}