HRESULT Technique::setPixelShader(LPCWSTR filename, LPCSTR entryPoint, LPCSTR shaderModel, ID3D11Device* g_pd3dDevice){

	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pPSBlob = nullptr;
	ID3DBlob* pErrorBlob = nullptr;
	hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
		dwShaderFlags, 0, &pPSBlob, &pErrorBlob);
	if (FAILED(hr))
	{
		if (pErrorBlob)
		{
			std::ofstream fout("Shader_Debug.txt");
			fout << reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer());
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}

	}
	if (pErrorBlob) pErrorBlob->Release();

	hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &g_pPixelShader);
	if (FAILED(hr))
	{
		pPSBlob->Release();

	}

	pPSBlob->Release();
	return hr;
}