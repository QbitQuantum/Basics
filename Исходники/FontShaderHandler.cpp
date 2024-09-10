bool FontShaderHandler::SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D11ShaderResourceView* fontTexture, XMFLOAT3 color)
{
	HRESULT hresult;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferSimple* dataPtr;
	unsigned int bufferNumber;

	//Transpose each matrix to prepare for shaders (requirement in directx 11)
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	//Map the constant buffer so we can write to it (denies GPU access)
	hresult = deviceContext->Map(this->matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hresult)) {
		return false;
	}

	//Get pointer to the data
	dataPtr = (MatrixBufferSimple*)mappedResource.pData;

	//Copy the matrices to the constant buffer
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;
	dataPtr->color = color;

	//Unmap the constant buffer to give the GPU access agin
	deviceContext->Unmap(this->matrixBuffer, 0);

	//Set constant buffer position in vertex shader
	bufferNumber = 0;

	//Set the constant buffer in vertex and pixel shader with updated values
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &this->matrixBuffer);
	deviceContext->PSSetConstantBuffers(bufferNumber, 1, &this->matrixBuffer);

	if (fontTexture) {
		//Set shader color texture resource for pixel shader
		deviceContext->PSSetShaderResources(0, 1, &fontTexture);
	}

	deviceContext->OMSetBlendState(this->transparencyBlendState, NULL, 0xffffffff);

	return true;
}