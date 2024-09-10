//-----------------------------------------------------------------------------
void CPUT_DX11::UpdatePerFrameConstantBuffer( double totalSeconds )
{
    if( mpPerFrameConstantBuffer )
    {
        ID3D11Buffer *pBuffer = mpPerFrameConstantBuffer->GetNativeBuffer();

        // update parameters of constant buffer
        D3D11_MAPPED_SUBRESOURCE mapInfo;
        mpContext->Map( pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapInfo );
        {
            // TODO: remove construction of XMM type
            CPUTFrameConstantBuffer *pCb = (CPUTFrameConstantBuffer*)mapInfo.pData;
            CPUTCamera *pCamera     = gpSample->GetCamera();
            if( pCamera )
            {
                pCb->View               = XMMATRIX((float*)pCamera->GetViewMatrix());
                pCb->Projection         = XMMATRIX((float*)pCamera->GetProjectionMatrix());
            }
            pCb->LightColor         = XMLoadFloat3(&XMFLOAT3((float*)&mLightColor)); // TODO: Get from light
            float totalSecondsFloat = (float)totalSeconds;
            pCb->TotalSeconds       = XMLoadFloat(&totalSecondsFloat);
            pCb->AmbientColor       = XMLoadFloat3(&XMFLOAT3((float*)&mAmbientColor));
        }
        mpContext->Unmap(pBuffer,0);
    }
}