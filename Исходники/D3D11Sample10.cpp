/*--------------------------------------------
	画面の描画処理
--------------------------------------------*/
HRESULT Render(void)
{
	HRESULT hr;

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
	// 立方体の描画

	// 定数バッファ�Aを更新
	// ビュー変換行列
	XMVECTORF32 eyePosition   = { 0.0f, 5.0f, -5.0f, 1.0f };  // 視点(カメラの位置)
	XMVECTORF32 focusPosition = { 0.0f, 0.0f,  0.0f, 1.0f };  // 注視点
	XMVECTORF32 upDirection   = { 0.0f, 1.0f,  0.0f, 1.0f };  // カメラの上方向
	XMMATRIX mat = XMMatrixLookAtLH(eyePosition, focusPosition, upDirection);
	XMStoreFloat4x4(&g_cbCBuffer.View, XMMatrixTranspose(mat));
	// 点光源座標
	XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&g_vLightPos), mat);
	XMStoreFloat3(&g_cbCBuffer.Light, vec);
	// ワールド変換行列
	XMMATRIX matY, matX;
	FLOAT rotate = (FLOAT)(XM_PI * (timeGetTime() % 3000)) / 1500.0f;
	matY = XMMatrixRotationY(rotate);
	rotate = (FLOAT)(XM_PI * (timeGetTime() % 1500)) / 750.0f;
	matX = XMMatrixRotationX(rotate);
	XMStoreFloat4x4(&g_cbCBuffer.World, XMMatrixTranspose(matY * matX));
	// 定数バッファのマップ取得
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	hr = g_pImmediateContext->Map(
	                  g_pCBuffer,              // マップするリソース
	                  0,                       // サブリソースのインデックス番号
	                  D3D11_MAP_WRITE_DISCARD, // 書き込みアクセス
	                  0,                       //
	                  &MappedResource);        // データの書き込み先ポインタ
	if (FAILED(hr))
		return DXTRACE_ERR(L"InitBackBuffer  g_pImmediateContext->Map", hr);  // 失敗
	// データ書き込み
	CopyMemory(MappedResource.pData, &g_cbCBuffer, sizeof(cbCBuffer));
	// マップ解除
	g_pImmediateContext->Unmap(g_pCBuffer, 0);

	// ***************************************
	// IAに頂点バッファを設定
	// IAに入力レイアウト・オブジェクトを設定(頂点バッファなし)
	g_pImmediateContext->IASetInputLayout(NULL);
	// IAにプリミティブの種類を設定
	g_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// VSに頂点シェーダを設定
	g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
	// VSに定数バッファを設定
	g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBuffer);

	// GSにジオメトリ・シェーダを設定
	g_pImmediateContext->GSSetShader(g_pGeometryShader, NULL, 0);
	// GSに定数バッファを設定
	g_pImmediateContext->GSSetConstantBuffers(0, 1, &g_pCBuffer);

	// RSにビューポートを設定
	g_pImmediateContext->RSSetViewports(1, g_ViewPort);
	// RSにラスタライザ・ステート・オブジェクトを設定
	g_pImmediateContext->RSSetState(g_pRasterizerState);

	// PSにピクセル・シェーダを設定
	g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
	// PSに定数バッファを設定
	g_pImmediateContext->PSSetConstantBuffers(0, 1, &g_pCBuffer);
	// PSにシェーダ・リソース・ビューを設定
	g_pImmediateContext->PSSetShaderResources(
        0,                // 設定する最初のスロット番号
        1,                // 設定するシェーダ・リソース・ビューの数
        &g_pTextureSRV);  // 設定するシェーダ・リソース・ビューの配列
	// PSにサンプラーを設定
	g_pImmediateContext->PSSetSamplers(0, 1, &g_pTextureSampler);

	// OMに描画ターゲット ビューと深度/ステンシル・ビューを設定
	g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_bDepthMode ? g_pDepthStencilView : NULL);
	// OMにブレンド・ステート・オブジェクトを設定
	FLOAT BlendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	g_pImmediateContext->OMSetBlendState(g_pBlendState, BlendFactor, 0xffffffff);
	// OMに深度/ステンシル・ステート・オブジェクトを設定
	g_pImmediateContext->OMSetDepthStencilState(g_pDepthStencilState, 0);

	// ***************************************
	// 頂点バッファとインデックス・バッファを使わずに描画する
	g_pImmediateContext->Draw(
			36, // 描画する頂点数
			0); // 最初の頂点ID

	// ***************************************
	// バック バッファの表示
	hr = g_pSwapChain->Present(	0,	// 画面を直ぐに更新する
								0);	// 画面を実際に更新する

	return hr;
}