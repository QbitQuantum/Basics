int ShaderClass::CreatePixelShader(ID3D11PixelShader** ppPS, WCHAR* fileName, char* EntryPoint)
{
	HRESULT hr;
	// Initialie Pixel shader
	ID3D10Blob* pixelShaderBuffer;
	ID3D10Blob* errorMessages;
	hr = D3DCompileFromFile(
		fileName,
		NULL,
		NULL,
		EntryPoint,
		"ps_5_0",
		0,
		0,
		&pixelShaderBuffer,
		&errorMessages);

	if (FAILED(hr))
	{
		// If the shader failed to compile it should have writen something to the error message.
		if (errorMessages)
		{
			OutputShaderErrorMessage(errorMessages, fileName);
			return -26;
		}
		// If there was nothing in the error message then it simply could not find the shader file itself.
		else
		{
			MessageBox(0, fileName, L"Missing Shader File", MB_OK);
			return -27;
		}
	}

	// Create the pixel shader from the buffer.
	hr = SystemClass::GetInstance()->mGrapInst->GetDevice()->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, ppPS);
	if (FAILED(hr))
	{
		MessageBox(0, L"Failed to create pixel shader", 0, MB_OK);
		return -28;
	}

	pixelShaderBuffer->Release();
	return 0;
}