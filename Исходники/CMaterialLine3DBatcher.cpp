////////////////////////////////////////////////////////////////
//
// CMaterialLine3DBatcher::DrawBatch
//
// Create vertices and draw
//
////////////////////////////////////////////////////////////////
void CMaterialLine3DBatcher::DrawBatch(const CVector& vecCameraPos, uint* pBatchIndices, uint uiNumBatchLines, CMaterialItem* pMaterial)
{
    // Prepare vertex buffer
    std::vector<SPDTVertex> vertices;
    vertices.resize(uiNumBatchLines * 6);
    SPDTVertex* pBuffer = &vertices[0];

    // For each line
    for (uint i = 0; i < uiNumBatchLines; i++)
    {
        const SMaterialLine3DItem& item = m_LineList[pBatchIndices[i]];

        SColor color = item.ulColor;
        if (m_bPreGUI)
        {
            color.R /= 2;
            color.G /= 2;
            color.B /= 2;
        }
        const ulong    ulColor = color;
        const CVector& vecA = item.vecFrom;
        const CVector& vecB = item.vecTo;

        const CVector& vecFaceToward = item.bUseFaceToward ? item.vecFaceToward : vecCameraPos;

        // Face toward supplied point
        const CVector vecDif = vecB - vecA;
        const CVector vecToCam = vecFaceToward - vecA;
        const float   t = vecDif.DotProduct(&vecToCam) / vecDif.DotProduct(&vecDif);
        const CVector vecClosestPoint = vecA + vecDif * t;
        const CVector vecToLine = vecClosestPoint - vecFaceToward;

        // Calc other direction
        CVector vecLeft = vecDif;
        vecLeft.CrossProduct(&vecToLine);
        vecLeft.Normalize();

        // Create rectangle points
        const CVector vecShift = vecLeft * (item.fWidth * 0.5f);
        const CVector vecA2 = item.vecFrom + vecShift;
        const CVector vecB2 = item.vecTo + vecShift;
        const CVector vecA1 = item.vecFrom - vecShift;
        const CVector vecB1 = item.vecTo - vecShift;

        WRITE_PDT_VERTEX(pBuffer, vecA1.fX, vecA1.fY, vecA1.fZ, ulColor, item.fU1, item.fV1);
        WRITE_PDT_VERTEX(pBuffer, vecA2.fX, vecA2.fY, vecA2.fZ, ulColor, item.fU2, item.fV1);
        WRITE_PDT_VERTEX(pBuffer, vecB1.fX, vecB1.fY, vecB1.fZ, ulColor, item.fU1, item.fV2);

        WRITE_PDT_VERTEX(pBuffer, vecA2.fX, vecA2.fY, vecA2.fZ, ulColor, item.fU2, item.fV1);
        WRITE_PDT_VERTEX(pBuffer, vecB2.fX, vecB2.fY, vecB2.fZ, ulColor, item.fU2, item.fV2);
        WRITE_PDT_VERTEX(pBuffer, vecB1.fX, vecB1.fY, vecB1.fZ, ulColor, item.fU1, item.fV2);
    }

    // Set vertex stream
    uint        PrimitiveCount = vertices.size() / 3;
    const void* pVertexStreamZeroData = &vertices[0];
    uint        VertexStreamZeroStride = sizeof(SPDTVertex);
    m_pDevice->SetFVF(SPDTVertex::FVF);

    // Change texture addressing mode if required
    if (m_CurrentTextureAddress != pMaterial->m_TextureAddress)
    {
        m_CurrentTextureAddress = pMaterial->m_TextureAddress;
        m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, m_CurrentTextureAddress);
        m_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, m_CurrentTextureAddress);
    }

    if (m_CurrentTextureAddress == TADDRESS_BORDER)
        m_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, pMaterial->m_uiBorderColor);

    // Draw
    if (CTextureItem* pTextureItem = DynamicCast<CTextureItem>(pMaterial))
    {
        // Draw using texture
        m_pDevice->SetTexture(0, pTextureItem->m_pD3DTexture);
        m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
    }
    else if (CShaderInstance* pShaderInstance = DynamicCast<CShaderInstance>(pMaterial))
    {
        // Draw using shader
        ID3DXEffect* pD3DEffect = pShaderInstance->m_pEffectWrap->m_pD3DEffect;

        // Apply custom parameters
        pShaderInstance->ApplyShaderParameters();
        // Apply common parameters
        pShaderInstance->m_pEffectWrap->ApplyCommonHandles();
        // Apply mapped parameters
        pShaderInstance->m_pEffectWrap->ApplyMappedHandles();

        // Do shader passes
        DWORD dwFlags = D3DXFX_DONOTSAVESHADERSTATE;            // D3DXFX_DONOTSAVE(SHADER|SAMPLER)STATE
        uint  uiNumPasses = 0;
        pShaderInstance->m_pEffectWrap->Begin(&uiNumPasses, dwFlags);

        for (uint uiPass = 0; uiPass < uiNumPasses; uiPass++)
        {
            pD3DEffect->BeginPass(uiPass);
            m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
            pD3DEffect->EndPass();
        }
        pShaderInstance->m_pEffectWrap->End();

        // If we didn't get the effect to save the shader state, clear some things here
        if (dwFlags & D3DXFX_DONOTSAVESHADERSTATE)
        {
            m_pDevice->SetVertexShader(NULL);
            m_pDevice->SetPixelShader(NULL);
        }
    }
}