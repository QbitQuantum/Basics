HRESULT ManagementShader::initPixelShader(ID3D11Device* device, std::wstring filePath, std::wstring fileName, ID3D11PixelShader** shader, ID3DBlob** blob)
{
	HRESULT hr = S_OK;

	std::wstring completePath = filePath + fileName;

	hr = D3DReadFileToBlob(completePath.c_str(), blob);
	if(FAILED(hr))
		MessageBox(NULL, L"ManagmenetShader::initPixelShader() | D3DReadFileToBlob() | Failed", completePath.c_str(), MB_OK | MB_ICONEXCLAMATION);
	else
	{
		hr = device->CreatePixelShader((*blob)->GetBufferPointer(), (*blob)->GetBufferSize(), NULL, shader);
		if(FAILED(hr))
			MessageBox(NULL, L"ManagementShader::initPixelShader() | device->CreatePixelShader() | Failed", completePath.c_str(), MB_OK | MB_ICONEXCLAMATION);
	}

	return hr;
}