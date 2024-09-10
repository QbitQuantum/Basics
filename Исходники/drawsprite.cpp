static void d3d_DrawRotatableSprite(const ViewParams& Params, SpriteInstance *pInstance, SharedTexture *pShared)
{
	
	if(!d3d_SetTexture(pShared, 0, eFS_SpriteTexMemory))
		return;

	float fWidth = (float)((RTexture*)pShared->m_pRenderData)->GetBaseWidth();
	float fHeight = (float)((RTexture*)pShared->m_pRenderData)->GetBaseHeight();

	//cache the object position
	LTVector vPos = pInstance->GetPos();
	
	LTMatrix mRotation;
	d3d_SetupTransformation(&vPos, (float*)&pInstance->m_Rotation, &pInstance->m_Scale, &mRotation);

	//get our basis vectors
	LTVector vRight, vUp, vForward;
	mRotation.GetBasisVectors(&vRight, &vUp, &vForward);

	//scale the vectors to be the appropriate size
	vRight  *= fWidth;
	vUp		*= fHeight;

	// Setup the points.
	RGBColor Color;
	d3d_GetSpriteColor(pInstance, &Color);
	uint32 nColor = Color.color;

	CSpriteVertex SpriteVerts[4];
	SpriteVerts[0].SetupVert(vPos + vUp - vRight, nColor, 0.0f, 0.0f);
	SpriteVerts[1].SetupVert(vPos + vUp + vRight, nColor, 1.0f, 0.0f);
	SpriteVerts[2].SetupVert(vPos + vRight - vUp, nColor, 1.0f, 1.0f);
	SpriteVerts[3].SetupVert(vPos - vRight - vUp, nColor, 0.0f, 1.0f);


	//figure out our final vertices to use
	CSpriteVertex	*pPoints;
	uint32			nPoints;
	CSpriteVertex	ClippedSpriteVerts[40 + 5];

	if(pInstance->m_ClipperPoly != INVALID_HPOLY)
	{
		if(!d3d_ClipSprite(pInstance, pInstance->m_ClipperPoly, &pPoints, &nPoints, ClippedSpriteVerts))
		{
			return;
		}
	}
	else
	{
		pPoints = SpriteVerts;
		nPoints = 4;
	}

	if((pInstance->m_Flags & FLAG_SPRITEBIAS) && !(pInstance->m_Flags & FLAG_REALLYCLOSE))
	{
		//adjust the points
		for(uint32 nCurrPt = 0; nCurrPt < nPoints; nCurrPt++)
		{
			//get the sprite vertex that we are modifying
			LTVector& vPt = SpriteVerts[nCurrPt].m_Vec;

			//find a point relative to the viewer position
			LTVector vPtRelCamera = vPt - Params.m_Pos;

			//determine the distance from the camera
			float fZ = vPtRelCamera.Dot(Params.m_Forward);

			if(fZ <= NEARZ)
				continue;

			//find the bias, up to, but not including the near plane
			float fBiasDist = SPRITE_POSITION_ZBIAS;
			if((fZ + fBiasDist) < NEARZ)
				fBiasDist = NEARZ - fZ;
			
			//now adjust our vectors accordingly so that we can move it forward
			//but have it be the same size
			float fScale = 1 + fBiasDist / fZ;

			vPt = Params.m_Right * vPtRelCamera.Dot(Params.m_Right) * fScale +
				  Params.m_Up * vPtRelCamera.Dot(Params.m_Up) * fScale +
				  (fZ + fBiasDist) * Params.m_Forward + Params.m_Pos;
		}
	}
	
	LTEffectImpl* pEffect = (LTEffectImpl*)LTEffectShaderMgr::GetSingleton().GetEffectShader(pInstance->m_nEffectShaderID);
	if(pEffect)
	{
		pEffect->UploadVertexDeclaration();

		ID3DXEffect* pD3DEffect = pEffect->GetEffect();
		if(pD3DEffect)
		{
			RTexture* pTexture = (RTexture*)pShared->m_pRenderData;
			pD3DEffect->SetTexture("texture0", pTexture->m_pD3DTexture);

			i_client_shell->OnEffectShaderSetParams(pEffect, NULL, NULL, LTShaderDeviceStateImp::GetSingleton());

			UINT nPasses = 0;
			pD3DEffect->Begin(&nPasses, 0);

			for(UINT i = 0; i < nPasses; ++i)
			{
				pD3DEffect->BeginPass(i);
				D3D_CALL(PD3DDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, nPoints-2, pPoints, sizeof(CSpriteVertex)));
				pD3DEffect->EndPass();
			}

			pD3DEffect->End();
		}

	}
	else
	{	
		D3D_CALL(PD3DDEVICE->SetVertexShader(NULL));
		D3D_CALL(PD3DDEVICE->SetFVF(SPRITEVERTEX_FORMAT));
		D3D_CALL(PD3DDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, nPoints-2, pPoints, sizeof(CSpriteVertex)));
	}

	d3d_DisableTexture(0);
}