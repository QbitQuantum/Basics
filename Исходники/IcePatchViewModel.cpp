bool IcePatchViewModel::RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, IcePatchObstacle* entity)
{
	//writeTextToConsole(L"IcePatchViewModel::RenderEntity");

	if(!textureShader) return false; //we were not provided with a shader

	XMFLOAT3 positionVector = entity->getPosition();
	positionVector.z += 0.01f;
	positionVector.x -= 1.5f;
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMLoadFloat4x4( &GetOrientation()));

	//SNOWFIELD MODEL RENDER
	XMFLOAT4X4 snowFieldMatrix;
	XMStoreFloat4x4(&snowFieldMatrix, XMLoadFloat4x4( &worldMatrix) * XMMatrixScaling(3.0f, entity->getLength(), 0.0f) * XMMatrixTranslationFromVector( XMLoadFloat3( &positionVector )));

	icePatchVertexModel->Render(deviceContext);

	bool result = textureShader->Render(deviceContext, 
										icePatchVertexModel->GetIndexCount(), 
										snowFieldMatrix, 
										viewMatrix, 
										projectionMatrix,
										icePatchTexture->GetTexture()); //get the texture to render

	return result; 
}