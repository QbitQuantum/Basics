//function that handles the custom rendering
void CBaseSpriteFX::RenderSprite(ILTCustomRenderCallback* pInterface, const LTRigidTransform& tCamera)
{
	//setup our vertex declaration
	if(pInterface->SetVertexDeclaration(g_ClientFXVertexDecl.GetTexTangentSpaceDecl()) != LT_OK)
		return;

	//bind a quad index stream
	if(pInterface->BindQuadIndexStream() != LT_OK)
		return;

	//determine how many indices we are going to need
	uint32 nNumIndices  = (GetProps()->m_bTwoSided) ? 12 : 6;
	uint32 nNumVertices = (GetProps()->m_bTwoSided) ? 8 : 4;

	//sanity check to ensure that we can at least render a sprite
	LTASSERT(QUAD_RENDER_INDEX_STREAM_SIZE >= nNumIndices, "Error: Quad index list is too small to render a sprite");
	LTASSERT(DYNAMIC_RENDER_VERTEX_STREAM_SIZE / sizeof(STexTangentSpaceVert) >= nNumVertices, "Error: Dynamic vertex buffer size is too small to render a sprite");

	//determine the up and right vectors for the sprite
	LTVector vTangent, vBinormal;

	//get the position of this sprite
	LTRigidTransform tObjTransform;
	g_pLTClient->GetObjectTransform(m_hObject, &tObjTransform);

	//determine the center of this sprite
	LTVector vCenter = tObjTransform.m_vPos;

	//determine the orientation of the sprite based upon its facing
	if(GetProps()->m_bAlignToCamera)
	{
		//apply the to camera offset
		LTVector vToCamera = tCamera.m_vPos - vCenter;
		float fScale = GetProps()->m_fToCameraOffset / vToCamera.Mag();
		vCenter += vToCamera * fScale;

		//perform the rotation
		float fCosAng = LTCos(m_fCurrRotationRad);
		float fSinAng = LTSin(m_fCurrRotationRad);

		LTVector vRight = tCamera.m_rRot.Right();
		LTVector vUp = -tCamera.m_rRot.Up();

		vTangent	= fCosAng * vRight + fSinAng * vUp;
		vBinormal	= fCosAng * vUp - fSinAng * vRight;
	}
	else if(GetProps()->m_bAlignAroundZ)
	{
		//we want to orient around the Z axis and align to the camera

		//we need to determine our U vector, which is always our forward
		LTVector vU = tObjTransform.m_rRot.Forward();

		//and now we want to offset our center so that we are anchored on the right hand
		//side of the sprite to the point
		vCenter += vU * (m_fWidth * 0.5f);

		//determine the axis from our camera to our object
		LTVector vToCamera = tCamera.m_vPos - vCenter;

		//and now derive our V vector from the forward and the direction to the camera
		LTVector vV = vToCamera.Cross(vU);

		//detect degenerate cases
		if(vV == LTVector::GetIdentity())
		{
			//degenerate case, any orientation will work fine since the sprite won't
			//be visible anyway
			vV.Init(0.0f, 1.0f, 0.0f);
		}

		//and normalize our vector
		vV.Normalize();

		//now we can determine our tangent and binormal vectors
		vTangent	= -vU;
		vBinormal	= vV;
	}
	else
	{
		vTangent	= -tObjTransform.m_rRot.Right();
		vBinormal	= -tObjTransform.m_rRot.Up();
	}
	
	LTVector vNormal = vBinormal.Cross(vTangent);

	//scale the right and down values to be the appropriate size
	LTVector vRight	= vTangent * m_fWidth * -0.5f;
	LTVector vDown	= vBinormal * m_fWidth * GetProps()->m_fAspectRatio * 0.5f;


	//lock down our buffer for rendering
	SDynamicVertexBufferLockRequest LockRequest;
	if(pInterface->LockDynamicVertexBuffer(nNumVertices, LockRequest) != LT_OK)
		return;

	//fill in our sprite vertices
	STexTangentSpaceVert* pCurrOut = (STexTangentSpaceVert*)LockRequest.m_pData;

	uint32 nColor = SETRGBA(	(uint8)(m_vColor.x * 255.0f), 
								(uint8)(m_vColor.y * 255.0f), 
								(uint8)(m_vColor.z * 255.0f), 
								(uint8)(m_vColor.w * 255.0f));

	//fill in the particle vertices
	pCurrOut[0].m_vPos = vCenter + vRight - vDown;
	pCurrOut[0].m_vUV.Init(0.0f, 0.0f);
	
	pCurrOut[1].m_vPos = vCenter - vRight - vDown;
	pCurrOut[1].m_vUV.Init(1.0f, 0.0f);
	
	pCurrOut[2].m_vPos = vCenter - vRight + vDown;
	pCurrOut[2].m_vUV.Init(1.0f, 1.0f);

	pCurrOut[3].m_vPos = vCenter + vRight + vDown;
	pCurrOut[3].m_vUV.Init(0.0f, 1.0f);

	//setup the remaining vertex components
	for(uint32 nCurrVert = 0; nCurrVert < 4; nCurrVert++)
	{
		pCurrOut[nCurrVert].m_nPackedColor = nColor;
		pCurrOut[nCurrVert].m_vNormal = vNormal;
		pCurrOut[nCurrVert].m_vTangent = vTangent;
		pCurrOut[nCurrVert].m_vBinormal = vBinormal;
	}

	//and fill in the back side if appropriate
	if(GetProps()->m_bTwoSided)
	{
		pCurrOut[4].m_vPos = vCenter - vRight - vDown;
		pCurrOut[4].m_vUV.Init(1.0f, 0.0f);
		
		pCurrOut[5].m_vPos = vCenter + vRight - vDown;
		pCurrOut[5].m_vUV.Init(0.0f, 0.0f);
		
		pCurrOut[6].m_vPos = vCenter + vRight + vDown;
		pCurrOut[6].m_vUV.Init(0.0f, 1.0f);

		pCurrOut[7].m_vPos = vCenter - vRight + vDown;
		pCurrOut[7].m_vUV.Init(1.0f, 1.0f);

		//setup the remaining vertex components
		for(uint32 nCurrVert = 4; nCurrVert < 8; nCurrVert++)
		{
			pCurrOut[nCurrVert].m_nPackedColor = nColor;
			pCurrOut[nCurrVert].m_vNormal = -vNormal;
			pCurrOut[nCurrVert].m_vTangent = -vTangent;
			pCurrOut[nCurrVert].m_vBinormal = vBinormal;
		}
	}

	//unlock and render the batch
	pInterface->UnlockAndBindDynamicVertexBuffer(LockRequest);
	pInterface->RenderIndexed(	eCustomRenderPrimType_TriangleList, 
								0, nNumIndices, LockRequest.m_nStartIndex, 
								0, nNumVertices);
}