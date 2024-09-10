//function that handles the custom rendering
void CTracerFX::RenderTracer(ILTCustomRenderCallback* pInterface, const LTRigidTransform& tCamera)
{
	//track our performance
	CTimedSystemBlock TimingBlock(g_tsClientFXTracer);

	//first determine the length, position, and U range for this tracer (this allows for some
	//early outs)
	float fTracerLen	= GetTracerLength();
	float fTracerStart	= m_fRayPosition;
	float fTracerEnd	= fTracerStart - fTracerLen;

	if((fTracerStart <= 0.0f) || (fTracerEnd >= m_fRayLength))
	{
		//the tracer has fully gone through the ray, don't render
		return;
	}

	//now we need to clip the extents to the range [0..ray length], and handle cropping of the texture
	float fUMin = 0.0f;
	float fUMax = 1.0f;

	if(fTracerEnd < 0.0f)
	{
		//adjust the U max if we are cropping
		if(GetProps()->m_bCropTexture)
		{
			fUMax += fTracerEnd / fTracerLen;
		}
		fTracerEnd = 0.0f;
	}
	if(fTracerStart >= m_fRayLength)
	{
		//adjust the U min if we are cropping
		if(GetProps()->m_bCropTexture)
		{
			fUMin += (fTracerStart - m_fRayLength) / fTracerLen;
		}
		fTracerStart = m_fRayLength;
	}

	//setup our vertex declaration
	if(pInterface->SetVertexDeclaration(g_ClientFXVertexDecl.GetTexTangentSpaceDecl()) != LT_OK)
		return;

	//bind a quad index stream
	if(pInterface->BindQuadIndexStream() != LT_OK)
		return;

	//sanity check to ensure that we can at least render a sprite
	LTASSERT(QUAD_RENDER_INDEX_STREAM_SIZE >= 6, "Error: Quad index list is too small to render a tracer");
	LTASSERT(DYNAMIC_RENDER_VERTEX_STREAM_SIZE / sizeof(STexTangentSpaceVert) > 4, "Error: Dynamic vertex buffer size is too small to render a tracer");

	//we need to determine the facing of this tracer. This is formed by creating a plane from the points
	//Camera, Start, and another point on the ray. The plane normal is then the up, the right is the ray
	//direction, and the normal is ray cross plane normal. 
	LTVector vStartToCamera = m_vStartPos - tCamera.m_vPos;
	float fMag = vStartToCamera.Mag( );
	if( fMag < 0.00001f )
	{
		vStartToCamera = tCamera.m_rRot.Forward();
	}
	else
	{
		vStartToCamera /= fMag;
	}

	//determine the up vector
	LTVector vUp = vStartToCamera.Cross(m_vDirection);
	vUp.Normalize();

	//now determine the actual normal (doesn't need to be normalized since the vectors are
	//unit length and orthogonal)
	LTVector vNormal = vUp.Cross(m_vDirection);

	//lock down our buffer for rendering
	SDynamicVertexBufferLockRequest LockRequest;
	if(pInterface->LockDynamicVertexBuffer(4, LockRequest) != LT_OK)
		return;

	//fill in our sprite vertices
	STexTangentSpaceVert* pCurrOut = (STexTangentSpaceVert*)LockRequest.m_pData;

	//determine the color of this tracer
	float fUnitLifetime = GetUnitLifetime();
	uint32 nColor = CFxProp_Color4f::ToColor(GetProps()->m_cfcColor.GetValue(fUnitLifetime));

	//calculate the front of the tracer in world space
	LTVector vFront = m_vStartPos + m_vDirection * fTracerStart;
	LTVector vBack	= m_vStartPos + m_vDirection * fTracerEnd;

	//and the thickness vector
	float fThickness = GetProps()->m_ffcThickness.GetValue(fUnitLifetime);
	LTVector vThickness = vUp * (fThickness * 0.5f);

	//fill in the particle vertices
	pCurrOut[0].m_vPos = vFront + vThickness;
	pCurrOut[0].m_vUV.Init(fUMin, 0.0f);
	
	pCurrOut[1].m_vPos = vBack + vThickness;
	pCurrOut[1].m_vUV.Init(fUMax, 0.0f);
	
	pCurrOut[2].m_vPos = vBack - vThickness;
	pCurrOut[2].m_vUV.Init(fUMax, 1.0f);

	pCurrOut[3].m_vPos = vFront - vThickness;
	pCurrOut[3].m_vUV.Init(fUMin, 1.0f);

	//setup the remaining vertex components
	for(uint32 nCurrVert = 0; nCurrVert < 4; nCurrVert++)
	{
		pCurrOut[nCurrVert].m_nPackedColor	= nColor;
		pCurrOut[nCurrVert].m_vNormal		= vNormal;
		pCurrOut[nCurrVert].m_vTangent		= vUp;
		pCurrOut[nCurrVert].m_vBinormal		= m_vDirection;
	}

	//unlock and render the batch
	pInterface->UnlockAndBindDynamicVertexBuffer(LockRequest);
	pInterface->RenderIndexed(	eCustomRenderPrimType_TriangleList, 
								0, 6, LockRequest.m_nStartIndex, 
								0, 4);
}