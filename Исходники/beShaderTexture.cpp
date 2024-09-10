bool beShaderTexture::Init(beRenderInterface* ri, const beWString& pixelFilename, const beWString& vertexFilename)
{
	ID3D11Device* device = ri->GetDevice();
	D3D11_SAMPLER_DESC samplerDesc;

	//ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vBuffer = nullptr;
	ID3D10Blob* pBuffer = nullptr;

	//HRESULT res = D3DCompileFromFile(vertexFilename.c_str(), nullptr, nullptr, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &vBuffer, &errorMessage);
	//if (FAILED(res))
	//{
	//	if (errorMessage)
	//	{
	//		LOG("%s\n Filename:%s, res:0x%08x", errorMessage->GetBufferPointer(), vertexFilename.c_str(), res);
	//	}

	//	BE_ASSERT(false);
	//	return false;
	//}

	//res = D3DCompileFromFile(pixelFilename.c_str(), nullptr, nullptr, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, &pBuffer, &errorMessage);
	//if (FAILED(res))
	//{
	//	if (errorMessage)
	//	{
	//		bePrintf::bePrintf(false, "", "%s\n Filename:%s, res:0x%08x", errorMessage->GetBufferPointer(), pixelFilename.c_str(), res);
	//	}

	//	BE_ASSERT(false);
	//	return false;
	//}

	D3DReadFileToBlob(vertexFilename.c_str(), &vBuffer);
	D3DReadFileToBlob(pixelFilename.c_str(), &pBuffer);
	defer({BE_SAFE_RELEASE(vBuffer);});