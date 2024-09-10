/*--------------------------------------------
	画面の描画処理
--------------------------------------------*/
HRESULT Render(void)
{
	HRESULT hr;

	// 定数バッファを更新
	// ワールド変換行列
	XMFLOAT3 center = g_wfObjKuma.GetBoundingSphereCenter();
	XMMATRIX matTrans = XMMatrixTranslation(-center.x, -center.y, -center.z);

	float scale = 1.0f / g_wfObjKuma.GetBoundingSphereRadius();
	XMMATRIX matScale = XMMatrixScaling(scale, scale, scale);

	FLOAT rotate = (FLOAT)(XM_PI * (timeGetTime() % 3000)) / 1500.0f;
	XMMATRIX matY = XMMatrixRotationY(rotate);

	XMMATRIX matWorld = matTrans * matScale * matY;
	XMStoreFloat4x4(&g_cbCBuffer.World, XMMatrixTranspose(matWorld));

	// ***************************************
	// シャドウ マップの描画
	if (g_bShadowMappingMode) {
		g_pImmediateContext->ClearState();

		// ビュー変換行列(光源から見る)
		XMVECTORF32 focusPosition = { 0.0f, 0.0f,  0.0f };  // 注視点
		XMVECTORF32 upDirection   = { 0.0f, 1.0f,  0.0f };  // カメラの上方向
		XMMATRIX matShadowMapView = XMMatrixLookAtLH(XMLoadFloat3(&g_vLightPos), focusPosition, upDirection);
		XMStoreFloat4x4(&g_cbCBuffer.View, XMMatrixTranspose(matShadowMapView));

		// 射影変換行列(パースペクティブ(透視法)射影)
		XMMATRIX matShadowMapProj = XMMatrixPerspectiveFovLH(
				XMConvertToRadians(45.0f),		// 視野角45°
				g_ViewPortShadowMap[0].Width / g_ViewPortShadowMap[0].Height,	// アスペクト比
				1.0f,							// 前方投影面までの距離
				400.0f);						// 後方投影面までの距離
		XMStoreFloat4x4(&g_cbCBuffer.Projection, XMMatrixTranspose(matShadowMapProj));

		// 深度/ステンシルのクリア
		g_pImmediateContext->ClearDepthStencilView(g_pShadowMapDSView, D3D11_CLEAR_DEPTH, 1.0f, 0);

		// VSに定数バッファを設定
		g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBuffer);

		// PSに定数バッファを設定
		g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pCBuffer);
		// PSにサンプラーを設定
		g_pImmediateContext->PSSetSamplers(0, 2, g_pTextureSampler);

		// RSにビューポートを設定
		g_pImmediateContext->RSSetViewports(1, g_ViewPortShadowMap);

		// OMに描画ターゲット ビューと深度/ステンシル・ビューを設定
		ID3D11RenderTargetView* pRender[1] = { NULL };
		g_pImmediateContext->OMSetRenderTargets(1, pRender, g_pShadowMapDSView);

		// 物体の描画
		RenderObj(true);

		// シャドウマップの設定
		XMMATRIX mat = XMMatrixTranspose(matWorld * matShadowMapView * matShadowMapProj);
		XMStoreFloat4x4(&g_cbCBuffer.SMWorldViewProj, mat);
	}

	// ***************************************
	// ビュー変換行列
	XMVECTORF32 eyePosition   = { 0.0f, g_fEye, -g_fEye, 1.0f };  // 視点(カメラの位置)
	XMVECTORF32 focusPosition = { 0.0f, 0.0f,  0.0f, 1.0f };  // 注視点
	XMVECTORF32 upDirection   = { 0.0f, 1.0f,  0.0f, 1.0f };  // カメラの上方向
	XMMATRIX matView = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	XMStoreFloat4x4(&g_cbCBuffer.View, XMMatrixTranspose(matView));
	// 射影変換行列(パースペクティブ(透視法)射影)
	XMMATRIX matProj = XMMatrixPerspectiveFovLH(
			XMConvertToRadians(30.0f),		// 視野角30°
			g_ViewPort[0].Width / g_ViewPort[0].Height,	// アスペクト比
			1.0f,							// 前方投影面までの距離
			20.0f);						// 後方投影面までの距離
	XMStoreFloat4x4(&g_cbCBuffer.Projection, XMMatrixTranspose(matProj));
	// 点光源座標
	XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&g_vLightPos), matView);
	XMStoreFloat3(&g_cbCBuffer.Light, vec);

	// ***************************************
    // 描画ターゲットのクリア
    g_pImmediateContext->ClearRenderTargetView(
                       g_pRenderTargetView, // クリアする描画ターゲット
                       g_ClearColor);         // クリアする値

	// 深度/ステンシルのクリア
	g_pImmediateContext->ClearDepthStencilView(
			g_pDepthStencilView, // クリアする深度/ステンシル・ビュー
			D3D11_CLEAR_DEPTH,   // 深度値だけをクリアする
			1.0f,                // 深度バッファをクリアする値
			0);                  // ステンシル・バッファをクリアする値(この場合、無関係)

	// ***************************************
	g_pImmediateContext->ClearState();

	// VSに定数バッファを設定
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBuffer);

	// PSに定数バッファを設定
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pCBuffer);
	// PSにサンプラーを設定
	g_pImmediateContext->PSSetSamplers(0, 2, g_pTextureSampler);

	// RSにビューポートを設定
	g_pImmediateContext->RSSetViewports(1, g_ViewPort);

	// OMに描画ターゲット ビューと深度/ステンシル・ビューを設定
	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_bDepthMode ? g_pDepthStencilView : NULL);

	// 物体の描画
	RenderObj(false);

	// ***************************************
	// バック バッファの表示
	hr = g_pSwapChain->Present(	0,	// 画面を直ぐに更新する
								0);	// 画面を実際に更新する

	return hr;
}