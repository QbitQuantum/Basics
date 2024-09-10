bool Shader::SetConstants(ID3D11DeviceContext* context, Matrix world, Matrix view, Matrix projection)
{
	//This method copies the provided matrices over to the constant buffer

	D3D11_MAPPED_SUBRESOURCE mappedResource;	//To do this we us the Map method, this method gives us a "Mapped Subresource", that will end up here
	MatrixBuffer* inputData;

	//We call the Map method and pass in our Mapped Subresource struct, the method will fill it out for us
	if (FAILED(context->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return false;
	}
	
	inputData = (MatrixBuffer*)mappedResource.pData;	//The pData pointer in the Mapped Subresource points to the memory within the buffer, so we cast it to a MatrixBuffer

	inputData->world = world.Transpose();				//and fill it out!
	inputData->view = view.Transpose();					//The matrices we use a in row-major format, HLSL assumes column-major format so we transpose them
	inputData->projection = projection.Transpose();		//as we pass them into the matrix buffer

	context->Unmap(m_matrixBuffer, 0);					//Unmapping the subresource frees it and finishes the process

	return true;
}