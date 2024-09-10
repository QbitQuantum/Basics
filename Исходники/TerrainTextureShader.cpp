void TerrainTextureShader::SetVertexBufferValues(ID3D11DeviceContext* context, const Matrix &wvpMatrix, const Matrix &worldMatrix) const {
	// set buffer values
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	InputBufferVertex* dataPtr;

	// Lock the screen size constant buffer so it can be written to.
	HRESULT result = context->Map(mConstantVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result)) {
		throw std::runtime_error(std::string("TerrainTextureShader: failed to map buffer in SetVertexBufferValues function"));
	}

	dataPtr = (InputBufferVertex*)mappedResource.pData;
	dataPtr->worldMatrix = worldMatrix.Transpose();
	dataPtr->wvpMatrix = wvpMatrix.Transpose();

	context->Unmap(mConstantVertexBuffer,0);	
}