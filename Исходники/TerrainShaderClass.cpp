bool TerrainShaderClass::SetShadowConstantBufferParamters(ID3D11DeviceContext* pDeviceContext, ObjectClass* pObject, CameraClass* pCamera, PointLightClass* pPointLight)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ShadowBuffer* dataPtr;
	unsigned int bufferNumber;

	// Lock the constant buffer so it can be written to.
	result = pDeviceContext->Map(mShadowBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (ShadowBuffer*)mappedResource.pData;
	
	XMMATRIX world = XMLoadFloat4x4(&pObject->GetWorldMatrix());

	XMMATRIX view = XMLoadFloat4x4(&pCamera->GetViewMatrix());
	XMMATRIX proj = XMLoadFloat4x4(&pCamera->GetProjMatrix());

	XMMATRIX lview = XMLoadFloat4x4(&pPointLight->GetViewMatrix());
	XMMATRIX lproj = XMLoadFloat4x4(&pPointLight->GetProjMatrix());

	XMMATRIX lWVP = XMMatrixTranspose(world*lview*lproj);
	XMMATRIX WVP = XMMatrixTranspose(world*view*proj);


	XMStoreFloat4x4(&dataPtr->worldViewProj, WVP);
	XMStoreFloat4x4(&dataPtr->world, world);
	XMStoreFloat4x4(&dataPtr->LightWorldViewProj, lWVP);
	XMFLOAT3 cP = pCamera->GetPosition();
	dataPtr->camPos = XMFLOAT4(cP.x, cP.y, cP.z, 0);

	// Unlock the constant buffer.
	pDeviceContext->Unmap(mShadowBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Set the constant buffer in the shader with the updated values.
	pDeviceContext->GSSetConstantBuffers(bufferNumber, 1, &mShadowBuffer);

	return true;
}