HRESULT GenerationShader::compileShaderFromFile(WCHAR * FileName, LPCSTR EntryPoint, LPCSTR ShaderModel, ID3DBlob ** Outblob)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debug output, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* errorBlob;
	//DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;


	hr = D3DCompileFromFile(FileName, NULL, NULL, EntryPoint, ShaderModel,
		dwShaderFlags, NULL, Outblob, &errorBlob);

	if (FAILED(hr))
	{
		if (errorBlob != NULL)
		{
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
		if (errorBlob)
		{
			errorBlob->Release();
		}
		return hr;
	}

	if (errorBlob) errorBlob->Release();

	return S_OK;

}