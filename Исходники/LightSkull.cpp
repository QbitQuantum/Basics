void LightSkull::OnResize()
{
    D3DApp::OnResize();

    m_proj = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi,
        AspectRatio(), 1.0f, 1000.0f);
}