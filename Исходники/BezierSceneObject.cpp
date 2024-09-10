void BezierSceneObject::renderTheScene(GraphicsContext & p_in)
{
	auto * invoker = m_quadInvoker;
	auto * Model = m_model;

	updateIncrement += p_in.deltaTime * 0.01f *  m_model->TweakVariables["timeMod"];

	ID3D11DeviceContext * tempDevice = p_in.GetD3DContext()->GetDeviceContext();
	
	XMMATRIX tempMat;
	Model->ModelMatrix(tempMat);
	Model->UpdateBuffers(p_in.c_d3d->GetDeviceContext(), updateBezierPoints(updateIncrement, m_model->TweakVariables["AmpIncrement"]));
	
	XMMATRIX orbitMatrix = XMMatrixTranslation(10.0f , 0.0f, 0.0f) * XMMatrixRotationY(updateIncrement * 0.1f);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	QuadInvoker::MatrixBufferType *tempMatBuff = invoker->MapCBuffer<QuadInvoker::MatrixBufferType>(tempDevice , "matrixBuffer");
	tempMatBuff->worldMatrix = XMMatrixTranspose(tempMat* orbitMatrix);
	tempMatBuff->viewMatrix = XMMatrixTranspose( *p_in.c_view);
	tempMatBuff->projectionMatrix = XMMatrixTranspose(*p_in.c_projection);
	invoker->UnMapCBuffer(tempDevice , "matrixBuffer");
	tempDevice->VSSetConstantBuffers(0, 1, &invoker->GetBufferMap()["matrixBuffer"]);
	tempDevice->DSSetConstantBuffers(0, 1, &invoker->GetBufferMap()["matrixBuffer"]);

	QuadInvoker::TessellationBufferType *tempTessBuff = invoker->MapCBuffer<QuadInvoker::TessellationBufferType>(tempDevice , "tessBuffer");
	tempTessBuff->cameraPosition = p_in.c_cam->GetPos();
	tempTessBuff->misc = XMFLOAT3();
	tempTessBuff->tessellationAmount = m_model->TweakVariables["TessFactor"];
	tempTessBuff->LODModifier = 0;
	invoker->UnMapCBuffer(tempDevice , "tessBuffer");
	tempDevice->HSSetConstantBuffers(0, 1, &invoker->GetBufferMap()["tessBuffer"]);

	QuadInvoker::LightBufferType *tempLightBuff = invoker->MapCBuffer<QuadInvoker::LightBufferType>(tempDevice, "LightBuffer");
	tempLightBuff->ambientColor = p_in.c_lightInfo->GetAmbientColor();
	tempLightBuff->diffuseColor = p_in.c_lightInfo->GetDiffuseColor();
	tempLightBuff->lightDirection = p_in.c_lightInfo->Getdirection();
	tempLightBuff->specularPower = p_in.c_lightInfo->GetSpecularPower();
	invoker->UnMapCBuffer(tempDevice, "LightBuffer");
	tempDevice->PSSetConstantBuffers(0, 1, &invoker->GetBufferMap()["LightBuffer"]);

	Model->RenderAllBuffers<ModelLightingClass::LightingVertexType> (tempDevice, D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST);
	invoker->RenderShader(tempDevice ,  Model->GetIndexCount());
}