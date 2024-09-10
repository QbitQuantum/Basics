// Set the render state before drawing this object
//-----------------------------------------------------------------------------
void CPUTModelDX11::UpdateShaderConstants(CPUTRenderParameters &renderParams)
{
    ID3D11DeviceContext *pContext  = ((CPUTRenderParametersDX*)&renderParams)->mpContext;
    D3D11_MAPPED_SUBRESOURCE mapInfo;
    pContext->Map( mpModelConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapInfo );
    {
        CPUTModelConstantBuffer *pCb = (CPUTModelConstantBuffer*)mapInfo.pData;

        // TODO: remove construction of XMM type
        XMMATRIX     world((float*)GetWorldMatrix());
        pCb->World = world;

        CPUTCamera *pCamera   = renderParams.mpCamera;
        XMVECTOR    cameraPos = XMLoadFloat3(&XMFLOAT3( 0.0f, 0.0f, 0.0f ));
        if( pCamera )
        {
            XMMATRIX    view((float*)pCamera->GetViewMatrix());
            XMMATRIX    projection((float*)pCamera->GetProjectionMatrix());
            float      *pCameraPos = (float*)&pCamera->GetPosition();
            cameraPos = XMLoadFloat3(&XMFLOAT3( pCameraPos[0], pCameraPos[1], pCameraPos[2] ));

            // Note: We compute viewProjection to a local to avoid reading from write-combined memory.
            // The constant buffer uses write-combined memory.  We read this matrix when computing WorldViewProjection.
            // It is very slow to read it directly from the constant buffer.
            XMMATRIX viewProjection  = view * projection;
            pCb->ViewProjection      = viewProjection;
            pCb->WorldViewProjection = world * viewProjection;
            XMVECTOR determinant     = XMMatrixDeterminant(world);
            pCb->InverseWorld        = XMMatrixInverse(&determinant, XMMatrixTranspose(world));
        }
        // TODO: Have the lights set their render states?

        XMVECTOR lightDirection = XMLoadFloat3(&XMFLOAT3( gLightDir.x, gLightDir.y, gLightDir.z ));
        pCb->LightDirection     = XMVector3Normalize(lightDirection);
        pCb->EyePosition        = cameraPos;
        float *bbCWS = (float*)&mBoundingBoxCenterWorldSpace;
        float *bbHWS = (float*)&mBoundingBoxHalfWorldSpace;
        float *bbCOS = (float*)&mBoundingBoxCenterObjectSpace;
        float *bbHOS = (float*)&mBoundingBoxHalfObjectSpace;
        pCb->BoundingBoxCenterWorldSpace  = XMLoadFloat3(&XMFLOAT3( bbCWS[0], bbCWS[1], bbCWS[2] )); ;
        pCb->BoundingBoxHalfWorldSpace    = XMLoadFloat3(&XMFLOAT3( bbHWS[0], bbHWS[1], bbHWS[2] )); ;
        pCb->BoundingBoxCenterObjectSpace = XMLoadFloat3(&XMFLOAT3( bbCOS[0], bbCOS[1], bbCOS[2] )); ;
        pCb->BoundingBoxHalfObjectSpace   = XMLoadFloat3(&XMFLOAT3( bbHOS[0], bbHOS[1], bbHOS[2] )); ;

        // Shadow camera
        XMMATRIX    shadowView, shadowProjection;
        CPUTCamera *pShadowCamera = gpSample->GetShadowCamera();
        if( pShadowCamera )
        {
            shadowView = XMMATRIX((float*)pShadowCamera->GetViewMatrix());
            shadowProjection = XMMATRIX((float*)pShadowCamera->GetProjectionMatrix());
            pCb->LightWorldViewProjection = world * shadowView * shadowProjection;
        }
    }
    pContext->Unmap(mpModelConstantBuffer,0);
}