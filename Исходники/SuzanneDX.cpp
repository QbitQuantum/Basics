void SuzanneDX::RenderShadowMaps()
{
	D3D11_TEXTURE2D_DESC shadowMapDesc;
	ZeroMemory(&shadowMapDesc, sizeof(shadowMapDesc));
	shadowMapDesc.Width = SHADOW_RESOLUTION;
	shadowMapDesc.Height = SHADOW_RESOLUTION;
	shadowMapDesc.MipLevels = 1;
	shadowMapDesc.ArraySize = 1;
	shadowMapDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	shadowMapDesc.SampleDesc.Count = 1;
	shadowMapDesc.SampleDesc.Quality = 0;
	shadowMapDesc.Usage = D3D11_USAGE_DEFAULT;
	shadowMapDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	shadowMapDesc.CPUAccessFlags = 0;
	shadowMapDesc.MiscFlags = 0;

	D3D11_DEPTH_STENCIL_VIEW_DESC shadowMapDsvDesc;
	ZeroMemory(&shadowMapDsvDesc, sizeof(shadowMapDsvDesc));
	shadowMapDsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	shadowMapDsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	shadowMapDsvDesc.Texture2D.MipSlice = 0;

	D3D11_SHADER_RESOURCE_VIEW_DESC shadowMapResourceDesc;
	ZeroMemory(&shadowMapResourceDesc, sizeof(shadowMapResourceDesc));
	shadowMapResourceDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	shadowMapResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shadowMapResourceDesc.Texture2D.MipLevels = 1;
	shadowMapResourceDesc.Texture2D.MostDetailedMip = 0;

	D3D11_VIEWPORT shadowMapViewport;
	shadowMapViewport.Width = (FLOAT)SHADOW_RESOLUTION;
	shadowMapViewport.Height = (FLOAT)SHADOW_RESOLUTION;
	shadowMapViewport.MinDepth = 0.0f;
	shadowMapViewport.MaxDepth = 1.0f;
	shadowMapViewport.TopLeftX = 0;
	shadowMapViewport.TopLeftY = 0;
	mDeviceContext->RSSetViewports(1, &shadowMapViewport);

	XMMATRIX shadowViewProjectionMatrices[NUMBER_OF_LIGHTS];
	for (int i = 0; i < NUMBER_OF_LIGHTS; ++i)
	{
		ID3D11Texture2D* shadowMap;
		mDevice->CreateTexture2D(&shadowMapDesc, NULL, &shadowMap);

		ID3D11DepthStencilView* shadowMapDsv;
		mDevice->CreateDepthStencilView(shadowMap, &shadowMapDsvDesc, &shadowMapDsv);

		mDevice->CreateShaderResourceView(shadowMap, &shadowMapResourceDesc, &shadowMapResources[i]);

		mDeviceContext->OMSetRenderTargets(0, 0, shadowMapDsv);
		mDeviceContext->ClearDepthStencilView(shadowMapDsv, D3D11_CLEAR_DEPTH, 1.0f, 0);

		XMVECTOR lightInvDir = XMVector3Normalize(XMVectorSet(lighting.lights[i].position.x, lighting.lights[i].position.y, lighting.lights[i].position.z, 1.0f));
		XMMATRIX shadowProjectionMatrix = XMMatrixOrthographicRH(20, 20, -10, 20);
		XMMATRIX shadowViewMatrix = XMMatrixLookAtRH(lightInvDir, XMVectorSet(0, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
		shadowViewProjectionMatrices[i] = shadowViewMatrix * shadowProjectionMatrix;

		ID3D11Buffer* shadowViewProjectionMatrixBuffer = DXUtil::CreateMatrixBuffer(mDevice, shadowViewProjectionMatrices[i]);
		mDeviceContext->VSSetConstantBuffers(shadowViewProjectionMatrixBufferSlot, 1, &shadowViewProjectionMatrixBuffer);

		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		for (ModelDX model : models)
		{
			mDeviceContext->IASetVertexBuffers(0, 1, &model.vertexBuffer, &stride, &offset);
			mDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			mDeviceContext->IASetInputLayout(model.inputLayout);

			mDeviceContext->VSSetShader(shadowVertexShader, 0, 0);
			mDeviceContext->PSSetShader(shadowPixelShader, 0, 0);

			mDeviceContext->VSSetConstantBuffers(modelMatrixBufferSlot, 1, &model.modelMatrixBuffer);

			mDeviceContext->Draw(model.vertexCount, 0);
		}

		shadowMap->Release();
		shadowMapDsv->Release();
		shadowViewProjectionMatrixBuffer->Release();
	}

	mDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	mDeviceContext->RSSetViewports(1, &mViewport);

	D3D11_BUFFER_DESC matrixDesc;
	ZeroMemory(&matrixDesc, sizeof(matrixDesc));
	matrixDesc.ByteWidth = sizeof(XMMATRIX) * NUMBER_OF_LIGHTS;
	matrixDesc.Usage = D3D11_USAGE_DEFAULT;
	matrixDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA matrixData;
	ZeroMemory(&matrixData, sizeof(matrixData));
	matrixData.pSysMem = &shadowViewProjectionMatrices[0];

	ID3D11Buffer* matrixBuffer;
	mDevice->CreateBuffer(&matrixDesc, &matrixData, &matrixBuffer);

	mDeviceContext->VSSetConstantBuffers(shadowViewProjectionMatrixBufferSlot, 1, &matrixBuffer);
	matrixBuffer->Release();

	XMMATRIX biasMatrix = XMMatrixSet(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.5, 0.5, 0.0, 1.0
		);

	ID3D11Buffer* shadowBiasMatrixBuffer = DXUtil::CreateMatrixBuffer(mDevice, biasMatrix);
	mDeviceContext->VSSetConstantBuffers(shadowBiasMatrixBufferSlot, 1, &shadowBiasMatrixBuffer);
	shadowBiasMatrixBuffer->Release();
}