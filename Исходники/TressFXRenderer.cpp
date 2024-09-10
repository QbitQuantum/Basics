//--------------------------------------------------------------------------------------
//
// BeginHairFrame
//
// Start of hair rendering.
//
//--------------------------------------------------------------------------------------
void TressFXRenderer::BeginHairFrame(ID3D11DeviceContext* pd3dContext,
                                    DirectX::XMVECTOR eyePoint, DirectX::XMVECTOR lightPosition,
                                    DirectX::XMMATRIX *pModelTransformForHead,  DirectX::XMMATRIX *pViewProj,  DirectX::XMMATRIX *pViewProjLightOut,
                                    float screenWidth, float screenHeight, bool singleHeadTransform)
{
    SetSamplerStates(pd3dContext);

    // Set up camera parameters for when the camera is at the position of the light for rendering the shadow map
    XMMATRIX mViewLight, mProjLight;
    XMVECTOR modelCenter = XMVector3TransformCoord(XMLoadFloat3(&m_pTressFXMesh->m_HairAsset.m_bSphere.center), *pModelTransformForHead);
    XMVECTOR vLightAt = modelCenter;
    XMVECTOR vUp = XMVectorSet(0, 1, 0, 0);
    mViewLight = XMMatrixLookAtLH(lightPosition, vLightAt, vUp);

    XMVECTOR vLightToObject = XMVectorSubtract(lightPosition, modelCenter);
    float dis = XMVectorGetX(XMVector3Length(vLightToObject));

    float min_dis = max(0.001f, dis - m_pTressFXMesh->m_HairAsset.m_bSphere.radius);
    float max_dis = dis + m_pTressFXMesh->m_HairAsset.m_bSphere.radius;

    float halfAngle = 1.5f*asin(m_pTressFXMesh->m_HairAsset.m_bSphere.radius/dis);
    float FOV = 2*halfAngle;

    float ratio = 1;

    mProjLight = XMMatrixPerspectiveFovLH( FOV, ratio, min_dis, max_dis );
    *pViewProjLightOut = mViewLight * mProjLight;

    // Map the per-frame constant buffer
    D3D11_MAPPED_SUBRESOURCE MappedResource;
    pd3dContext->Map( m_pcbPerFrame, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource );
    CB_PER_FRAME* pcbPerFrame = ( CB_PER_FRAME* )MappedResource.pData;

    // camera parameters
    XMMATRIX mViewProj = *pViewProj;
    XMMATRIX mInvViewProj = XMMatrixInverse(0, mViewProj);

    float fRenderWidth =  screenWidth;
    float fRenderHeight = screenHeight;

    // Inverse of viewprojection matrix with viewport mapping
    XMMATRIX mViewport  ( 2.0f/fRenderWidth,  0.0f,                   0.0f, 0.0f,
                            0.0f,               -2.0f/fRenderHeight,    0.0f, 0.0f,
                            0.0f,               0.0f,                   1.0f, 0.0f,
                            -1.0f,              1.0f,                   0.0f, 1.0f );

    XMMATRIX mInvViewProjViewport = mViewport * mInvViewProj;

    pcbPerFrame->m_mViewProj = XMMatrixTranspose(mViewProj);
    pcbPerFrame->m_mInvViewProj = XMMatrixTranspose(mInvViewProj);

    pcbPerFrame->m_mInvViewProjViewport = XMMatrixTranspose(mInvViewProjViewport);

    pcbPerFrame->m_mWorld = XMMatrixTranspose(*pModelTransformForHead);

    XMStoreFloat3(&pcbPerFrame->m_vEye, eyePoint);

    pcbPerFrame->m_fvFOV = XM_PI/4;

    // Light camera parameters
    pcbPerFrame->m_mViewProjLight  = XMMatrixTranspose(*pViewProjLightOut);
    pcbPerFrame->m_fNearLight = min_dis;
    pcbPerFrame->m_fFarLight = max_dis;

    XMStoreFloat4(&pcbPerFrame->m_PointLightPos, lightPosition);
    pcbPerFrame->m_PointLightPos.w = 1;

    // scene light color
    pcbPerFrame->m_AmbientLightColor = m_hairParams.ambientLightColor;
    pcbPerFrame->m_PointLightColor = m_hairParams.pointLightColor;

    // hair material
    pcbPerFrame->m_MatBaseColor =  XMFLOAT4(m_hairParams.color.x, m_hairParams.color.y, m_hairParams.color.z, 1);
    pcbPerFrame->m_MatKValue = XMFLOAT4(m_hairParams.Ka, m_hairParams.Kd, m_hairParams.Ks1, m_hairParams.Ex1);
    pcbPerFrame->m_fHairKs2 = m_hairParams.Ks2;
    pcbPerFrame->m_fHairEx2 = m_hairParams.Ex2;

    pcbPerFrame->m_FiberAlpha = m_hairParams.alpha;
    pcbPerFrame->m_HairSMAlpha = m_hairParams.shadowMapAlpha;

    pcbPerFrame->m_FiberRadius = m_hairParams.thickness;

    pcbPerFrame->m_FiberSpacing = m_hairParams.duplicateStrandSpacing;

    pcbPerFrame->m_bThinTip = (m_hairParams.bThinTip ? 1.f : -1.f);
    pcbPerFrame->m_bExpandPixels = 1;

    pcbPerFrame->m_WinSize = XMFLOAT4((float)screenWidth, (float)screenHeight, 1.0f/(float)screenWidth, 1.0f/(float)screenHeight);

    pcbPerFrame->m_iMaxFragments = m_hairParams.maxFragments;

    pcbPerFrame->m_alphaThreshold = m_hairParams.alphaThreshold;

    pcbPerFrame->m_iTechSM = m_hairParams.shadowTechnique;
    pcbPerFrame->m_bUseCoverage = m_hairParams.bAntialias ? 1 : 0;
    pcbPerFrame->m_iStrandCopies = m_hairParams.strandCopies;

    pcbPerFrame->m_mNumVerticesPerStrand = g_TressFXNumVerticesPerStrand;
    pcbPerFrame->m_mNumFollowHairsPerGuideHair = m_pTressFXMesh->m_HairAsset.m_NumFollowHairsPerGuideHair;
    pcbPerFrame->m_bSingleHeadTransform = singleHeadTransform;

    unsigned optionalSRVs = 0;
    if ((m_pTressFXMesh->m_pStrandTexCoordSRV) && (m_pTressFXMesh->m_pHairTextureSRV))
    {
        optionalSRVs |= PER_STRAND_TEX_COORDS;
        // ignore the material base color when getting hair color from the texture
        pcbPerFrame->m_MatBaseColor =  XMFLOAT4(1, 1, 1, 1);
    }
    pcbPerFrame->m_optionalSRVs = optionalSRVs;

    pd3dContext->Unmap( m_pcbPerFrame, 0 );

    // Set constant buffer for vertex and pixel shader
    pd3dContext->VSSetConstantBuffers( 1, 1, &m_pcbPerFrame );
    pd3dContext->PSSetConstantBuffers( 1, 1, &m_pcbPerFrame );
}