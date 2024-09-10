void GameSystem::Render()
{
	gameTime.Update();
	//gameTime.ShowFPS();

	cam.Update();
	//UPPDATING MATRIXBUFFER
	//Check for input
	cam.Input(gameTime.DeltaTime(), mainHwnd.getHWND());

	//--------------UPDATING MATRIXES-----------------------------
	XMFLOAT3 Pos = cam.getPos();
	if (!cam.flying)
	{
	Pos.y = hMap.HMap(Pos.x, Pos.z) + 10.0f;
	cam.setPos(Pos);
	}

	XMStoreFloat4x4(&matrix.View, XMMatrixTranspose(cam.GetViewMa()));
	XMStoreFloat4x4(&matrix.Proj, XMMatrixTranspose(cam.GetProjMa()));

	D3D11_MAPPED_SUBRESOURCE MapDATA;
	Matrix* temp;
	ZeroMemory(&MapDATA, sizeof(MapDATA));

	deviceContext->Map(MatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MapDATA);

	temp = (Matrix*)MapDATA.pData;
	temp->World = matrix.World;
	temp->View =  matrix.View;
	temp->Proj = matrix.Proj;
	deviceContext->Unmap(MatrixBuffer, 0);
	ZeroMemory(&MapDATA, sizeof(MapDATA));

	deviceContext->Map(GeomBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &MapDATA);
	memcpy(MapDATA.pData,&Pos, sizeof(XMFLOAT3));
	deviceContext->Unmap(GeomBuff, 0);
	//--------------UPDATING MATRIXES-----------------------------
	//TEST
	//testView = XMMatrixLookAtLH(XMVectorSet(0.0, -100, 0.0, 1.0), XMVectorSet(Pos.x,Pos.y,Pos.z,1), XMVectorSet(0, 1, 0, 1));
	//TEST

	//Shadow
	DeferedRendering.setLayout(deviceContext);

	deviceContext->VSSetConstantBuffers(1, 1, &SunBuffer);
	shadow.prepRun(deviceContext);

	//hMap.renderFrustCull(deviceContext, cam.GetProjMa(), cam.GetViewMa());
	hMap.render(deviceContext); 
	obj.render(deviceContext);

	shadow.close(deviceContext);

	deviceContext->VSSetConstantBuffers(0, 1, &MatrixBuffer);

	DeferedRendering.setGBufferShaders(deviceContext);
	DeferedRendering.clearBuffer(deviceContext);

	DeferedRendering.OMSetRender(device, deviceContext, directX.getDepthView(deviceContext));

	deviceContext->VSSetConstantBuffers(0, 1, &MatrixBuffer);

	//draw obj
	if (GetAsyncKeyState('L') & 0x8000)
	{
		if (frustLock)
			frustLock = false;
		else
			frustLock = true;
	}

	if (!frustLock)
	{
		viewLock = cam.GetViewMa();
	}




	hMap.renderFrustCull(deviceContext, cam.GetProjMa(),viewLock);

	//hMap.render(deviceContext);
	obj.render(deviceContext);

	DeferedRendering.nullRender(deviceContext);
	DeferedRendering.setShaderResources(deviceContext);

	//SSAO
	XMFLOAT4X4 oTemp;

	XMStoreFloat4x4(&oTemp, XMMatrixMultiplyTranspose(cam.GetViewMa(), cam.GetProjMa()));
	
	Ssao.renderPass(device, deviceContext, oTemp);

	//Finalising and drawing
	DeferedRendering.setBackBufferShaders(deviceContext);

	//Rendertarget
	DeferedRendering.OMSetBackBuff(deviceContext);

	deviceContext->PSSetConstantBuffers(0, 1, &LightBuffer);
	deviceContext->PSSetConstantBuffers(3, 1, &SunBuffer);
	DeferedRendering.Render(device, deviceContext);

	//kolla shadowmappen
	swapChain->Present(0, 0);

	XMFLOAT3 posT = cam.getPos();

	std::cout <<"Curreny Position: X:"<< posT.x<<" Y: " <<posT.y<<"Z: "<< posT.z<< endl;

	DeferedRendering.CloseBuffers(deviceContext);
}