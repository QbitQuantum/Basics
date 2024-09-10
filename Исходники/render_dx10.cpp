void RenderFrameDX10(void)
{
	Vector4 vColorDarkBlue(0.0f, 0.0f, 0.5f, 1.0f);
	Vector4 vColorBlue(0.0f, 0.0f, 0.8f, 1.0f);
	Vector4 vPlane(0.0f, 0.0f, 1.0f, -g_mirror_z);

	D3D10_VIEWPORT mainVP, VP;

	// `取得呼叫GutCreateGraphicsDeviceDX10時所產生的D3D10物件`
	ID3D10RenderTargetView *pRenderTargetView = GutGetDX10RenderTargetView();
	ID3D10DepthStencilView *pDepthStencilView = GutGetDX10DepthStencilView();
	// front/back buffer
	IDXGISwapChain *pSwapChain = GutGetDX10SwapChain(); 

	// `在動態貼圖中畫出鏡射的茶壼`
	{
		UINT nViewports = 1;
		g_pDevice->RSGetViewports(&nViewports, &mainVP);

		// new rendertarget viewport size
		VP.TopLeftX = VP.TopLeftY = 0;
		VP.Width = VP.Height = 512;
		VP.MinDepth = 0.0f;
		VP.MaxDepth = 1.0f;

		ID3D10ShaderResourceView *null_views[4] = {NULL, NULL, NULL, NULL};
		g_pDevice->PSSetShaderResources(0, 4, null_views);
		// `使用代表動態貼圖的`RenderTarget
		g_pDevice->OMSetRenderTargets(1, &g_pRGBAView, g_pDepthStencilView);
		//
		g_pDevice->RSSetViewports(1, &VP);
		// `清除顏色`
		g_pDevice->ClearRenderTargetView(g_pRGBAView, (float *)&vColorDarkBlue);
		// `清除`Depth/Stencil buffer
		g_pDevice->ClearDepthStencilView(g_pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
		// `畫鏡射的茶壼`
		RenderModelDX10(true, &vPlane);
	}

	// `在主Framebuffer中畫出正常的茶壼`
	{
		// `使用主`framebuffer
		g_pDevice->OMSetRenderTargets(1, &pRenderTargetView, pDepthStencilView);
		//
		g_pDevice->RSSetViewports(1, &mainVP);
		// `清除顏色`
		g_pDevice->ClearRenderTargetView(pRenderTargetView, (float *)&vColorBlue);
		// `清除`Depth/Stencil buffer
		g_pDevice->ClearDepthStencilView(pDepthStencilView, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0);
		// `畫茶壼`
		RenderModelDX10(false, &vPlane);
	}

	// `在主framebuffer中畫出鏡面`
	{
		UINT stride = sizeof(Vertex_VT);
		UINT offset = 0;
		// `設定`vertex shader
		g_pDevice->VSSetShader(g_pVertexShader);
		// `設定`pixel shader
		g_pDevice->PSSetShader(g_pPixelShader);
		// `設定`Shader Constants
		g_pDevice->VSSetConstantBuffers(0, 1, &g_pVSConstBuffer);
		// `設定vertex資料格式`
		g_pDevice->IASetInputLayout(g_pVertexLayout);
		// `設定三角形頂點索引值資料排列是triangle strip`
		g_pDevice->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		// Vertex Buffer
		g_pDevice->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
		// `計算`texture matrix
		Matrix4x4 uv_offset_matrix;
		uv_offset_matrix.Scale_Replace(0.5f, -0.5f, 1.0f);
		uv_offset_matrix[3].Set(0.5f, 0.5f, 0.0f, 1.0f);
		Matrix4x4 texture_matrix = g_mirror_view_matrix * g_proj_matrix * uv_offset_matrix;

		Vertex_VT *pVertices = NULL;
		g_pVertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, NULL, (void **) &pVertices);
		for ( int i=0; i<4; i++ )
		{
			Vector4 vPosition = g_Quad[i].m_Position;
			Vector4 vTexcoord = vPosition * texture_matrix;
			vTexcoord /= vTexcoord.GetW();

			pVertices[i].m_Position = vPosition;
			pVertices[i].m_Texcoord = vTexcoord;
		}
		g_pVertexBuffer->Unmap();

		// `計算矩陣`
		Matrix4x4 view_matrix = g_Control.GetViewMatrix();
		Matrix4x4 wvp_matrix = view_matrix * g_proj_matrix;
		// `更新shader參數`
		Matrix4x4 *pConstData;
		g_pVSConstBuffer->Map( D3D10_MAP_WRITE_DISCARD, NULL, (void **) &pConstData );
		*pConstData = wvp_matrix;
		g_pVSConstBuffer->Unmap();
		// `套用第1張貼圖`
		g_pDevice->PSSetShaderResources(0, 1, &g_pTextureView);
		g_pDevice->PSSetSamplers(0, 1, &g_pSamplerState);
		// `畫出格子`
		g_pDevice->Draw(4, 0);
	}

	// `等待硬體掃結束, 然後才更新畫面.`
	pSwapChain->Present(1, 0);
}