void CRtwShadowRenderer::DrawFinal()
{

    GetDX11Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
    GetDX11Context()->OMSetDepthStencilState(DepthStencilStates::DepthTestDSS, 0);


    if( GetAsyncKeyState('2') & 0x8000 )
        GetDX11Context()->RSSetState(RasterizerStates::WireframeRS);

    GetDX11Context()->OMSetBlendState(BlendStates::AlphaBlendBS, 0, 0xffffffff);

    GetDX11Context()->RSSetViewports(1, &m_finalScreenViewport);

    static float bgColor[4] = {(0.0f, 0.0f, 0.0f, 0.0f)};

    GetDX11Context()->ClearRenderTargetView(Globals::Get().device.m_renderTargetView, bgColor);
    GetDX11Context()->ClearDepthStencilView(Globals::Get().device.m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    GetDX11Context()->OMSetRenderTargets(1, &Globals::Get().device.m_renderTargetView, Globals::Get().device.m_depthStencilView);


    //////////

    GetDX11Context()->HSSetShader(m_finalHS, 0, 0);
    GetDX11Context()->DSSetShader(m_finalDS, 0, 0);

    //////////

    GetDX11Context()->VSSetShader(m_finalVS, 0, 0);
    GetDX11Context()->PSSetShader(m_finalPS, 0, 0);

    GetDX11Context()->IASetInputLayout(m_inputLayout);

    GetDX11Context()->PSSetSamplers(0, 1, &SamplerStates::PointWrapSampler);
    GetDX11Context()->PSSetSamplers(1, 1, &SamplerStates::DefaultSamplerWrap);
    GetDX11Context()->PSSetSamplers(2, 1, &SamplerStates::DefaultSamplerClamp);

    

    int modelsCount = Globals::Get().scene.m_models.size();

    for(int i = 0; i < modelsCount; i++)
    {
        D3DPERF_BeginEvent(D3DCOLOR_XRGB(255, 0, 0), L"DRAW_FINAL_WITH_SHADOW"); 

        XMMATRIX world =  Globals::Get().scene.m_models[i]->m_transformation.GetWorld();

        XMMATRIX lightView       = XMLoadFloat4x4(&GetRenderer().mLightView);
        XMMATRIX lightProj       = XMLoadFloat4x4(&GetRenderer().mLightProj);
        XMMATRIX lightViewProj   = XMMatrixMultiply(lightView, lightProj);


        SRenderFinalVSCbuffer cbufferVS;
        cbufferVS.mtxView        = XMMatrixTranspose(GetCamera().GetView());
        cbufferVS.mtxProj        = XMMatrixTranspose(GetCamera().GetProj());
        cbufferVS.mtxWorld       = XMMatrixTranspose(world);
        cbufferVS.mtxWorldIt     = XMMatrixTranspose(XMMatrixInverse(&XMMatrixDeterminant(world), world));
        cbufferVS.mtxShadowVP    = XMMatrixTranspose(lightViewProj);
        cbufferVS.g_texScale     = Globals::Get().scene.m_models[i]->texScale;

        GetDX11Context()->UpdateSubresource(m_finalVSCBuffer, 0, NULL, &cbufferVS, 0, 0);
        GetDX11Context()->VSSetConstantBuffers(0, 1, &m_finalVSCBuffer);

        ///////
                GetDX11Context()->DSSetConstantBuffers(0, 1, &m_finalVSCBuffer);
        ///////

        SRenderFinalPSCBuffer cbufferPS;
        cbufferPS.lightDir.x = GetGlobalState().GetSun().Direction.x;
        cbufferPS.lightDir.y = GetGlobalState().GetSun().Direction.y;
        cbufferPS.lightDir.z = GetGlobalState().GetSun().Direction.z;

        GetDX11Context()->UpdateSubresource(m_finalPSCBuffer, 0, NULL, &cbufferPS, 0, 0);
        GetDX11Context()->PSSetConstantBuffers(0, 1, &m_finalPSCBuffer);

        /////////// set textures
        GetDX11Context()->PSSetShaderResources(0, 1, &Globals::Get().scene.m_models[i]->m_material->m_diffuseRV);
        GetDX11Context()->PSSetShaderResources(1, 1, &m_warpedShadowMap);
        GetDX11Context()->PSSetShaderResources(2, 1, &m_horizWarpSRV);
        GetDX11Context()->PSSetShaderResources(3, 1, &m_vertWarpSRV);


        uint offset = 0;
        GetDX11Context()->IASetIndexBuffer(Globals::Get().scene.m_models[i]->m_mesh->m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
        GetDX11Context()->IASetVertexBuffers(0, 1, &Globals::Get().scene.m_models[i]->m_mesh->m_vertexBuffer, &Globals::Get().scene.m_models[i]->m_mesh->m_stride, &offset);


        GetDX11Context()->DrawIndexed(Globals::Get().scene.m_models[i]->m_mesh->m_indexCount, 0, 0 );

        D3DPERF_EndEvent();
    }

    GetDX11Context()->HSSetShader(NULL, 0, 0);
    GetDX11Context()->DSSetShader(NULL, 0, 0);

        GetDX11Context()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}