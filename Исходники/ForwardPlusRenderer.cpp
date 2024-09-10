void ForwardPlusRenderer::RenderFinal(const RenderView& view, const RenderTarget& renderTarget)
{
    auto& pass = (MsaaEnabled) ? FinalPassMsaa : FinalPass;

    if (!MsaaEnabled)
    {
        pass->SetRenderTarget(0, renderTarget.Texture->GetRTV());
    }

    pass->Begin();

    XMMATRIX worldToView = XMLoadFloat4x4(&view.WorldToView);
    XMMATRIX worldToProjection = XMMatrixMultiply(worldToView, XMLoadFloat4x4(&view.ViewToProjection));

    // Directional Lights are shared for all objects, so fill up front
    FinalPassPSConstants psConstants{};
    psConstants.NumLights = 0;
    psConstants.TileSize = NUM_PIXELS_PER_GROUP_X;
    psConstants.NumTilesX = RTWidth / NUM_PIXELS_PER_GROUP_X;

    for (auto& light : Lights)
    {
        if (light->GetType() == LightType::Directional)
        {
            psConstants.Lights[psConstants.NumLights].Color = light->GetColor();

            XMFLOAT4X4 localToWorld = light->GetLocalToWorld();
            XMVECTOR lightDir = XMVectorNegate(XMVectorSet(localToWorld.m[2][0], localToWorld.m[2][1], localToWorld.m[2][2], 0.f));
            lightDir = XMVector3TransformNormal(lightDir, worldToView);
            XMStoreFloat3(&psConstants.Lights[psConstants.NumLights].Direction, lightDir);

            ++psConstants.NumLights;
        }
    }

    FinalPassPSCB->Update(&psConstants, sizeof(psConstants));

    // Remainder of data is object-specific
    FinalPassVSConstants constants{};

    for (auto& visual : Visuals)
    {
        XMMATRIX localToWorld = XMLoadFloat4x4(&visual->GetLocalToWorld());
        XMStoreFloat4x4(&constants.LocalToView, XMMatrixMultiply(localToWorld, worldToView));
        XMStoreFloat4x4(&constants.LocalToProjection, XMMatrixMultiply(localToWorld, worldToProjection));

        HRESULT hr = FinalPassVSCB->Update(&constants, sizeof(constants));
        if (FAILED(hr))
        {
            assert(false);
            continue;
        }

        pass->SetPSResource(3, visual->GetAlbedoTexture() ? visual->GetAlbedoTexture()->GetSRV() : nullptr);
        pass->SetPSResource(4, visual->GetNormalTexture() ? visual->GetNormalTexture()->GetSRV() : nullptr);

        pass->Draw(visual);
    }

    pass->End();

    if (MsaaEnabled)
    {
        Context->ResolveSubresource(renderTarget.Texture->GetTexture().Get(), 0, FinalRTMsaa->GetTexture().Get(), 0, FinalRTMsaa->GetDesc().Format);
    }
}