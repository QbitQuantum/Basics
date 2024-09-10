void Assignment5::OnResize()
{
    D3DApp::OnResize();

    // The window resized, so update the aspect ratio and recompute the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f*MathHelper::Pi, AspectRatio(), 1.0f, 1000.0f);
    XMStoreFloat4x4(&mProj, P);
    m_Phone.resizeScreen(XMFLOAT2(static_cast<float>(mClientWidth), 
        static_cast<float>(mClientHeight)), md3dDevice);
}