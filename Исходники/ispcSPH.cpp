//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Update our time
    static float t = 0.0f;
    float delta_t = 0.0f;
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if( dwTimeStart == 0 )
            dwTimeStart = dwTimeCur;
        float old_t = t;
        t = ( dwTimeCur - dwTimeStart ) / 1000.0f;
        delta_t = t-old_t;
    }

    {
        sphParticle particles[32];
        for(size_t i=0; i<_countof(particles); ++i) {
            particles[i].position = ist::simdvec4_set(GenRand()*0.5f, GenRand()*0.5f, GenRand()*0.5f-7.5f, 1.0f);
            particles[i].velocity = _mm_set1_ps(0.0f);
        }
        g_sphgrid.addParticles(particles, _countof(particles));
    }
    {
        static PerformanceCounter s_timer;
        static float s_prev = 0.0f;
        PerformanceCounter timer;

        g_sphgrid.update(1.0f);
        g_pImmediateContext->UpdateSubresource( g_pCubeInstanceBuffer, 0, NULL, &g_sphgrid.particles, 0, 0 );

        if(s_timer.getElapsedMillisecond() - s_prev > 1000.0f) {
            char buf[128];
            _snprintf(buf, _countof(buf), "  SPH update: %d particles %.3fms\n", g_sphgrid.num_active_particles, timer.getElapsedMillisecond());
            OutputDebugStringA(buf);
            ::SetWindowTextA(g_hWnd, buf);
            s_prev = s_timer.getElapsedMillisecond();
        }
    }

    {
        CBChangesEveryFrame cb;
        XMVECTOR eye = g_camera.getEye();
        {
            XMMATRIX rot = XMMatrixRotationZ(XMConvertToRadians(0.1f));
            eye = XMVector4Transform(eye, rot);
        }
        g_camera.setEye(eye);
        g_camera.updateMatrix();
        XMMATRIX vp = g_camera.getViewProjectionMatrix();

        cb.ViewProjection   = XMMatrixTranspose( vp );
        cb.CameraPos        = (FLOAT*)&eye;

        cb.LightPos         = XMFLOAT4(10.0f, 10.0f, -10.0f, 1.0f);
        cb.LightColor       = XMFLOAT4(0.9f, 0.9f, 0.9f, 1.0f);

        cb.MeshShininess    = 200.0f;
        g_pImmediateContext->UpdateSubresource( g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0 );
    }


    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha
    g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );
    g_pImmediateContext->ClearDepthStencilView( g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

    {
        ID3D11Buffer *buffers[] = {g_pCubeVertexBuffer, g_pCubeInstanceBuffer};
        UINT strides[] = {sizeof(SimpleVertex), sizeof(sphParticle), };
        UINT offsets[] = {0, 0};
        g_pImmediateContext->IASetVertexBuffers( 0, ARRAYSIZE(buffers), buffers, strides, offsets );
    }
    g_pImmediateContext->IASetInputLayout( g_pCubeVertexLayout );
    g_pImmediateContext->IASetIndexBuffer( g_pCubeIndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
    g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    // Render the cube
    g_pImmediateContext->VSSetShader( g_pCubeVertexShader, NULL, 0 );
    g_pImmediateContext->VSSetConstantBuffers( 0, 1, &g_pCBChangesEveryFrame );
    g_pImmediateContext->PSSetShader( g_pCubePixelShader, NULL, 0 );
    g_pImmediateContext->PSSetConstantBuffers( 0, 1, &g_pCBChangesEveryFrame );

    g_pImmediateContext->DrawIndexedInstanced( 36, (UINT)g_sphgrid.num_active_particles, 0, 0, 0 );

    // Present our back buffer to our front buffer
    g_pSwapChain->Present( 1, 0 ); // vsync on
    //g_pSwapChain->Present( 0, 0 ); // vsync off
}