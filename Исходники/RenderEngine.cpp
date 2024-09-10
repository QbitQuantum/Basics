void RenderEngine::Render(){
	static float rot = 0.00f;
	UINT32 vertexSize = sizeof(float) * 8;
	UINT32 offset = 0;
	rot += 0.01;
	float clearColor[] = { 0.15f,0.6f,1.0f, 0.2f };
	gDeviceContext->OMSetBlendState(0, 0, 0xffffffff);
	gDeviceContext->ClearRenderTargetView(gBackRufferRenderTargetView, clearColor);
	gDeviceContext->ClearDepthStencilView(gDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	mainCamera.setPlayerXPos(theCharacter->xPos);
	mainCamera.setPlayerYPos(theCharacter->yPos);

	mainCamera.updateCamera();
	//WORLD
	XMMATRIX YRotation = XMMatrixRotationY(rot);

	//The Camera Matrices are now defined in the camera class (mainCamera)

	XMMATRIX CamView = mainCamera.getCamView();
	XMMATRIX CamProjection = mainCamera.getCamProjection();
	XMMATRIX identityM = XMMatrixIdentity();
	XMMATRIX WorldInv = XMMatrixInverse(nullptr, XMMatrixIdentity());

	World perObjCBData;

	XMMATRIX WVP;
	WVP = identityM* CamView*CamProjection;


	XMStoreFloat4x4(&perObjCBData.WVP, XMMatrixTranspose(WVP));
	XMStoreFloat4x4(&perObjCBData.View, XMMatrixTranspose(CamView));
	XMStoreFloat4x4(&perObjCBData.Projection, XMMatrixTranspose(CamProjection));
	XMStoreFloat4x4(&perObjCBData.WorldSpace, XMMatrixTranspose(XMMatrixIdentity()));
	XMStoreFloat4x4(&perObjCBData.InvWorld, XMMatrixTranspose(WorldInv));

	
	gDeviceContext->UpdateSubresource(gWorld, 0, NULL, &perObjCBData, 0, 0);
	gDeviceContext->VSSetConstantBuffers(0, 1, &gWorld);
	gDeviceContext->IASetVertexBuffers(0, 1, &gVertexBuffer, &vertexSize, &offset);
	
	ID3D11Buffer *pShaderBuffers[2] = { matConstBuff, lightConstBuff };
	gDeviceContext->PSSetConstantBuffers(0, 2, pShaderBuffers);

	//RENDER OBJ FILES

	for each (GameObject var in gamePlatforms)
	{
			gDeviceContext->PSSetShaderResources(0, 1, &ddsTex1);
	
		gDeviceContext->IASetInputLayout(gVertexLayout);
		gDeviceContext->IASetVertexBuffers(0, 1, &var.vertexBuffer, &vertexSize, &offset);
		gDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		gDeviceContext->VSSetShader(gVertexShader, nullptr, 0);
		gDeviceContext->HSSetShader(nullptr, nullptr, 0);
		gDeviceContext->DSSetShader(nullptr, nullptr, 0);
		gDeviceContext->PSSetShader(gPixelShader, nullptr, 0);
		
		var.CalculateWorld();
		var.material = MatPresets::Emerald;
		var.material.SpecPow = 38.0f;
		
		matProperties.Material = var.material;

		gDeviceContext->UpdateSubresource(matConstBuff, 0, nullptr, &matProperties, 0, 0);
		
		

		XMStoreFloat4x4(&perObjCBData.InvWorld, XMMatrixTranspose(XMMatrixInverse(nullptr, var.world)));
		XMStoreFloat4x4(&perObjCBData.WorldSpace, XMMatrixTranspose(var.world));
		WVP = XMMatrixIdentity();
		WVP = var.world * CamView *CamProjection;

		XMStoreFloat4x4(&perObjCBData.WVP, XMMatrixTranspose(WVP));


		gDeviceContext->UpdateSubresource(gWorld, 0, NULL, &perObjCBData, 0, 0);
		gDeviceContext->VSSetConstantBuffers(0, 1, &gWorld);

		gDeviceContext->Draw(var.nrElements * 3, 0);
		}