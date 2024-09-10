void SpriteGame::render()
{
	if(backBuffer == nullptr)
		return;

	float black[4] = { 1.0f, 0.5f, 0.0f, 1.0f };
	backBuffer->fillColor(black);

	device->setInputLayout(inputLayout);
	device->setVertexBuffer(0, vertexBuffer, sizeof(Vertex), 0);
	device->setTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	device->setVertexShader(vertexShader);
	device->setPixelShader(pixelShader);

	pixelShader->setResource(0, srvTexture);
	pixelShader->setSampler(0, samplerState);

	for(int i=0; i<sizeof(sprites)/sizeof(Sprite); i++)
	{
		Matrix mvpMatrix = sprites[i].getWorldMatrix() * viewProjectionMatrix;
		mvpMatrix = mvpMatrix.transpose();

		matrixBuffer->update(&mvpMatrix);
		vertexShader->setConstantBuffer(0, matrixBuffer);

		device->draw(4, 0);
	}

	swapChain->rotate();
}