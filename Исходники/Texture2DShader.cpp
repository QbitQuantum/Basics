	uint Texture2DShader::Render(ID3D11DeviceContext* pDeviceContext, GraphicSettings* settings, translationData* modelData, XMFLOAT4X4 view, XMFLOAT4X4 projection, XMFLOAT4X4 ortho)
	{
		uint result;
		XMMATRIX mWorld = XMLoadFloat4x4(&modelData->objectTranslation);
		XMMATRIX mOrtho = XMLoadFloat4x4(&ortho);

		XMMATRIX WO = XMMatrixTranspose(mWorld*mOrtho);

		TBuffer data;
		XMStoreFloat4x4(&data.mWO, WO);

		result = mBuffer->SetConstantBuffer(pDeviceContext, &data);
		iferr(result) return result;

		RenderShader(pDeviceContext, modelData->indexCount, modelData->indexStart);

		return 0;
	}