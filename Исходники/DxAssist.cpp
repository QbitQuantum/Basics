void DxAssist::SetUICoordinates(ID3D11Buffer* constantBuffer, uint w, uint h)
{
    static XMMATRIX projectionMatrix;

    projectionMatrix = XMMatrixOrthographicLH( (FLOAT)w, -(FLOAT)h, 0.0f, 1.0f );

    ConstantBuffer cb;
    cb.mWorld = XMMatrixTranslation(-(FLOAT)w * 0.5f, -(FLOAT)h * 0.5f, 0.0f);
    cb.mView = XMMatrixIdentity();
    cb.mProjection = projectionMatrix ;

    m_deviceContext->UpdateSubresource( constantBuffer, 0, NULL, &cb, 0, 0 );
    m_deviceContext->VSSetConstantBuffers( 0, 1, &constantBuffer );
}