bool TextureShaderClass::SetShaderParameters(Matrix worldMatrix, Matrix viewMatrix,
	Matrix projectionMatrix, ID3D11ShaderResourceView** texture_array, int tipo_, int mouse_status_, Color color_, Vector3 lightPos_, float dimmed_)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;
	Data_* dataPtr2;


	// Transpose the matrices to prepare them for the shader.
	worldMatrix = worldMatrix.Transpose();
	viewMatrix = viewMatrix.Transpose();
	projectionMatrix = projectionMatrix.Transpose();

	// Lock the constant buffer so it can be written to.
	result = D3D_context->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer.
	D3D_context->Unmap(m_matrixBuffer, 0);

	// Set the position of the constant buffer in the vertex shader.
	bufferNumber = 0;

	// Now set the constant buffer in the vertex shader with the updated values.
	D3D_context->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Set shader texture resource in the pixel shader.
	D3D_context->PSSetShaderResources(0, 4, texture_array);

	// Lock the basic constant buffer so it can be written to.
	result = D3D_context->Map(texture_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (Data_*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr2->color = color_;
	dataPtr2->lightPos = lightPos_;
	dataPtr2->extra1 = 0.0f;
	dataPtr2->type_ = float(tipo_);
	dataPtr2->mouse_status = float(mouse_status_);
	dataPtr2->dimmed = dimmed_;
	dataPtr2->extra2 = 0.0f;

	// Unlock the constant buffer.
	D3D_context->Unmap(texture_Buffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	D3D_context->PSSetConstantBuffers(bufferNumber, 1, &texture_Buffer);

	return true;
}